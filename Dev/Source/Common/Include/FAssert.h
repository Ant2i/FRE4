#pragma once

#include "FPlatform.h"
#include "FStringUtils.h"

#include <cstdlib>

#ifdef PLATFORM_WIN
#include "windows.h"
#endif

#ifndef _DEBUG
#define F_ASSERT(x) ((void)0)
#undef F_ASSERTS_ENABLED
#else
#define F_ASSERT(_exp) do { if (!!!(_exp)) FAssert(#_exp, __FILE__, __LINE__); } while (0)
#define F_ASSERTS_ENABLED
#endif

#define F_VERIFY(_exp) do { if (!!!(_exp)) FAssert(#_exp, __FILE__, __LINE__); } while (0)

//----------------

inline void FPrintLocal(const char * str)
{
#ifdef PLATFORM_WIN
	OutputDebugStringA(str);
#else
	printf("%s", str);
#endif
}

inline void FAssert(const char * exp, const char * file, unsigned line)
{
	char buffer[512];
	StringUtils::SPrint(buffer, sizeof(buffer), "%s(%u): Assertion failed: \"%s\"\n", file, line, exp);
	FPrintLocal(buffer);
}