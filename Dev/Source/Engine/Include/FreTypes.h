#pragma once

#include "FPlatformTypes.h"
#include <string>

namespace FRE
{
#if defined(_WIN32)
	#ifdef UNICODE
		typedef std::wstring sPath;
	#else
		typedef std::string sPath;
	#endif
#else
	typedef std::string sPath;
#endif

}