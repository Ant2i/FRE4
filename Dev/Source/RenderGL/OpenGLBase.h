#pragma once
#include "FPlatform.h"
#include "GLPlatform.h"

#if defined(PLATFORM_WIN)
#include "WinGLAPI.h"
#elif defined(PLATFORM_OSX)
#include "OsxGLAPI.h"
#elif defined(PLATFORM_LINUX)
#include "X11GLAPI.h"
#endif
