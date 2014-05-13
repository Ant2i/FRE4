#include "FPlatform.h"

#ifdef _FRE4_EXPORTS
#define RE_API API_EXPORT_CLASS
#else
#define RE_API API_IMPORT_CLASS
#endif