#pragma once

#include <string>

namespace FRE
{
	typedef long long unsigned int bits64;
	typedef unsigned int bits32;
	typedef unsigned short bits16;
	typedef unsigned char bits8;

#if defined(_WIN32)
	typedef std::wstring sPath;
#else
	typedef std::string sPath;
#endif

}