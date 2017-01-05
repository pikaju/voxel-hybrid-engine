#include "Attribute.h"

#include <glew.h>

#include "../debug/Debug.h"

namespace graphics {
	namespace attribute {

		unsigned int getGLType(const Type& type)
		{
			switch (type) {
			case TYPE_FLOAT: return GL_FLOAT; break;
			case TYPE_DOUBLE: return GL_DOUBLE; break;
			case TYPE_UNSIGNED_BYTE: return GL_UNSIGNED_BYTE; break;
			case TYPE_UNSIGNED_INT: return GL_UNSIGNED_INT; break;
			default: debug::crash("Invalid type: " + std::to_string(type)); break;
			}
			return 0;
		}

		unsigned int getGLTypeSize(const Type& type)
		{
			switch (type) {
			case TYPE_FLOAT: return 4; break;
			case TYPE_DOUBLE: return 8; break;
			case TYPE_UNSIGNED_BYTE: return 1; break;
			case TYPE_UNSIGNED_INT: return 4; break;
			default: debug::crash("Invalid type: " + std::to_string(type)); break;
			}
			return 0;
		}

	}
}