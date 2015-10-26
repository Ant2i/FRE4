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