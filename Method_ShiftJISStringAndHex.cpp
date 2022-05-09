#include "Method_ShiftJISStringAndHex.h"

std::string Method::Method_ShiftJISStringAndHex::ShiftJISStrongToHex(const std::string& str) {
	const char* c = str.c_str();
	std::string hexStr = "";
	std::stringstream ss;
	while (*c != 0) {
		if (_mbclen((unsigned char*)c) == 1)
		{
			ss << std::hex << static_cast<std::uint16_t>(static_cast<unsigned char>(*c));
			ss << " ";
			++c;
		}
		else
		{
			ss << std::hex << static_cast<std::uint16_t>(static_cast<unsigned char>(*c));
			ss << " ";
			ss << std::hex << static_cast<std::uint16_t>(static_cast<unsigned char>(*(c + 1)));
			ss << " ";
			c += 2;
		}
		hexStr.append(ss.str());
		ss.str("");
	}
	return hexStr;
}

std::string Method::Method_ShiftJISStringAndHex::ShiftJISHexToString(const std::string& hexStr) {
	std::string str = "";
	std::istringstream iss;
	int tmp;
	iss = std::istringstream(hexStr);
	while (iss) {
		iss >> std::hex >> tmp;
		str.push_back(tmp);
		tmp = 0;
	}
	return str;
}