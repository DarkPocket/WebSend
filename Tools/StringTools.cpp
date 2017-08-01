#include "StringTools.h"
#include <algorithm>


namespace StringTools
{
	using namespace std;
	void SplitString(const string &AString, const string &ASplitStr, vector<string> &AStrings)
	{
		const char *sdata = AString.c_str();
		const char *ssplit = ASplitStr.c_str();
		unsigned int i = 0, j = 0, iSizeA = AString.length(), iSizeB = ASplitStr.length();
		AStrings.clear();
		while (i < iSizeA) {
			if (i + iSizeB > iSizeA) {
				AStrings.push_back(AString.substr(j));
				j = i;
				break;
			}
			if (memcmp(&(sdata[i]), ssplit, iSizeB) == 0) {
				AStrings.push_back(AString.substr(j, i - j));
				j = i + iSizeB;
				i += iSizeB;
			} else
				++i;
		}
		if (j < i)
			AStrings.push_back(AString.substr(j));
		return;
	}

	std::string StrUpper( const std::string &sIn )
	{
		std::string sOut(sIn);
		std::transform(sIn.begin(), sIn.end(), sOut.begin(), toupper);
		return sOut;
	}

	std::string StrLower( const std::string &sIn )
	{
		std::string sOut(sIn);
		std::transform(sIn.begin(), sIn.end(), sOut.begin(), tolower);
		return sOut;
	}

	std::string Int2String(int n)
	{
		char cNumber[16] = { 0 };
		sprintf_s(cNumber, sizeof(cNumber), "%d", n);
		return std::string(cNumber);
	}


	std::string UInt2String( unsigned int n )
	{
		char cNumber[16] = {0};
		sprintf_s( cNumber, sizeof(cNumber), "%u", n );
		return std::string(cNumber);
	}

	std::string Int642String(long long n)
	{
		char cNumber[32] = { 0 };
		sprintf_s(cNumber, sizeof(cNumber), "%lld", n);
		return std::string(cNumber);
	}

	unsigned int String2UInt( std::string strNumber )
	{
		unsigned int n;
		sscanf_s(strNumber.data(), "%u", &n);
		return n;
	}

	int String2Int(std::string strNumber)
	{
		int n;
		sscanf_s(strNumber.data(), "%d", &n);
		return n;
	}

}