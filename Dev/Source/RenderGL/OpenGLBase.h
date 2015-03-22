#pragma once
#include "GLPlatform.h"

#if defined(PLATFORM_WIN)
#include "OpenGLWindowsAPI.h"
#elif defined(PLATFORM_OSX)
#include "OpenGLOsxAPI.h"
#elif defined(PLATFORM_LINUX)
//#include "OpenGLX11API.h"
#endif

#include "OpenGLX11API.h"
