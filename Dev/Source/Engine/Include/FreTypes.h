#pragma once

#include "FPlatform.h"
#include <string>

namespace FRE
{

#ifdef PLATFORM_WIN
	#if defined(FRE_UNICODE)
		typedef std::wstring sPath;
	#else
		typedef std::string sPath;
	#endif
#else
	typedef std::string sPath;
#endif

}