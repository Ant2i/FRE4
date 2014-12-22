#include "FPlatform.h"

#ifdef _OUTPUT_EXPORTS
#define OUTPUT_API API_EXPORT_CLASS
#define OUTPUT_API_F API_EXPORT
#else
#define OUTPUT_API API_IMPORT_CLASS
#define OUTPUT_API_F API_IMPORT
#endif

namespace Output
{
	OUTPUT_API_F void _Assert(const char * exp, const char * file, unsigned line);
	OUTPUT_API_F void _OutputDebugString(const char * p);

	OUTPUT_API_F int SPrintf_s(char * buffer, unsigned size, const char * format, ...);
}
