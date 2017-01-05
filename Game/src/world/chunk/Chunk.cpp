#include "Chunk.h"

#include "ChunkManager.h"
#include "ChunkMesher.h"

#include "../World.h"
#include "../../util/Noise.h"

namespace world {

	Chunk::Chunk(ChunkManager* chunkManager, const math::Vec3i& position) : m_chunkManager(chunkManager), m_position(position), m_voxelContainer(CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE), m_model(), m_running(false), m_inProgress(false), m_progress(INITIALIZATIONPROGRESS_PRE_NEIGHBOR_TERRAIN), m_removed(false)
	{
		Chunk* neighbor;
		if ((neighbor = m_chunkManager->getChunk(m_position + math::Vec3i(0, 1, 0))) != nullptr) { setNeighbor(CHUNKNEIGHBOR_TOP, neighbor); neighbor->setNeighbor(CHUNKNEIGHBOR_BOTTOM, this); }
		if ((neighbor = m_chunkManager->getChunk(m_position + math::Vec3i(0, -1, 0))) != nullptr) { setNeighbor(CHUNKNEIGHBOR_BOTTOM, neighbor); neighbor->setNeighbor(CHUNKNEIGHBOR_TOP, this); }
		if ((neighbor = m_chunkManager->getChunk(m_position + math::Vec3i(-1, 0, 0))) != nullptr) { setNeighbor(CHUNKNEIGHBOR_LEFT, neighbor); neighbor->setNeighbor(CHUNKNEIGHBOR_RIGHT, this); }
		if ((neighbor = m_chunkManager->getChunk(m_position + math::Vec3i(1, 0, 0))) != nullptr) { setNeighbor(CHUNKNEIGHBOR_RIGHT, neighbor); neighbor->setNeighbor(CHUNKNEIGHBOR_LEFT, this); }
		if ((neighbor = m_chunkManager->getChunk(m_position + math::Vec3i(0, 0, 1))) != nullptr) { setNeighbor(CHUNKNEIGHBOR_FRONT, neighbor); neighbor->setNeighbor(CHUNKNEIGHBOR_BACK, this); }
		if ((neighbor = m_chunkManager->getChunk(m_position + math::Vec3i(0, 0, -1))) != nullptr) { setNeighbor(CHUNKNEIGHBOR_BACK, neighbor); neighbor->setNeighbor(CHUNKNEIGHBOR_FRONT, this); }
	
		m_mesh.addAttribute(graphics::Attribute(graphics::TYPE_FLOAT, 3));
		m_mesh.addAttribute(graphics::Attribute(graphics::TYPE_UNSIGNED_BYTE, 4, true));
		m_mesh.addAttribute(graphics::Attribute(graphics::TYPE_FLOAT, 3));

		m_model.initialize();
	}
	
	Chunk::~Chunk()
	{
		m_model.cleanup();
	}

	void Chunk::update(float delta)
	{
		if (m_progress == INITIALIZATIONPROGRESS_POST_NEIGHBOR_TERRAIN && !m_inProgress && m_chunkManager->isSurrounded(m_position)) {
			m_chunkManager->addToProcessingList(this);
		}
		if (m_progress != INITIALIZATIONPROGRESS_PRE_NEIGHBOR_TERRAIN) {
			if (m_neighbors[CHUNKNEIGHBOR_TOP] == nullptr) m_chunkManager->generateChunk(m_position + math::Vec3i(0, 1, 0));
			if (m_neighbors[CHUNKNEIGHBOR_BOTTOM] == nullptr) m_chunkManager->generateChunk(m_position + math::Vec3i(0, -1, 0));
			if (m_neighbors[CHUNKNEIGHBOR_LEFT] == nullptr) m_chunkManager->generateChunk(m_position + math::Vec3i(-1, 0, 0));
			if (m_neighbors[CHUNKNEIGHBOR_RIGHT] == nullptr) m_chunkManager->generateChunk(m_position + math::Vec3i(1, 0, 0));
			if (m_neighbors[CHUNKNEIGHBOR_FRONT] == nullptr) m_chunkManager->generateChunk(m_position + math::Vec3i(0, 0, 1));
			if (m_neighbors[CHUNKNEIGHBOR_BACK] == nullptr) m_chunkManager->generateChunk(m_position + math::Vec3i(0, 0, -1));
		}
		if (m_progress == INITIALIZATIONPROGRESS_DONE && !m_mesh.isEmpty()) {
			m_mesh.createModel(m_model);
			m_mesh.clear();
		}
	}
	
	void Chunk::render()
	{
		m_model.render();
	}

