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

struct GLPlatformContext;
struct GLPlatformRenderSurface;

typedef GLPlatformContext * GLPlatformContextP;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

typedef unsigned long long int GLSurfaceFormatH;

//-----------------------------------------------------------------------------

typedef void * GLPContext;
typedef void * GLPSurface;
typedef void * GLPConfig;
typedef void * GLPNativeWindowType;

struct PGLSurfaceDesc
{
	
};

struct PGLContextDesc
{

};

struct PGLConfigDesc
{
	int RedSize;
	int GreenSize;
	int BlueSize;
	int DepthSize;
	int Stereo;
};

GLCP_API bool PGLInitialize(unsigned * oMajorVer, unsigned * oMinorVer, bool iDebugMode);
GLCP_API void PGLTerminate();

GLCP_API PGLConfigDesc PGLDefaultConfigDesc();
GLCP_API GLPConfig PGLChooseConfig(const PGLConfigDesc * iDesc);
GLCP_API bool PGLGetConfigDesc(GLPConfig iConfig, PGLConfigDesc * oDesc);

GLCP_API GLPContext PGLContextCreate(GLPConfig iConfig, GLPContext iSharedContext = nullptr, const PGLContextDesc * iDesc = nullptr);
GLCP_API void PGLContextDestroy(GLPContext iContext);

GLCP_API GLPSurface PGLSurfaceCreate(GLPConfig iConfig, GLPNativeWindowType iWindow, const PGLSurfaceDesc * iDesc = nullptr);
GLCP_API void PGLSurfaceDestroy(GLPSurface iSurface);

GLCP_API bool PGLContextMakeCurrent(GLPContext iContext, GLPSurface iSurface = nullptr);
GLCP_API bool PGLSwapBuffers(GLPSurface iSurface);

GLCP_API GLPContext PGLGetCurrentContext();


//------------------------------------------------------------------------------

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

struct SurfaceFormatDesc
{
	bool Stereo;
};

//-----------------------------------------------------------------------------

GLCP_API bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode);

GLCP_API GLSurfaceFormatH FindSurfaceFormat(const SurfaceFormatDesc & formatDesc);
GLCP_API SurfaceFormatDesc GetDefaultSurfaceFormat();

GLCP_API GLPlatformContextP GLPlatformContextCreate(GLSurfaceFormatH hFormat, GLPlatformContextP pSharedContext = nullptr);
GLCP_API void GLPlatformContextDestroy(GLPlatformContextP pContext);

GLCP_API bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface = nullptr);
GLCP_API bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface);
GLCP_API GLPlatformContextP GLPlatformGetCurrentContext();

GLCP_API GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLSurfaceFormatH hFormat, const SurfaceDesc & surfaceDesc);
GLCP_API void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface);
GLCP_API void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height);

