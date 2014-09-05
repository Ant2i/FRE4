#pragma once

#ifdef _WIN32
#include "FOpenGLWindow.h"
#else
#include "FOpenGLOsx.h"
#endif

namespace FRE
{
	typedef TOpenGLAPI OpenGLAPI;

	//-----------------------------------------------------------------------

	typedef uint64 h_GLContext;
	typedef uint64 h_GLRenderTarget;

	bool GLPlatformInit(const GLVersion & ver, bool debugMode);

	h_GLContext GLContextCreate(h_GLContext hShared = 0);
	void GLContextDestroy(h_GLContext hContext);

	bool GLContextMakeCurrent(h_GLContext hContext);
	bool GLContextMakeCurrent(h_GLContext hContext, h_GLRenderTarget hTarget);
	bool GLContextSwap(h_GLContext hContext, h_GLRenderTarget hTarget);

	h_GLRenderTarget GLTargetCreate(h_GLContext hContext, uint64 params);
	void GLTargetDestroy(h_GLRenderTarget hTarget);

	void GLTargetUpdate(h_GLRenderTarget hTarget, unsigned width, unsigned height);
}
