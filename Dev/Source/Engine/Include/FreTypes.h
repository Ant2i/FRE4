#pragma once

#include "FPlatform.h"
#include <string>

//#define FRE_UNICODE

namespace FRE
{
#if F_CURRENT_PLATFORM == F_PLATFORM_WIN
	#if defined(FRE_UNICODE)
		typedef std::wstring sPath;
	#else
		typedef std::string sPath;
	#endif
#else
	typedef std::string sPath;
#endif

}