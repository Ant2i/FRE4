#pragma once

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN
#include "FOpenGLWindows.h"
#else
#include "FOpenGLMac.h"
#endif

class GLPlatformContext;
class GLPlatformRenderSurface;

typedef GLPlatformContext * GLPlatformContextP;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

//-----------------------------------------------------------------------------

bool GLPlatformInit(const GLVersion & ver, bool debugMode);

GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP hShared = nullptr);
void GLPlatformContextDestroy(GLPlatformContextP hContext);

bool GLPlatformContextMakeCurrent(GLPlatformContextP hContext);
bool GLPlatformContextMakeCurrent(GLPlatformContextP hContext, GLPlatformRenderSurfaceP hSurface);
bool GLPlatformContextSwap(GLPlatformContextP hContext, GLPlatformRenderSurfaceP hSurface);

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLPlatformContextP hContext, uint64 params);
void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP hSurface);
void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP hSurface, unsigned width, unsigned height);