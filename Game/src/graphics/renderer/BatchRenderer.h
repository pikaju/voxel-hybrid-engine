#pragma once

#include "Renderer.h"

namespace graphics {

	class Attribute;

	class BatchRenderer : public Renderer
	{
	public:
		BatchRenderer();
		virtual ~BatchRenderer();

		virtual void initialize(unsigned int numAllocatedVertices, const Attribute* attributes, unsigned int numAttributes);
		virtual void cleanup();

		virtual void begin();
		virtual void end();
		virtual void flush();

		virtual void submit(const void* vertex);
	private:
		unsigned int m_vbo;
		unsigned int m_vao;

		unsigned int m_index;
		unsigned int m_mode;
		unsigned int m_stride;
		unsigned int m_numAllocatedVertices;

		void* m_pointer;
	};

}