#include "FreAssert.h"
#include "FreStringUtils.h"
#include <cstdlib>
#include <stdio.h>

#ifdef PLATFORM_WIN
#include "windows.h"
#endif

void _FRE_DebugBreakIfDebugging(void)
{
	static const char * breakOnAssert = getenv("FRE_BREAK_ON_ASSERT");

	if (breakOnAssert || IsDebug())
	{
		P_BREAKPOINT
	}
}

void _FRE_Assert(const char *pExp, const char *pFile, unsigned line)
{
	char buf[512];
	FRE::Utils::SPrintf_s(buf, sizeof(buf), "%s(%u): Assertion failed: \"%s\"\n", pFile, line, pExp);
	
	_FRE_OutputDebugString(buf);
	_FRE_DebugBreakIfDebugging();
}

void _FRE_OutputDebugString(const char *p)
{
#ifdef PLATFORM_WIN
	OutputDebugStringA(p);
#else
    printf("%s", p);
#endif
}