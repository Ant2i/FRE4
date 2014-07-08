#include "FreStringUtils.h"
#include <cstdio>
#include <cstdarg>

namespace FRE
{
	namespace Utils
	{
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

			// Absolutely guarantee the buffer is null terminated.
			buffer[size - 1] = '\0';

			return c < (int)size - 1 ? c : (int)size - 1;
		}		
	}
}