#pragma once

#include <string>

namespace io {

	enum LogType
	{
		LOGTYPE_INFO,
		LOGTYPE_WARNING,
		LOGTYPE_ERROR
	};

	extern void log(const std::string& message, const LogType& type = LOGTYPE_INFO);

}