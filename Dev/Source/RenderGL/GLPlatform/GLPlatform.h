#pragma once

#include "FPlatform.h"

#ifdef GL_PLATFORM_EXPORTS
#define GLP_API API_EXPORT_C
#else
#define GLP_API API_IMPORT_C
#endif

class GLPlatformContext;
class GLPlatformRenderSurface;

typedef uint64 GLPlatformContextH;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

//-----------------------------------------------------------------------------

GLP_API bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode);

GLP_API GLPlatformContextH GLPlatformContextCreate(GLPlatformContextH hShared = 0);
GLP_API void GLPlatformContextDestroy(GLPlatformContextH hContext);

GLP_API bool GLPlatformContextMakeCurrent(GLPlatformContextH hContext, GLPlatformRenderSurfaceP pSurface = nullptr);
GLP_API bool GLPlatformContextSwap(GLPlatformContextH hContext, GLPlatformRenderSurfaceP pSurface);

GLP_API GLPlatformContextH GLPlatformGetCurrentContext();

GLP_API GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(uint64 params);
GLP_API void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface);
GLP_API void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height);