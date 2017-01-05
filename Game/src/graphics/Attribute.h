#pragma once

namespace graphics {

	enum Type
	{
		TYPE_FLOAT, TYPE_DOUBLE, TYPE_UNSIGNED_BYTE, TYPE_UNSIGNED_INT
	};

	class Attribute
	{
	public:
		Type type;
		unsigned int amount;
		bool normalized;

		Attribute(const Type& type, unsigned int amount, bool normalized = false) : type(type), amount(amount), normalized(normalized) {  }
		~Attribute() {  }
	};

	namespace attribute {

		extern unsigned int getGLType(const Type& type);
		extern unsigned int getGLTypeSize(const Type& type);

	}
}