	const Voxel& Chunk::getVoxelRelative(int x, int y, int z)
	{
		if (y > CHUNK_SIZE - 1) return m_neighbors[CHUNKNEIGHBOR_TOP]->getVoxelRelative(x, y - CHUNK_SIZE, z);
		if (y < 0) return m_neighbors[CHUNKNEIGHBOR_BOTTOM]->getVoxelRelative(x, y + CHUNK_SIZE, z);
		if (x < 0) return m_neighbors[CHUNKNEIGHBOR_LEFT]->getVoxelRelative(x + CHUNK_SIZE, y, z);
		if (x > CHUNK_SIZE - 1) return m_neighbors[CHUNKNEIGHBOR_RIGHT]->getVoxelRelative(x - CHUNK_SIZE, y, z);
		if (z > CHUNK_SIZE - 1) return m_neighbors[CHUNKNEIGHBOR_FRONT]->getVoxelRelative(x, y, z - CHUNK_SIZE);
		if (z < 0) return m_neighbors[CHUNKNEIGHBOR_BACK]->getVoxelRelative(x, y, z + CHUNK_SIZE);
		return getVoxel((unsigned int)x, (unsigned int)y, (unsigned int)z);
	}

	void Chunk::threadUpdate()
	{
		if (m_progress != INITIALIZATIONPROGRESS_PRE_NEIGHBOR_TERRAIN) {
			for (unsigned int i = 0; i < CHUNKNEIGHBOR_COUNT; i++) {
				if (m_neighbors[i] == nullptr) return;
			}
		}

		util::Noise noise(0);
		switch (m_progress) {
		case INITIALIZATIONPROGRESS_PRE_NEIGHBOR_TERRAIN:
			for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
				for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
					for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
						float n0 = noise.noise((float)((int)x + m_position.x * CHUNK_SIZE) / 32.0f, (float)((int)y + m_position.y * CHUNK_SIZE) / 32.0f, (float)((int)z + m_position.z * CHUNK_SIZE) / 32.0f);
						float n1 = noise.noise((float)((int)x + m_position.x * CHUNK_SIZE) / 64.0f, (float)((int)y + m_position.y * CHUNK_SIZE) / 64.0f, (float)((int)z + m_position.z * CHUNK_SIZE) / 64.0f) * 2.0f;
						float n2 = noise.noise((float)((int)x + m_position.x * CHUNK_SIZE) / 128.0f, (float)((int)y + m_position.y * CHUNK_SIZE) / 128.0f, (float)((int)z + m_position.z * CHUNK_SIZE) / 128.0f) * 4.0f;
						float n3 = noise.noise((float)((int)x + m_position.x * CHUNK_SIZE) / 256.0f, (float)((int)y + m_position.y * CHUNK_SIZE) / 256.0f, (float)((int)z + m_position.z * CHUNK_SIZE) / 256.0f) * 8.0f;
						float n4 = noise.noise((float)((int)x + m_position.x * CHUNK_SIZE) / 8192.0f, (float)((int)y + m_position.y * CHUNK_SIZE) / 8192.0f, (float)((int)z + m_position.z * CHUNK_SIZE) / 8192.0f) * 256.0f;

						char colorOffset = (char)(noise.noise(x * 0.25f, y * 0.25f, z * 0.25f) * 16.0f);
						m_voxelContainer.setVoxel(x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE, Voxel(32, 128 + colorOffset, 32, n0 + n1 + n2 + n3 >(float)((int)y + m_position.y * CHUNK_SIZE) / 32.0f ? 255 : 0, abs(m_position.x + m_position.y + m_position.z) % 2 == 0 ? true : false));
						if (n0 > (float)((int)y + m_position.y * CHUNK_SIZE) / 32.0f) {
							m_voxelContainer.setVoxel(x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE, Voxel(64 + colorOffset, 64 + colorOffset, 64 + colorOffset, 255, abs(m_position.x + m_position.y + m_position.z) % 2 == 0 ? true : false));
						}
					}
				}
			}
			m_progress = INITIALIZATIONPROGRESS_POST_NEIGHBOR_TERRAIN;
			break;
		case INITIALIZATIONPROGRESS_POST_NEIGHBOR_TERRAIN:
			m_progress = INITIALIZATIONPROGRESS_MESH;
			break;
		}
		if (m_progress == INITIALIZATIONPROGRESS_MESH) {
			ChunkMesher::createMesh(*this, m_mesh);
			m_progress = INITIALIZATIONPROGRESS_DONE;
		}
		m_inProgress = false;
		m_running = false;
	}

	void Chunk::calculateDistanceToCamera()
	{
		m_distanceToCamera = (m_chunkManager->getWorld()->getCamera().position - ((math::Vec3f)m_position * (float)CHUNK_SIZE + (float)CHUNK_SIZE / 2.0f)).getLength<float>();
	}

}