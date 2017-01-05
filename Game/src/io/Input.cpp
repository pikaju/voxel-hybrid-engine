#include "Input.h"

#include <glfw3.h>

#include "../graphics/Window.h"

namespace io {

	Input::Input(graphics::Window* window) : m_window(window), m_events(), m_states()
	{
	}

	Input::~Input()
	{
	}

	void Input::preRefresh()
	{
		m_events.clear();
	}
	
	void Input::postRefresh()
	{
		m_dx = m_x - m_lx;
		m_dy = m_y - m_ly;
		m_lx = m_x;
		m_ly = m_y;
	}

	void Input::addEvent(unsigned int id, bool state)
	{
		m_events[id] = state;
		m_states[id] = state;
	}
	
	void Input::addEvent(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	void Input::setMouseGrabbed(bool grabbed) const
	{
		glfwSetInputMode(m_window->getGLFWWindow(), GLFW_CURSOR, grabbed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}
	
	bool Input::isMouseGrabbed() const
	{
		return glfwGetInputMode(m_window->getGLFWWindow(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
	}

	bool Input::getEvent(unsigned int id, bool state) const
	{
		auto it = m_events.find(id);
		if (it == m_events.end()) return false;
		return it->second == state;
	}

	bool Input::getState(unsigned int id) const
	{
		auto it = m_states.find(id);
		if (it == m_states.end()) return false;
		return it->second;
	}

}