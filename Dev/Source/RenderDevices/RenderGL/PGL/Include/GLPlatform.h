#pragma once

#ifdef _WIN32
#define API_EXPORT_C extern "C" __declspec(dllexport)
#define API_IMPORT_C extern "C" __declspec(dllimport)
#else
#define API_EXPORT_C extern "C"
#define API_IMPORT_C extern "C"
#endif

#ifndef GLCP_STATIC
	#ifdef GL_PLATFORM_EXPORTS
	#define GLCP_API API_EXPORT_C
	#else
	#define GLCP_API API_IMPORT_C
	#endif
#else
	#define GLCP_API
#endif

typedef void * PGLContext;
typedef void * PGLSurface;
typedef void * PGLConfig;
typedef void * PGLNativeWindowType;

struct PGLSurfaceDesc
{
	
};

enum Profile
{
	None = 0,
	Core = 1,
	ES = 2,
	ES2 = 4
};

struct PGLContextDesc
{
	bool CoreProfile;
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
GLCP_API PGLConfig PGLChooseConfig(const PGLConfigDesc * iDesc);
GLCP_API bool PGLGetConfigDesc(PGLConfig iConfig, PGLConfigDesc * oDesc);

GLCP_API PGLContext PGLContextCreate(PGLConfig iConfig, PGLContext iSharedContext = nullptr, const PGLContextDesc * iDesc = nullptr);
GLCP_API void PGLContextDestroy(PGLContext iContext);

GLCP_API PGLSurface PGLSurfaceCreate(PGLConfig iConfig, PGLNativeWindowType iWindow, const PGLSurfaceDesc * iDesc = nullptr);
GLCP_API void PGLSurfaceDestroy(PGLSurface iSurface);

GLCP_API bool PGLContextMakeCurrent(PGLContext iContext, PGLSurface iSurface = nullptr);
GLCP_API bool PGLSwapBuffers(PGLSurface iSurface);

GLCP_API PGLContext PGLGetCurrentContext();
