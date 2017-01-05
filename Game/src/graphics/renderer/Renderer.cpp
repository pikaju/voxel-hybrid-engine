#include "Renderer.h"

#include <glew.h>

#include "../../io/Log.h"

namespace graphics {

	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::setDepthRead(bool depth)
	{
		if (depth) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);
	}

	void Renderer::setCulling(bool culling)
	{
		if (culling) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);
	}

	void Renderer::setWireframe(bool wireframe)
	{
		if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Renderer::clear(bool color, bool depth, bool stencil)
	{
		int flags = 0;
		if (color) flags |= GL_COLOR_BUFFER_BIT;
		if (depth) flags |= GL_DEPTH_BUFFER_BIT;
		if (stencil) flags |= GL_STENCIL_BUFFER_BIT;
		glClear(flags);
	}

}