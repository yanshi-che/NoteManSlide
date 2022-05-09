#pragma once

#include <iostream>
#include <mbstring.h>
#include <sstream>
#include <string>

namespace Method {
	class Method_ShiftJISStringAndHex
	{
	public:
		std::string ShiftJISStrongToHex(const std::string& str);
		std::string ShiftJISHexToString(const std::string& hexStr);
	};
}

