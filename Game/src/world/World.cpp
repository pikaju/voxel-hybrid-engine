#include "World.h"

#include "../graphics/Window.h"
#include "../graphics/renderer/AttributelessRenderer.h"
#include "../util/FrustumCuller.h"

namespace world {

	World::World() : m_chunkManager(this), m_smoothFog(0.0f)
	{
	}

	World::~World()
	{
	}

	void World::initialize()
	{
		m_chunkManager.initialize();

		m_shader.initialize();
		m_shader.loadShader("res/Voxel.vert", graphics::SHADERTYPE_VERTEX);
		m_shader.loadShader("res/Voxel.frag", graphics::SHADERTYPE_FRAGMENT);
		m_shader.link();

		m_screen.initialize();
		m_screen.loadShader("res/Screen.vert", graphics::SHADERTYPE_VERTEX);
		m_screen.loadShader("res/Screen.frag", graphics::SHADERTYPE_FRAGMENT);
		m_screen.link();

		m_ssao.initialize();
	}
	
	void World::cleanup()
	{
		m_framebuffer.cleanup();
		m_shader.cleanup();
		m_ssao.cleanup();
		m_screen.cleanup();

		m_chunkManager.cleanup();
	}

	void World::update(const io::Input& input, float delta)
	{
		m_chunkManager.update(delta);
		m_camera.debugUpdate(input, delta);
		m_smoothFog += (m_chunkManager.getFogDistance() - m_smoothFog) * delta;
	}
	
	void World::render(const graphics::Window& window)
	{
		if (window.getWidth() != m_framebuffer.getWidth() || window.getHeight() != m_framebuffer.getHeight()) {
			if (window.getWidth() != 0 && window.getHeight() != 0) {
				std::vector<graphics::Attachment> attachments;
				attachments.push_back(graphics::ATTACHMENT_COLOR);
				attachments.push_back(graphics::ATTACHMENT_COLOR);
				attachments.push_back(graphics::ATTACHMENT_DEPTH);
				std::vector<graphics::Format> formats;
				formats.push_back(graphics::FORMAT_RGBA8);
				formats.push_back(graphics::FORMAT_RGB8);
				formats.push_back(graphics::FORMAT_DEPTH24);

				m_msaaFramebuffer.cleanup();
				m_msaaFramebuffer.initialize(window.getWidth(), window.getHeight(), attachments.size(), attachments.data(), formats.data(), 0);
				
				m_framebuffer.cleanup();
				m_framebuffer.initialize(window.getWidth(), window.getHeight(), attachments.size(), attachments.data(), formats.data());

				m_ssao.setFramebufferSize(m_framebuffer.getWidth(), m_framebuffer.getHeight());
			}
		}
		graphics::AttributelessRenderer renderer;
		
		m_msaaFramebuffer.bind();
		renderer.clear(true, true);

		math::Mat4f viewMatrix = m_camera.getViewMatrix();
		math::Mat4f projectionMatrix = math::Mat4f::perspective(m_framebuffer.getAspectRatio(), 90.0f, 0.125f, 1024.0f);

		util::FrustumCuller frustumCuller;
		frustumCuller.extractPlanes(viewMatrix * projectionMatrix);

		m_shader.enable();
		m_shader.setUniform("modelMatrix", math::Mat4f::identity());
		m_shader.setUniform("viewMatrix", viewMatrix);
		m_shader.setUniform("projectionMatrix", projectionMatrix);
		m_chunkManager.render(m_shader, frustumCuller);
		m_shader.disable();

		m_msaaFramebuffer.blitTo(m_framebuffer);

		m_ssao.render(m_framebuffer, 1, 2, viewMatrix, projectionMatrix);

		window.bind();
		m_framebuffer.use(0, 0);
		m_framebuffer.use(1, 1);
		m_framebuffer.use(2, 2);
		m_ssao.getFramebuffer().use(0, 3);
		m_screen.enable();
		m_screen.setUniform("inverseViewMatrix", math::Mat4f::inverse(viewMatrix));
		m_screen.setUniform("inverseProjectionMatrix", math::Mat4f::inverse(projectionMatrix));
		m_screen.setUniform("cameraPosition", m_camera.position);
		m_screen.setUniform("fogDistance", m_smoothFog);
		m_screen.setUniform("renderedColor", 0);
		m_screen.setUniform("renderedNormal", 1);
		m_screen.setUniform("renderedDepth", 2);
		m_screen.setUniform("renderedSSAO", 3);
		renderer.renderTriangleStrip(4);
		m_screen.disable();
	}

}