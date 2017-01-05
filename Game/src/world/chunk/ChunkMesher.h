#pragma once

namespace graphics {
	template<typename Vertex, typename Index> class Mesh;
}

namespace world {

	class Chunk;
	class ChunkVertex;

	class ChunkMesher
	{
	public:
		static void createMesh(Chunk& chunk, graphics::Mesh<ChunkVertex, unsigned int>& model);
	};

}