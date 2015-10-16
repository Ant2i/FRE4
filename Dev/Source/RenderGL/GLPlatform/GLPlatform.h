#pragma once

#ifdef _WIN32
#define API_EXPORT_C extern "C" __declspec(dllexport)
#define API_IMPORT_C extern "C" __declspec(dllimport)
#else
#define API_EXPORT_C extern "C"
#define API_IMPORT_C extern "C"
#endif

#ifdef GL_PLATFORM_EXPORTS
#define GLCP_API API_EXPORT_C
#else
#define GLCP_API API_IMPORT_C
#endif

class GLPlatformContext;
class GLPlatformRenderSurface;

typedef GLPlatformContext * GLPlatformContextP;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

typedef unsigned long long int GLPixelFormatH;

//-----------------------------------------------------------------------------

struct SurfaceDesc
{
	SurfaceDesc() :
		PlatformData(0),
		External(true)
	{

	}

	unsigned long long int PlatformData;
	bool External;
};

struct PixelFormatDesc
{
	bool Stereo;
};

//-----------------------------------------------------------------------------

GLCP_API bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode);

GLCP_API GLPixelFormatH FindPixelFormat(const PixelFormatDesc & pixelFormatDesc);

GLCP_API GLPlatformContextP GLPlatformContextCreate(GLPixelFormatH hPixelFormat, GLPlatformContextP pSharedContext = nullptr);
GLCP_API void GLPlatformContextDestroy(GLPlatformContextP pContext);

GLCP_API bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface = nullptr);
GLCP_API bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface);
GLCP_API GLPlatformContextP GLPlatformGetCurrentContext();

GLCP_API GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLPixelFormatH hPixelFormat, const SurfaceDesc & surfaceDesc);
GLCP_API void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface);
GLCP_API void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height);