#pragma once

namespace graphics {

	class Attribute;

	class Model
	{
	public:
		Model();
		~Model();

		void initialize();
		void cleanup();

		void setData(const void* vertexData, unsigned int numVertices, const void* indexData, unsigned int numIndices, const Attribute* attributes, unsigned int numAttributes);

		void render() const;
	private:
		unsigned int m_vbo;
		unsigned int m_ibo;
		unsigned int m_vao;

		unsigned int m_mode;
		unsigned int m_indexType;
		unsigned int m_numIndices;
	};

}