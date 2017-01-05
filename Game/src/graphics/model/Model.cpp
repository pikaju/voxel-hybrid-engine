#include "Model.h"

#include <glew.h>

#include "../Attribute.h"

namespace graphics {

	Model::Model() : m_vbo(0), m_ibo(0), m_vao(0), m_mode(GL_TRIANGLES), m_indexType(GL_UNSIGNED_INT), m_numIndices(0)
	{
	}
	
	Model::~Model()
	{
	}

	void Model::initialize()
	{
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
		glGenVertexArrays(1, &m_vao);
	}

	void Model::cleanup()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void Model::setData(const void* vertexData, unsigned int numVertices, const void* indexData, unsigned int numIndices, const Attribute* attributes, unsigned int numAttributes)
	{
		m_numIndices = numIndices;

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		unsigned int stride = 0;
		for (unsigned int i = 0; i < numAttributes; i++) {
			stride += attribute::getGLTypeSize(attributes[i].type) * attributes[i].amount;
		}
		glBufferData(GL_ARRAY_BUFFER, stride * numVertices, vertexData, GL_STATIC_DRAW);
		
		unsigned int pointer = 0;
		for (unsigned int i = 0; i < numAttributes; i++) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attributes[i].amount, attribute::getGLType(attributes[i].type), attributes[i].normalized, stride, (const void*)pointer);
			pointer += attribute::getGLTypeSize(attributes[i].type) * attributes[i].amount;
		}
		

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_numIndices, indexData, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	void Model::render() const
	{
		glBindVertexArray(m_vao);
		glDrawElements(m_mode, m_numIndices, m_indexType, nullptr);
		glBindVertexArray(0);
	}

}