#include "Log.h"

#include <iostream>

#include "../debug/Debug.h"

namespace io {

	void log(const std::string& message, const LogType& type)
	{
		switch (type)
		{
		case LOGTYPE_INFO: std::cout << "Info> "; break;
		case LOGTYPE_WARNING: std::cout << "Warning> "; break;
		case LOGTYPE_ERROR: std::cout << "Error> "; break;
		default: debug::crash("Invalid log type: " + std::to_string(type)); break;
		}
		std::cout << message << std::endl;
	}

}