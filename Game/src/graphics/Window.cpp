#include "Window.h"

#include <glew.h>
#include <glfw3.h>

#include "../debug/Debug.h"

namespace graphics {

	Window::Window() : m_window(nullptr), m_input(this)
	{
	}

	Window::~Window()
	{
	}

	void Window::initialize(const char* title, int width, int height, bool resizable, bool fullscreen, bool vsync)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_RESIZABLE, resizable ? 1 : 0);
		glfwWindowHint(GLFW_SAMPLES, 0);

		m_window = glfwCreateWindow(width, height, title, fullscreen ? monitor : nullptr, nullptr);
		if (m_window == nullptr) {
			debug::crash("Could not create window");
		}

		if (!fullscreen) {
			glfwSetWindowPos(m_window, mode->width / 2 - width / 2, mode->height / 2 - height / 2);
		}
		
		use();
		
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			debug::crash("Could not initialize GLEW");
		}

		glfwSwapInterval(vsync ? 1 : 0);

		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetMouseButtonCallback(m_window, buttonCallback);
		glfwSetCursorPosCallback(m_window, mouseCallback);
	}
	
	void Window::cleanup()
	{
		glfwDestroyWindow(m_window);
	}

	void Window::update()
	{
		m_input.preRefresh();
		glfwPollEvents();
		m_input.postRefresh();
	}

	void Window::swap() const
	{
		glfwSwapBuffers(m_window);
	}

	void Window::use() const
	{
		glfwMakeContextCurrent(m_window);
	}
	
	void Window::bind() const
	{
		int width;
		int height;
		glfwGetFramebufferSize(m_window, &width, &height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	unsigned int Window::getWidth() const
	{
		int width;
		int height;
		glfwGetFramebufferSize(m_window, &width, &height);
		return width;
	}

	unsigned int Window::getHeight() const
	{
		int width;
		int height;
		glfwGetFramebufferSize(m_window, &width, &height);
		return height;
	}

	float Window::getAspectRatio() const
	{
		int width;
		int height;
		glfwGetFramebufferSize(m_window, &width, &height);
		return (float)width / (float)height;
	}

	bool Window::isCloseRequested() const
	{
		return glfwWindowShouldClose(m_window) != 0;
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->m_input.addEvent((unsigned int)key, action != GLFW_RELEASE);
	}
	
	void Window::buttonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->m_input.addEvent((unsigned int)button, action != GLFW_RELEASE);
	}
	
	void Window::mouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* w = (Window*)glfwGetWindowUserPointer(window);
		w->m_input.addEvent((int)xpos, (int)ypos);
	}

}