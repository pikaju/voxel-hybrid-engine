#pragma once

#include "voxel/VoxelArrayContainer.h"
#include "../../graphics/model/Model.h"
#include "../../math/Vec3.h"
#include "../../math/Vec4.h"
#include "../../graphics/model/Mesh.h"

#define CHUNK_SIZE 32

namespace world {

	class ChunkManager;

	enum ChunkNeighbor
	{
		CHUNKNEIGHBOR_TOP = 0,
		CHUNKNEIGHBOR_BOTTOM,
		CHUNKNEIGHBOR_LEFT,
		CHUNKNEIGHBOR_RIGHT,
		CHUNKNEIGHBOR_FRONT,
		CHUNKNEIGHBOR_BACK,
		CHUNKNEIGHBOR_COUNT
	};

	enum InitializationProgress
	{
		INITIALIZATIONPROGRESS_PRE_NEIGHBOR_TERRAIN,
		INITIALIZATIONPROGRESS_POST_NEIGHBOR_TERRAIN,
		INITIALIZATIONPROGRESS_MESH,
		INITIALIZATIONPROGRESS_DONE
	};


	class ChunkVertex
	{
	public:
		math::Vec3f position;
		math::Vec4b color;
		math::Vec3f normal;

		ChunkVertex(const math::Vec3f& position = math::Vec3f(), const math::Vec4b& color = math::Vec4b(), const math::Vec3f& normal = math::Vec3f()) : position(position), color(color), normal(normal) {  }
		~ChunkVertex() {  }
	};

	class Chunk
	{
	public:
		Chunk(ChunkManager* chunkManager, const math::Vec3i& position);
		~Chunk();

		void update(float delta);
		void render();

		void threadUpdate();
		
		inline unsigned int getID() const { return m_chunkID; }
		inline void setID(unsigned int chunkID) { m_chunkID = chunkID; }
		
		inline const math::Vec3i& getPosition() const { return m_position; }

		inline void getVoxelArrayBorder(const Voxel** voxels) const { m_voxelContainer.getVoxelArrayBorder(voxels); }
		inline const Voxel& getVoxel(unsigned int x, unsigned int y, unsigned int z) const { return m_voxelContainer.getVoxel(x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE); }
		const Voxel& getVoxelRelative(int x, int y, int z);

		inline void setNeighbor(const ChunkNeighbor& direction, Chunk* neighbor) { m_neighbors[direction] = neighbor; }
		
		inline bool isRunning() const { return m_running; }
		inline void run() { m_running = true; }
		inline void setInProgress(bool inProgress) { m_inProgress = inProgress; }
		inline const InitializationProgress& getInitializationProgress() const { return m_progress; }

		inline bool isRemoved() const { return m_removed; }
		inline void remove() { m_removed = true; }

		inline float getDistanceToCamera() const { return m_distanceToCamera; }
		void calculateDistanceToCamera();
	private:
		unsigned int m_chunkID;
		
		ChunkManager* m_chunkManager;
		math::Vec3i m_position;

		VoxelArrayContainer m_voxelContainer;
		graphics::Mesh<ChunkVertex, unsigned int> m_mesh;
		graphics::Model m_model;

		Chunk* m_neighbors[CHUNKNEIGHBOR_COUNT];

		bool m_running;
		bool m_inProgress;
		InitializationProgress m_progress;
	
		bool m_removed;

		float m_distanceToCamera;
	};

}