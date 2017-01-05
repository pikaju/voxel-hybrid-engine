#include "Framebuffer.h"

#include <glew.h>

#include "../../debug/Debug.h"

namespace graphics {

	namespace attachment {

		unsigned int getGLAttachment(const Attachment& attachment, unsigned int index)
		{
			switch (attachment) {
			case ATTACHMENT_COLOR: return GL_COLOR_ATTACHMENT0 + index;
			case ATTACHMENT_DEPTH: return GL_DEPTH_ATTACHMENT;
			}
			return 0;
		}

	}

	Framebuffer::Framebuffer() : m_width(0), m_height(0), m_textures(nullptr), m_numTextures(0), m_framebuffer(0), m_numColorAttachments(0), m_numSamples(0)
	{
	}
	
	Framebuffer::~Framebuffer()
	{
	}

	void Framebuffer::initialize(unsigned int width, unsigned int height, unsigned int numTextures, const Attachment* attachments, const Format* formats, unsigned int numSamples)
	{
		m_width = width;
		m_height = height;
		m_numTextures = numTextures;
		m_numSamples = numSamples;
		m_textures = new unsigned int[m_numTextures];
		glGenTextures(m_numTextures, m_textures);
		
		for (unsigned int i = 0; i < m_numTextures; i++) {
			unsigned int textureType = m_numSamples != 0 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;

			glBindTexture(textureType, m_textures[i]);
			glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, attachments[i] == ATTACHMENT_COLOR ? GL_LINEAR : GL_NEAREST);
			glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, attachments[i] == ATTACHMENT_COLOR ? GL_LINEAR : GL_NEAREST);
			glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(textureType, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			if (textureType == GL_TEXTURE_2D_MULTISAMPLE) {
				glTexImage2DMultisample(textureType, m_numSamples, format::getGLInternalFormat(formats[i]), m_width, m_height, false);
				glEnable(GL_MULTISAMPLE);
			}
			else {
				glTexImage2D(textureType, 0, format::getGLInternalFormat(formats[i]), m_width, m_height, 0, format::getGLFormat(formats[i]), format::getGLType(formats[i]), nullptr);
			}
		}

		glGenFramebuffers(1, &m_framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		std::vector<unsigned int> drawBuffers;
		
		for (unsigned int i = 0; i < m_numTextures; i++) {
			drawBuffers.push_back(attachment::getGLAttachment(attachments[i], m_numColorAttachments));
			glFramebufferTexture(GL_FRAMEBUFFER, drawBuffers.back(), m_textures[i], 0);
			if (attachments[i] == ATTACHMENT_DEPTH) {
				drawBuffers[i] = GL_NONE;
			}
			if (attachments[i] == ATTACHMENT_COLOR) {
				m_numColorAttachments++;
			}
		}
		glDrawBuffers(drawBuffers.size(), drawBuffers.data());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			debug::crash("Failed to create framebuffer");
		}
	}

	void Framebuffer::cleanup()
	{
		glDeleteTextures(m_numTextures, m_textures);
		glDeleteFramebuffers(1, &m_framebuffer);
		delete[] m_textures;
	}

	void Framebuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
		glViewport(0, 0, m_width, m_height);
	}

	void Framebuffer::use(unsigned int texture, unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textures[texture]);
	}

	void Framebuffer::blitTo(const Framebuffer& framebuffer) const
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebuffer);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer.m_framebuffer);
		for (unsigned int i = 0; i < m_numColorAttachments; i++) {
			glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
			glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
			glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, framebuffer.m_width, framebuffer.m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		}
		glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, framebuffer.m_width, framebuffer.m_height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

}