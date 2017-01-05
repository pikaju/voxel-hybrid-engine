#pragma once

#include "../ShaderProgram.h"
#include "../../texture/Framebuffer.h"
#include "../../../math/Vec3.h"

namespace graphics {

	class SSAO
	{
	public:
		SSAO();
		~SSAO();
		
		void initialize();
		void cleanup();

		void setFramebufferSize(unsigned int width, unsigned int height);

		void render(const graphics::Framebuffer& source, unsigned int normalTextureID, unsigned int depthTextureID, const math::Mat4<float>& viewMatrix, const math::Mat4<float>& projectionMatrix);

		inline const graphics::Framebuffer& getFramebuffer() const { return m_framebuffer; }
	private:
		graphics::ShaderProgram m_shader;
		graphics::Framebuffer m_framebuffer;
		graphics::Texture m_noiseTexture;
		math::Vec3f* m_samples;
		unsigned int m_numSamples;
	};

}