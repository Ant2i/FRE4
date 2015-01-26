#pragma once

#include "FPlatform.h"

#ifdef GL_PLATFORM_EXPORTS
#define GLP_API extern "C" __declspec(dllexport)
#else
#define GLP_API extern "C" __declspec(dllimport)
#endif

class GLPlatformContext;
class GLPlatformRenderSurface;

typedef GLPlatformContext * GLPlatformContextP;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

//-----------------------------------------------------------------------------

GLP_API bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode);

GLP_API GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP pShared = nullptr);
GLP_API void GLPlatformContextDestroy(GLPlatformContextP pContext);

GLP_API bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface = nullptr);
GLP_API bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface);

GLP_API GLPlatformContextP GLPlatformGetCurrentContext();

GLP_API GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(uint64 params);
GLP_API void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface);
GLP_API void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height);