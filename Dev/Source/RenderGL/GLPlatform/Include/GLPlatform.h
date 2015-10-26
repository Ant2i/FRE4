#pragma once

#ifdef _WIN32
#define API_EXPORT_C extern "C" __declspec(dllexport)
#define API_IMPORT_C extern "C" __declspec(dllimport)
#else
#define API_EXPORT_C extern "C"
#define API_IMPORT_C extern "C"
#endif

#ifdef GL_PLATFORM_EXPORTS
#define PGL_API API_EXPORT_C
#else
#define PGL_API API_IMPORT_C
#endif

struct GLPlatformContext;
struct GLPlatformRenderSurface;

typedef GLPlatformContext * GLPlatformContextP;
typedef GLPlatformRenderSurface * GLPlatformRenderSurfaceP;

typedef unsigned long long int GLSurfaceFormatH;

//-----------------------------------------------------------------------------

typedef void * PGLContext;
typedef void * PGLSurface;
typedef void * PGLConfig;
typedef void * PGLNativeWindowType;

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

PGL_API bool PGLInitialize(unsigned * oMajorVer, unsigned * oMinorVer, bool iDebugMode);
PGL_API void PGLTerminate();

PGL_API PGLConfigDesc PGLDefaultConfigDesc();
PGL_API PGLConfig PGLChooseConfig(const PGLConfigDesc * iDesc);
PGL_API bool PGLGetConfigDesc(PGLConfig iConfig, PGLConfigDesc * oDesc);

PGL_API PGLContext PGLContextCreate(PGLConfig iConfig, PGLContext iSharedContext = nullptr, const PGLContextDesc * iDesc = nullptr);
PGL_API void PGLContextDestroy(PGLContext iContext);

PGL_API PGLSurface PGLSurfaceCreate(PGLConfig iConfig, PGLNativeWindowType iWindow, const PGLSurfaceDesc * iDesc = nullptr);
PGL_API void PGLSurfaceDestroy(PGLSurface iSurface);

PGL_API bool PGLContextMakeCurrent(PGLContext iContext, PGLSurface iSurface = nullptr);
PGL_API bool PGLSwapBuffers(PGLSurface iSurface);

PGL_API PGLContext PGLGetCurrentContext();


