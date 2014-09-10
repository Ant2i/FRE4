#pragma once

#ifdef _WIN32
#include "FOpenGLWindow.h"
#else
#include "FOpenGLMac.h"
#endif

namespace FRE
{
	typedef TOpenGLAPI OpenGLAPI;

	//-----------------------------------------------------------------------

	typedef uint64 HGLContext;
	typedef uint64 HGLRenderSurface;

	bool GLPlatformInit(const GLVersion & ver, bool debugMode);

	HGLContext GLContextCreate(HGLContext hShared = 0);
	void GLContextDestroy(HGLContext hContext);

	bool GLContextMakeCurrent(HGLContext hContext);
	bool GLContextMakeCurrent(HGLContext hContext, HGLRenderSurface hSurface);
	bool GLContextSwap(HGLContext hContext, HGLRenderSurface hSurface);

	HGLRenderSurface GLSurfaceCreate(HGLContext hContext, uint64 params);
	void GLSurfaceDestroy(HGLRenderSurface hSurface);

	void GLSurfaceUpdate(HGLRenderSurface hSurface, unsigned width, unsigned height);
}
