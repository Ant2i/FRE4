#pragma once
#include "GLPlatform.h"

#if defined(_WIN32)
#include "WinGLAPI.h"
#elif defined(__APPLE__)
#include "OsxGLAPI.h"
#elif defined(__linux)
#include "X11GLAPI.h"
#endif
