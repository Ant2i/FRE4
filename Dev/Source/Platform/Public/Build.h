#pragma once
#include "Platform.h"

#ifdef PLATFORM_WIN
#define	P_BREAKPOINT DebugBreak();
#else
#define P_BREAKPOINT
#endif
