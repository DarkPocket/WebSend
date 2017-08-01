#include "stdafx.h"
#include "wHttp.h"
#include <Windows.h>
#include <wininet.h>
#pragma comment(lib, "WININET.LIB")
#include <iostream>
namespace winHttp {
	//static std::wstring wstrUserAgent = L"Testing";
	static std::wstring wstrUserAgent = L"Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36";
	static std::wstring wstrMethonGet = L"GET";
	static std::wstring wstrMethonPost = L"POST";
	static const int URL_PARSE_BUF_SIZE = 2048;

	bool ParseURL(const wchar_t *url, std::wstring &host, std::wstring &path, std::wstring &obj, WORD &port)
	{
		wchar_t szHostName[URL_PARSE_BUF_SIZE] = { 0 };
		wchar_t szURLPath[URL_PARSE_BUF_SIZE] = { 0 };
		wchar_t szURLExtra[URL_PARSE_BUF_SIZE] = { 0 };

		URL_COMPONENTS urlComp = { 0 };
		urlComp.dwStructSize = sizeof(urlComp);
		urlComp.lpszHostName = szHostName;
		urlComp.dwHostNameLength = URL_PARSE_BUF_SIZE;
		urlComp.lpszUrlPath = szURLPath;
		urlComp.dwUrlPathLength = URL_PARSE_BUF_SIZE;
		urlComp.lpszExtraInfo = szURLExtra;
		urlComp.dwExtraInfoLength = URL_PARSE_BUF_SIZE;
		urlComp.dwSchemeLength = -1;

		if (InternetCrackUrl(url, wcslen(url), 0, &urlComp)) {
			host.assign(szHostName);
			path.assign(szURLPath);
			obj.assign(szURLExtra);
			port = urlComp.nPort;
			return true;
		}
		return false;
	}

	bool Get(const std::wstring &wstrUrl, const std::wstring &wstrHeaders, std::wstring &wstrResHeaders, std::string &strResponse, bool sysProxy, bool unzip)
	{
		HINTERNET hInternet = NULL, hConnect = NULL, hOpenRequest = NULL;
		std::wstring wstrHost, wstrPath, wstrObj;
		DWORD dwSize = 0;
		WORD wPort = 0;

		if (!ParseURL(wstrUrl.data(), wstrHost, wstrPath, wstrObj, wPort)) {
			return false;
		}

		if (sysProxy)
			hInternet = InternetOpen(wstrUserAgent.data(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, INTERNET_FLAG_DONT_CACHE);
		else
			hInternet = InternetOpen(wstrUserAgent.data(), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, INTERNET_FLAG_DONT_CACHE);
		if (hInternet == NULL) return false;
		
		if (NULL == (hConnect = InternetConnect(hInternet, wstrHost.data(), wPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0))) {
			goto clean;
		}
		
		DWORD_PTR dwFlag = (wPort == 443) ? INTERNET_FLAG_SECURE : 0;
		dwFlag |= INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_NO_COOKIES;
		if (NULL == (hOpenRequest = HttpOpenRequest(hConnect, wstrMethonGet.data(), (wstrPath + wstrObj).data(), L"HTTP/1.1", NULL, NULL, dwFlag, 0))) {
			goto clean;
		}

		if (unzip) {
			BOOL bUnzip = TRUE;
			InternetSetOption(hOpenRequest, INTERNET_OPTION_HTTP_DECODING, &bUnzip, sizeof(bUnzip));
		}
		

		if (FALSE == HttpSendRequest(hOpenRequest, wstrHeaders.data(), wstrHeaders.length(), NULL, 0)) {
			goto clean;
		}
		
		//header
		HttpQueryInfo(hOpenRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &dwSize, NULL);
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			wchar_t *wszHeaders = new wchar_t[dwSize / sizeof(wchar_t)];
			if (HttpQueryInfo(hOpenRequest, HTTP_QUERY_RAW_HEADERS_CRLF, wszHeaders, &dwSize, NULL))
				wstrResHeaders.append(wszHeaders, dwSize / sizeof(wchar_t));
			delete[] wszHeaders;
		}

		//body
		char szBuffer[4096] = { 0 };
		while (InternetReadFile(hOpenRequest, szBuffer, sizeof(szBuffer), &dwSize) && dwSize > 0) {
			strResponse.append(szBuffer, dwSize);
		}

		BOOL BRet;
		DWORD dwError;
		if (hOpenRequest) {
			BRet = InternetCloseHandle(hOpenRequest);
			if (!BRet) {
				dwError = GetLastError();
			}
		}
		if (hConnect) {
			BRet = InternetCloseHandle(hConnect);
			if (!BRet) {
				dwError = GetLastError();
			}
		}
		if (hInternet) {
			BRet = InternetCloseHandle(hInternet);
			if (!BRet) {
				dwError = GetLastError();
			}
		}

		return true;

	clean:
//		long int err= GetLastError();
//		std::cout << "GetLastError()=" << err ;
		if (hOpenRequest) InternetCloseHandle(hOpenRequest);
		if (hConnect) InternetCloseHandle(hConnect);
		if (hInternet) InternetCloseHandle(hInternet);
		return false;
	}

