#pragma once

namespace graphics {

	enum Format
	{
		FORMAT_RGBA8,
		FORMAT_RGB32F,
		FORMAT_RGB8,
		FORMAT_R32F,
		FORMAT_R8,
		FORMAT_DEPTH16,
		FORMAT_DEPTH24,
		FORMAT_DEPTH32
	};

	namespace format {

		extern unsigned int getGLInternalFormat(const Format& format);
		extern unsigned int getGLFormat(const Format& format);
		extern unsigned int getGLType(const Format& format);

	}

	class Texture
	{
	public:
		Texture();
		~Texture();

		void initialize(unsigned int width, unsigned int height, const Format& format, const void* pixels);
		void cleanup();

		void use(unsigned int slot = 0);
	private:
		unsigned int m_id;
		unsigned int m_width;
		unsigned int m_height;
	};

}