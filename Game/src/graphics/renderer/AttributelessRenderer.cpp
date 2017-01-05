#include "AttributelessRenderer.h"

#include <glew.h>

namespace graphics {

	AttributelessRenderer::AttributelessRenderer()
	{
	}

	AttributelessRenderer::~AttributelessRenderer()
	{
	}

	void AttributelessRenderer::renderTriangles(unsigned int numVertices)
	{
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}

	void AttributelessRenderer::renderTriangleStrip(unsigned int numVertices)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);
	}

}