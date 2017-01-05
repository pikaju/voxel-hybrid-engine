#pragma once

#include "../io/Input.h"

struct GLFWwindow;

namespace graphics {

	class Window
	{
	public:
		Window();
		~Window();

		void initialize(const char* title, int width, int height, bool resizable, bool fullscreen, bool vsync);
		void cleanup();

		void update();
		void swap() const;

		void use() const;
		
		void bind() const;
		void clear() const;

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		float getAspectRatio() const;

		bool isCloseRequested() const;

		inline const io::Input& getInput() const { return m_input; }
		inline GLFWwindow* getGLFWWindow() { return m_window; }
	protected:
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void buttonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	private:
		GLFWwindow* m_window;
		io::Input m_input;
	};

}