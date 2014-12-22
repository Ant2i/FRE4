#include "FOutput.h"

#include <cstdlib>
#include <stdio.h>
#include <stdarg.h>

#ifdef PLATFORM_WIN
#include "windows.h"
#endif

namespace Output
{
	void DebugBreakIfDebugging(void)
	{
		static const char * breakOnAssert = getenv("FRE_BREAK_ON_ASSERT");

		if (breakOnAssert)
		{
			P_BREAKPOINT
		}
	}

	void _Assert(const char *pExp, const char *pFile, unsigned line)
	{
		char buf[512];
		SPrintf_s(buf, sizeof(buf), "%s(%u): Assertion failed: \"%s\"\n", pFile, line, pExp);

		_OutputDebugString(buf);
		DebugBreakIfDebugging();
	}

	void _OutputDebugString(const char *p)
	{
#ifdef PLATFORM_WIN
		OutputDebugStringA(p);
#else
		printf("%s", p);
#endif
	}

	//----------------------------------------------------------------------------

	int SPrintf_s(char * buffer, unsigned size, const char * format, ...)
	{
		if (!size)
			return 0;

		va_list args;
		va_start(args, format);
		int c = vsnprintf(buffer, size, format, args);
		va_end(args);

		if (c < 0)
		{
			buffer[0] = '\0';
			return 0;
		}

		buffer[size - 1] = '\0';
		return c < (int)size - 1 ? c : (int)size - 1;
	}
}