#pragma once

#include "chunk/ChunkManager.h"
#include "../graphics/shader/ShaderProgram.h"
#include "../graphics/shader/effect/SSAO.h"
#include "../graphics/texture/Framebuffer.h"
#include "../util/SmoothCamera.h"

namespace graphics {
	class Window;
}

namespace io {
	class Input;
}

namespace world {

	class World
	{
	public:
		World();
		~World();

		void initialize();
		void cleanup();

		void update(const io::Input& input, float delta);
		void render(const graphics::Window& window);

		inline const util::SmoothCamera& getCamera() const { return m_camera; }
		inline float getRenderDistance() const { return 12.0f; }
	private:
		ChunkManager m_chunkManager;

		graphics::ShaderProgram m_shader;
		graphics::ShaderProgram m_screen;
		graphics::Framebuffer m_msaaFramebuffer;
		graphics::Framebuffer m_framebuffer;
		graphics::SSAO m_ssao;
		util::SmoothCamera m_camera;

		float m_smoothFog;
	};

}