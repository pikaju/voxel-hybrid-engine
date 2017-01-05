#pragma once

#include <vector>

#include "Texture.h"

namespace graphics {

	enum Attachment
	{
		ATTACHMENT_COLOR,
		ATTACHMENT_DEPTH,
		ATTACHMENT_COUNT
	};

	namespace attachment {

		extern unsigned int getGLAttachment(const Attachment& attachment, unsigned int index);

	}

	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		void initialize(unsigned int width, unsigned int height, unsigned int numTextures, const Attachment* attachments, const Format* formats, unsigned int numSamples = 0);
		void cleanup();

		void bind();
		void use(unsigned int texture = 0, unsigned int slot = 0) const;

		void blitTo(const Framebuffer& framebuffer) const;

		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }
		inline float getAspectRatio() const { return (float)m_width / (float)m_height; }
	private:
		unsigned int m_width;
		unsigned int m_height;

		unsigned int* m_textures;
		unsigned int m_numTextures;
		unsigned int m_framebuffer;

		unsigned int m_numColorAttachments;

		unsigned int m_numSamples;
	};

}