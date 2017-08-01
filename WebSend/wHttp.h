#pragma once
#include <string>

namespace winHttp 
{
	bool Get(const std::wstring &wstrUrl, const std::wstring &wstrHeaders, std::wstring &wstrResHeaders, std::string &strResponse, bool sysProxy = true, bool unzip = true);
	bool Post(const std::wstring &wstrUrl, const std::wstring &wstrHeaders, const std::string &strPostData, std::wstring &wstrResHeaders, std::string &strResponse, bool sysProxy = true, bool unzip = true);
}
