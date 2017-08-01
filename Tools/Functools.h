#pragma once
#include <string>

namespace FuncTools
{
	std::string Bin2Hex(const std::string &in, int size = 0);
	std::string Hex2Bin(const std::string &in);

	std::string Trim(const std::string &in);
}

