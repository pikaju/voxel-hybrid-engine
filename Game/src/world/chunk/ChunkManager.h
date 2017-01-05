#pragma once

#include <unordered_map>
#include <vector>

#include "../../math/Vec3.h"
#include "../../util/ThreadPool.h"

namespace graphics {
	class ShaderProgram;
}

namespace util {
	class FrustumCuller;
}

namespace world {

	class World;
	class Chunk;

	class ChunkManager
	{
	public:
		ChunkManager(World* world);
		~ChunkManager();

		void initialize();
		void cleanup();

		void update(float delta);
		void render(const graphics::ShaderProgram& shaderProgram, const util::FrustumCuller& frustumCuller) const;

		void addChunk(Chunk* chunk);
		void generateChunk(const math::Vec3i& position);
		Chunk* getChunk(const math::Vec3i& position);
		void removeChunk(const math::Vec3i& position);

		void addToProcessingList(Chunk* chunk);

		bool isSurrounded(const math::Vec3i& position);

		inline World* getWorld() { return m_world; }

		inline float getFogDistance() const { return m_fogDistance; }
	protected:
		static void chunkThread(void* chunk);
		static bool chunkSort(Chunk* i, Chunk* j);
	private:
		World* m_world;

		util::ThreadPool m_threadPool;

		std::unordered_map<math::Vec3i, Chunk*> m_chunkMap;
		std::vector<Chunk*> m_chunkVector;
		std::vector<Chunk*> m_processingVector;

		float m_fogDistance;
	};

}