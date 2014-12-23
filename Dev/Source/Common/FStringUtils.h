#pragma once

#include <cstdio>
#include <cstdarg>

class StringUtils
{
public:
	static int SPrint(char * buffer, unsigned size, const char * format, ...)
	{
		if (!size)
			return 0;

		va_list args;
		va_start(args, format);

#ifdef WIN32
		int c = vsnprintf_s(buffer, size, size, format, args);
#else
		int c = vsnprintf(buffer, size, format, args); 
#endif
		va_end(args);

		if (c < 0)
		{
			buffer[0] = '\0';
			return 0;
		}

		buffer[size - 1] = '\0';
		return c < (int)size - 1 ? c : (int)size - 1;
	}
};