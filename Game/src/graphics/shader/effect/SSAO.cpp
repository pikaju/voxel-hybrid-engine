#include "SSAO.h"

#include <random>

#include "../../renderer/AttributelessRenderer.h"
#include "../../../math/Mat4.h"

namespace graphics {

	SSAO::SSAO() : m_shader(), m_framebuffer()
	{
	}

	SSAO::~SSAO()
	{
	}

	void SSAO::initialize()
	{
		std::mt19937 engine(4);
		std::uniform_int_distribution<int> noiseDistribution(0, 255);
		std::uniform_real_distribution<float> kernelDistribution0(-1.0f, 1.0f);
		std::uniform_real_distribution<float> kernelDistribution1(0.25f, 1.0f);
		std::uniform_real_distribution<float> kernelDistribution2(0.5f, 0.5f);

		m_numSamples = 16;
		m_samples = new math::Vec3f[m_numSamples];

		for (unsigned int i = 0; i < m_numSamples; i++) {
			float distance = kernelDistribution2(engine);
			distance *= distance;
			m_samples[i] = math::Vec3f(kernelDistribution0(engine), kernelDistribution0(engine), kernelDistribution1(engine)).normalized() * 0.25f;
		}

		const unsigned int noiseTextureSize = 5;
		math::Vec3b noisePixels[noiseTextureSize * noiseTextureSize];
		for (unsigned int i = 0; i < noiseTextureSize * noiseTextureSize; i++) {
			noisePixels[i] = math::Vec3b(noiseDistribution(engine), noiseDistribution(engine), noiseDistribution(engine));
		}
		m_noiseTexture.initialize(noiseTextureSize, noiseTextureSize, FORMAT_RGB8, noisePixels);

		m_shader.initialize();
		m_shader.loadShader("res/SSAO.vert", graphics::SHADERTYPE_VERTEX);
		m_shader.loadShader("res/SSAO.frag", graphics::SHADERTYPE_FRAGMENT);
		m_shader.link();

		m_shader.enable();
		m_shader.setUniform("renderedNormal", 0);
		m_shader.setUniform("renderedDepth", 1);
		m_shader.setUniform("noiseTexture", 2);
		m_shader.setUniform("samples", m_samples, m_numSamples);
		m_shader.disable();
	}
	
	void SSAO::cleanup()
	{
		delete[] m_samples;

		m_framebuffer.cleanup();
		m_shader.cleanup();
	}

	void SSAO::setFramebufferSize(unsigned int width, unsigned int height)
	{
		m_framebuffer.cleanup();
		std::vector<graphics::Attachment> attachments;
		attachments.push_back(graphics::ATTACHMENT_COLOR);
		std::vector<graphics::Format> formats;
		formats.push_back(graphics::FORMAT_R32F);
		m_framebuffer.initialize(width, height, 1, attachments.data(), formats.data());
	}

	void SSAO::render(const graphics::Framebuffer& source, unsigned int normalTextureID, unsigned int depthTextureID, const math::Mat4<float>& viewMatrix, const math::Mat4f& projectionMatrix)
	{
		graphics::AttributelessRenderer renderer;

		m_framebuffer.bind();
		renderer.clear(true, false);
		source.use(normalTextureID, 0);
		source.use(depthTextureID, 1);
		m_noiseTexture.use(2);
		m_shader.enable();
		m_shader.setUniform("viewMatrix", viewMatrix);
		m_shader.setUniform("projectionMatrix", projectionMatrix);
		m_shader.setUniform("inverseProjectionMatrix", math::Mat4f::inverse(projectionMatrix));
		renderer.renderTriangleStrip(4);
		m_shader.disable();
	}

}