	bool Post(const std::wstring &wstrUrl, const std::wstring &wstrHeaders, const std::string &strPostData, std::wstring &wstrResHeaders, std::string &strResponse, bool sysProxy, bool unzip)
	{
		HINTERNET hInternet = NULL, hConnect = NULL, hOpenRequest = NULL;
		std::wstring wstrHost, wstrPath, wstrObj;
		DWORD dwSize = 0;
		WORD wPort = 0;

		if (!ParseURL(wstrUrl.data(), wstrHost, wstrPath, wstrObj, wPort)) {
			return false;
		}

		if (sysProxy)
			hInternet = InternetOpen(wstrUserAgent.data(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		else
			hInternet = InternetOpen(wstrUserAgent.data(), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (hInternet == NULL) return false;

		if (NULL == (hConnect = InternetConnect(hInternet, wstrHost.data(), wPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0))) {
			return false;
		}

		DWORD_PTR dwFlag = (wPort == 443) ? INTERNET_FLAG_SECURE| INTERNET_FLAG_DONT_CACHE : INTERNET_FLAG_DONT_CACHE;
		if (NULL == (hOpenRequest = HttpOpenRequest(hConnect, wstrMethonPost.data(), (wstrPath + wstrObj).data(), NULL, NULL, NULL, dwFlag, 0))) {
			return false;
		}

		if (unzip) {
			BOOL bUnzip = TRUE;
			InternetSetOption(hOpenRequest, INTERNET_OPTION_HTTP_DECODING, &bUnzip, sizeof(bUnzip));
		}

		if (FALSE == HttpSendRequest(hOpenRequest, wstrHeaders.data(), wstrHeaders.length(), (LPVOID)strPostData.data(), strPostData.length())) {
			return false;
		}

		//header
		HttpQueryInfo(hOpenRequest, HTTP_QUERY_RAW_HEADERS_CRLF, NULL, &dwSize, NULL);
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
			wchar_t *wszHeaders = new wchar_t[dwSize / sizeof(wchar_t)];
			if (HttpQueryInfo(hOpenRequest, HTTP_QUERY_RAW_HEADERS_CRLF, wszHeaders, &dwSize, NULL))
				wstrResHeaders.append(wszHeaders, dwSize / sizeof(wchar_t));
			delete[] wszHeaders;
		}

		//body
		char szBuffer[4096] = { 0 };
		while (InternetReadFile(hOpenRequest, szBuffer, sizeof(szBuffer), &dwSize) && dwSize > 0) {
			strResponse.append(szBuffer, dwSize);
		}
		return true;
	}
}