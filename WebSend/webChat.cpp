/************************************************************************

 *文件名：  $webChat$
 *版本号：  V1.0.0.0
 *唯一标识：$guid10$
 *创建人：  $zhouwei$
 *创建时间：$20170801$
 *描述：
 *  利用wininet对服务器发送get post请求
 *   webxxx函数
 *修改标记
 *修改时间：$time$
 *修改人： $username$
 *版本号： V1.0.0.0
 *描述：
 *
/**************************************************************************/


#include "stdafx.h"



#include <iostream>
#include <map>
#include "Encoding.h"
#include "wHttp.h"

using namespace std;


void  webHeaderSet(map< string, string> &mapHeader, const  string & key, const  string & value);
void  webHttp(map<string, string> &mapHeader);
bool webGet(const std::wstring &wstrUrl, const std::string &strHeaders, std::wstring &wstrResHeaders, std::string &strResponse);
bool webPost(const std::wstring &wstrUrl, const std::string &strHeaders, const std::string &strPostData, std::wstring &wstrResHeaders, std::string &strResponse);


void  webHttp(map< string, string> &mapHeader)
{
	//zhouwei   20170801
	webHeaderSet(mapHeader, "Accept-Encoding", "gzip, deflate, sdch");
	webHeaderSet(mapHeader, "Connection", "keep-alive");
	webHeaderSet(mapHeader, "Accept-Language", "zh-CN,zh;q=0.8,ko;q=0.6");

}

void  webHeaderSet(map<string, string> &mapHeader, const std::string & key, const std::string & value)
{
	mapHeader.insert(make_pair(key, value));
}

bool webGet(const std::wstring &wstrUrl, const std::string &strHeaders, std::wstring &wstrResHeaders, std::string &strResponse)
{

	if (!winHttp::Get(wstrUrl, Encode::AtoU(strHeaders), wstrResHeaders, strResponse, true, true))
	{
		return false;
	}
	return  true;
}
bool webPost(const std::wstring &wstrUrl, const std::string &strHeaders, const std::string &strPostData, std::wstring &wstrResHeaders, std::string &strResponse)
{
	if (!winHttp::Post(wstrUrl, Encode::AtoU(strHeaders), strPostData, wstrResHeaders, strResponse, true, true))
	{
		return false;
	}
	return  true;
}


int webTest(std::wstring url)
{
	//设置c++ wcout显示中文
	std::wcout.imbue(std::locale("chs"));


	std::string  strHeader;
	std::string  strResponse;
	std::wstring wstrResponse;
	std::wstring wstrResponseHeader;

	std::map<std::string, std::string> mapHeader;

	//设置mapHeader 并且转化为  strHeader
	webHttp(mapHeader);
	webHeaderSet(mapHeader, "Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");

	std::map<std::string, std::string>::iterator itor = mapHeader.begin();
	for (itor = mapHeader.begin(); itor != mapHeader.end(); itor++) {
		strHeader += itor->first + ": " + itor->second + "\r\n";
	}
	if (strHeader.length())
		strHeader += "\r\n";



	if (!webGet(url, strHeader, wstrResponseHeader, strResponse))
	{
		return -1;
	}

	// post 请求
	/*
	const std::string data;
	if (!webPost(url, strHeader, data, wstrResponseHeader, strResponse)) {
		return false;
	}
	*/


	strHeader = Encode::UtoU8(wstrResponseHeader);
	wstrResponse = Encode::U8toU(strResponse);


	std::wcout << "	header=  \n" << wstrResponseHeader << std::endl;
	std::wcout << "response=  \n" << wstrResponse << std::endl;


	//	std::cout << "	header=  \n" << strHeader << std::endl;
	//	std::wcout << "response=  \n" << wstrResponse << std::endl;

	return 0;

}

int main()
{

	std::wstring url = L"http://172.16.31.244:3000/";


	webTest(url);

	std::cout << "    " << std::endl;

	system("pause");
	return 0;

}