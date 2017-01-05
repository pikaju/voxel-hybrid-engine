#pragma once

namespace graphics {

	class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		void setDepthRead(bool depth);
		void setCulling(bool culling);
		void setWireframe(bool wireframe);
		void clear(bool color = true, bool depth = false, bool stencil = false);
	};

}