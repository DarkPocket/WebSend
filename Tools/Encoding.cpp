
#include "Encoding.h"
#include <Windows.h>

namespace Encode
{
	std::wstring U8toU(const std::string &u8)
	{
		if (0 == u8.length()) return L"";

		DWORD dwUnicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, u8.data(), -1, NULL, 0);
		if (0 == dwUnicodeLen) {
			return L"";
		}

		wchar_t *pWstr = new wchar_t[dwUnicodeLen + 1];
		memset(pWstr, 0, (dwUnicodeLen + 1) * sizeof(wchar_t));

		::MultiByteToWideChar(CP_UTF8, 0, u8.data(), -1, (LPWSTR)pWstr, dwUnicodeLen);
		std::wstring wstrRet(pWstr);
		delete  pWstr;
		return  wstrRet;
	}

	std::string UtoU8(const std::wstring &u)
	{
		if (0 == u.length()) return "";

		DWORD dwU8Len = WideCharToMultiByte(CP_UTF8, 0, u.data(), -1, NULL, 0, NULL, NULL);

		char *pStr = new char[dwU8Len + 1];
		memset((void *)pStr, 0, sizeof(char)*(dwU8Len + 1));

		WideCharToMultiByte(CP_UTF8, 0, u.data(), -1, pStr, dwU8Len, NULL, NULL);
		std::string strRet(pStr);
		delete[]pStr;
		return strRet;
	}

	std::wstring AtoU(const std::string &a)
	{
		if (0 == a.length()) return L"";

		DWORD dwUnicodeLen = ::MultiByteToWideChar(CP_ACP, 0, a.data(), -1, NULL, 0);
		if (0 == dwUnicodeLen) {
			return L"";
		}

		wchar_t *pWstr = new wchar_t[dwUnicodeLen + 1];
		memset(pWstr, 0, (dwUnicodeLen + 1) * sizeof(wchar_t));

		::MultiByteToWideChar(CP_ACP, 0, a.data(), -1, (LPWSTR)pWstr, dwUnicodeLen);
		std::wstring wstrRet(pWstr);
		delete  pWstr;
		return  wstrRet;
	}

	std::string UtoA(const std::wstring &u)
	{
		if (0 == u.length()) return "";

		DWORD dwU8Len = WideCharToMultiByte(CP_ACP, 0, u.data(), -1, NULL, 0, NULL, NULL);

		char *pStr = new char[dwU8Len + 1];
		memset((void *)pStr, 0, sizeof(char)*(dwU8Len + 1));

		WideCharToMultiByte(CP_ACP, 0, u.data(), -1, pStr, dwU8Len, NULL, NULL);
		std::string strRet(pStr);
		delete[]pStr;
		return strRet;
	}
}
