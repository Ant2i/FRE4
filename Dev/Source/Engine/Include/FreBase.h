#include "FPlatform.h"

#ifdef _FRE4_EXPORTS
#define RE_API API_EXPORT_CLASS
#define RE_API_F API_EXPORT
#else
#define RE_API API_IMPORT_CLASS
#define RE_API_F API_IMPORT
#endif

#ifdef _WIN32
#define	P_BREAKPOINT DebugBreak();
#else
#define P_BREAKPOINT
#endif