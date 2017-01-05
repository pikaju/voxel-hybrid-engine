#include "Debug.h"

#include <iostream>

#include "../io/Log.h"

namespace debug {

	void crash(const std::string& message)
	{
		io::log(message, io::LOGTYPE_ERROR);
		int k;
		std::cin >> k;
	}

}