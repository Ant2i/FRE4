#pragma once
#include "FPlatform.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN
#include "FOpenGLWindow.h"
#else
#include "FOpenGLOsx.h"
#endif

class GLPlatformContext;
class GLPlatformRenderSurface;

typedef GLPlatformContext * GLPlatformContextP;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

//-----------------------------------------------------------------------------

bool GLPlatformInit(const GLVersion & ver, bool debugMode);

GLPlatformContextP GLContextCreate(GLPlatformContextP hShared = nullptr);
void GLContextDestroy(GLPlatformContextP hContext);

bool GLContextMakeCurrent(GLPlatformContextP hContext);
bool GLContextMakeCurrent(GLPlatformContextP hContext, GLPlatformRenderSurfaceP hSurface);
bool GLContextSwap(GLPlatformContextP hContext, GLPlatformRenderSurfaceP hSurface);

GLPlatformRenderSurfaceP GLSurfaceCreate(GLPlatformContextP hContext, uint64 params);
void GLSurfaceDestroy(GLPlatformRenderSurfaceP hSurface);

void GLSurfaceUpdate(GLPlatformRenderSurfaceP hSurface, unsigned width, unsigned height);

