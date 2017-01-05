#pragma once

#include "Renderer.h"

namespace graphics {

	class AttributelessRenderer : public Renderer
	{
	public:
		AttributelessRenderer();
		~AttributelessRenderer();

		void renderTriangles(unsigned int numVertices);
		void renderTriangleStrip(unsigned int numVertices);
	};

}