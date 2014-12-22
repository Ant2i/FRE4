#include "FPlatform.h"

#ifdef _FRE4_EXPORTS
#define RE_API API_EXPORT_CLASS
#define RE_API_F API_EXPORT
#else
#define RE_API API_IMPORT_CLASS
#define RE_API_F API_IMPORT
#endif

#include "FreTypes.h"