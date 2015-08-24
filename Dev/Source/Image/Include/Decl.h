#pragma once

#include "FPlatform.h"

#ifdef _IMAGE_EXPORTS
#define IMAGE_API API_EXPORT_CLASS
#define IMAGE_API_F API_EXPORT
#else
#define IMAGE_API API_IMPORT_CLASS
#define IMAGE_API_F API_IMPORT
#endif