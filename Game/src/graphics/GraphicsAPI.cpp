#include "GraphicsAPI.h"

#include <glfw3.h>

#include "../debug/Debug.h"

namespace graphics {
	namespace api {
		
		void initialize()
		{
			if (!glfwInit()) {
				debug::crash("Could not initialize GLFW");
			}
		}

		void cleanup()
		{
			glfwTerminate();
		}
	
	}
}