#include "Functools.h"
#include <algorithm>


namespace FuncTools
{
	#define int2hex(a) ((a)<10?(a)+'0':(a)+'a'-10)
	#define hex2int(x) ((x)<='9'?(x)-'0':((x)<='F'?(x)-'A'+10:(x)-'a'+10))


	static char char2print(char a)
	{
		if ((a >= 32) && (a <= 126))return a;
		return '.';
	}

	static std::string bin2print(const std::string &in, int size)
	{
		const char *buf = in.c_str();
		std::string out("");
		std::string inp("");
		for (unsigned int i = 0; i < (unsigned)size; i++)
		{
			unsigned char tmp = i < in.length() ? buf[i] : ' ';
			inp += char2print(tmp);
			out += i < in.length() ? int2hex(tmp >> 4) : ' ';
			out += i < in.length() ? int2hex(tmp & 0x0f) : ' ';
			out += ' ';
			if ((i % 4) == 3) out += ' ';
		}
		out += inp + "\r\n";
		return out;
	}

	std::string Bin2Hex( const std::string &in, int size /*= 0*/ )
	{
		const char *buf = in.c_str();
		std::string out("");
		int i = 0, j = 0;
		for (i; (unsigned)i < in.length(); i++) {
			char tmp = buf[i];
			if (!size) {
				out += int2hex((tmp >> 4) & 0x0f);
				out += int2hex(tmp & 0x0f);
			} else {
				out += bin2print(in.substr(i, size), size);
				i += size - 1;
			}
		}

		return out;
	}

	std::string Hex2Bin(const std::string &in)
	{
		const char *buf = in.c_str();
		std::string out("");
		int i = 0;
		for (i; (unsigned)i < in.length(); i += 2)
		{
			if (((buf[i] >= '0' && buf[i] <= '9') || (buf[i] >= 'a' && buf[i] <= 'f') || (buf[i] >= 'A' && buf[i] <= 'F'))
				&& ((buf[i + 1] >= '0' && buf[i + 1] <= '9') || (buf[i + 1] >= 'a' && buf[i + 1] <= 'f') || (buf[i + 1] >= 'A' && buf[i + 1] <= 'F'))) {
				char tmp = hex2int(buf[i]);
				char tmp1 = hex2int(buf[i + 1]);
				tmp = (tmp << 4) + tmp1;
				out += tmp;
			}
		}
		return out;
	}

	std::string Trim(const std::string &in)
	{
		std::string::size_type pos_begin, pos_end;

		for (pos_begin = 0; pos_begin < in.length(); pos_begin++) {
			if (in[pos_begin] == ' ') {
				continue;
			}
			break;
		}

		for (pos_end = in.length() - 1; pos_end >= pos_begin; pos_end--) {
			if (in[pos_end] == ' ') {
				continue;
			}
			break;
		}
		if (pos_begin > in.length()) return "";
		return in.substr(pos_begin, pos_end - pos_begin + 1);
	}
}