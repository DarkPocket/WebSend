#pragma once
#include <string>
/*
ʹ��win32��
*/
namespace Encode
{
	std::string UtoA(const std::wstring &u);
	std::string UtoU8(const std::wstring &u);
	std::wstring AtoU(const std::string &a);
	std::wstring U8toU(const std::string &u8);
}
