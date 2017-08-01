#pragma once
#include <string>
#include <vector>

namespace StringTools
{
	void SplitString(const std::string &AString, const std::string &ASplitStr, std::vector<std::string> &AStrings);

	std::string StrUpper(const std::string &sIn);
	std::string StrLower(const std::string &sIn);

	std::string Int2String(int n);
	std::string UInt2String(unsigned int n);

	std::string Int642String(long long n);
	unsigned int String2UInt(std::string strNumber);
	int String2Int(std::string strNumber);
}

