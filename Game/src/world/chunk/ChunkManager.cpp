#include "ChunkManager.h"

#include <algorithm>

#include "Chunk.h"
#include "../World.h"
#include "../../util/FrustumCuller.h"

namespace world {

	ChunkManager::ChunkManager(World* world) : m_world(world), m_threadPool(), m_chunkMap(), m_chunkVector(), m_processingVector(), m_fogDistance(0.0f)
	{
	}

	ChunkManager::~ChunkManager()
	{
	}

	void ChunkManager::initialize()
	{
		m_threadPool.start(7);
	}
	
	void ChunkManager::cleanup()
	{
		m_threadPool.stop();
	}

	void ChunkManager::update(float delta)
	{
		if (getChunk((math::Vec3i)(m_world->getCamera().position / (float)CHUNK_SIZE)) == nullptr) {
			generateChunk((math::Vec3i)(m_world->getCamera().position / (float)CHUNK_SIZE));
		}

		for (unsigned int i = 0; i < m_chunkVector.size(); i++) {
			m_chunkVector[i]->update(delta);
			m_chunkVector[i]->calculateDistanceToCamera();
			if (!m_chunkVector[i]->isRunning() && m_chunkVector[i]->getDistanceToCamera() > m_world->getRenderDistance() * (float)CHUNK_SIZE) {
				m_chunkVector[i]->remove();
			}
		}

		m_fogDistance = 0.0f;
		for (unsigned int i = 0; i < m_chunkVector.size(); i++) {
			if (m_chunkVector[i]->getInitializationProgress() == INITIALIZATIONPROGRESS_DONE) continue;
			if (m_fogDistance == 0.0f || m_fogDistance > m_chunkVector[i]->getDistanceToCamera() - (float)CHUNK_SIZE) {
				m_fogDistance = m_chunkVector[i]->getDistanceToCamera() - (float)CHUNK_SIZE;
			}
		}

		std::sort(m_processingVector.begin(), m_processingVector.end(), chunkSort);
		
		for (unsigned int i = 0; i < m_processingVector.size(); i++) {
			if (m_processingVector[i]->isRemoved()) {
				m_processingVector[i] = m_processingVector.back();
				m_processingVector.pop_back();
				i--;
				continue;
			}
			if (m_processingVector[i]->isRunning()) {
				continue;
			}
			if (m_threadPool.isSaturated()) {
				continue;
			}
			m_processingVector[i]->run();
			m_threadPool.addTask(util::ThreadTask(chunkThread, (void*)m_processingVector[i]));
			m_processingVector.erase(m_processingVector.begin() + i);
			i--;
		}

		for (unsigned int i = 0; i < m_chunkVector.size(); i++) {
			if (m_chunkVector[i]->isRemoved()) {
				removeChunk(m_chunkVector[i]->getPosition());
				i--;
			}
		}
	}
	
	void ChunkManager::render(const graphics::ShaderProgram& shaderProgram, const util::FrustumCuller& frustumCuller) const
	{
		for (unsigned int i = 0; i < m_chunkVector.size(); i++) {
			if (frustumCuller.isSphereInFrustum(math::Vec3f((float)(m_chunkVector[i]->getPosition().x * CHUNK_SIZE + CHUNK_SIZE / 2), (float)(m_chunkVector[i]->getPosition().y * CHUNK_SIZE + CHUNK_SIZE / 2), (float)(m_chunkVector[i]->getPosition().z * CHUNK_SIZE + CHUNK_SIZE / 2)), sqrt((float)(3 * (CHUNK_SIZE * CHUNK_SIZE))))) {
				shaderProgram.setUniform("modelMatrix", math::Mat4f::translation((float)(m_chunkVector[i]->getPosition().x * CHUNK_SIZE), (float)(m_chunkVector[i]->getPosition().y * CHUNK_SIZE), (float)(m_chunkVector[i]->getPosition().z * CHUNK_SIZE)));
				m_chunkVector[i]->render();
			}
		}
	}

	void ChunkManager::addChunk(Chunk* chunk)
	{
		chunk->setID(m_chunkVector.size());
		m_chunkVector.push_back(chunk);
		m_chunkMap[chunk->getPosition()] = chunk;
	}

	void ChunkManager::generateChunk(const math::Vec3i& position)
	{
		if (((m_world->getCamera().position / (float) CHUNK_SIZE) - (math::Vec3f)position).getLengthSquared() > m_world->getRenderDistance() * m_world->getRenderDistance()) {
			return;
		}
		Chunk* chunk = new Chunk(this, position);
		addChunk(chunk);
		addToProcessingList(chunk);
	}

	Chunk* ChunkManager::getChunk(const math::Vec3i& position)
	{
		auto& it = m_chunkMap.find(position);
		if (it == m_chunkMap.end()) return nullptr;
		return it->second;
	}
	
	void ChunkManager::removeChunk(const math::Vec3i& position)
	{
		Chunk* chunk = m_chunkMap[position];
		m_chunkMap.erase(position);
		m_chunkVector[chunk->getID()] = m_chunkVector.back();
		m_chunkVector[chunk->getID()]->setID(chunk->getID());
		m_chunkVector.pop_back();
		delete chunk;
	}

	void ChunkManager::addToProcessingList(Chunk* chunk) {
		m_processingVector.push_back(chunk);
		chunk->setInProgress(true);
	}

	bool ChunkManager::isSurrounded(const math::Vec3i& position)
	{
		for (int x = -1; x <= 1; x++) {
			for (int y = -1; y <= 1; y++) {
				for (int z = -1; z <= 1; z++) {
					Chunk* chunk = getChunk(position + math::Vec3i(x, y, z));
					if (chunk == nullptr || chunk->getInitializationProgress() == INITIALIZATIONPROGRESS_PRE_NEIGHBOR_TERRAIN) return false;
				}
			}
		}
		return true;
	}

	void ChunkManager::chunkThread(void* chunk)
	{
		Chunk* c = (Chunk*)chunk; c->threadUpdate();
	}

	bool ChunkManager::chunkSort(Chunk* i, Chunk* j)
	{
		return i->getDistanceToCamera() < j->getDistanceToCamera();
	}

}