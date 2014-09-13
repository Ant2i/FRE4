#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "FOpenGLPlatform.h"

static bool sDebugMode = false;

GLVersion OpenGLVer;

typedef WGLSurface GLGlobalWinTarget;
std::auto_ptr<GLGlobalWinTarget> globalWinTarget;

HWND GlobalHwnd()
{
	if (globalWinTarget.get())
		return globalWinTarget->Hwnd;
	return 0;
}

HDC	GlobalHdc()
{
	if (globalWinTarget.get())
		return globalWinTarget->Hdc;
	return 0;
}

GLGlobalWinTarget * CreateGlobalTarget()
{
	HWND hwnd = WinCreateWindow("FRE_GLWinPlatform", 1, 1, NULL);
	if (hwnd)
	{
		HDC hdc = GetDC(hwnd);
		if (hdc)
		{
			return new GLGlobalWinTarget(hwnd, hdc);
		}
		WinDestroyWindow(hwnd);
	}
	return nullptr;
}

//-----------------------------------------------------------------------
// Platform function implementation for windows.

namespace FRE
{
	bool GLPlatformInit(const GLVersion & glVer, bool debugMode)
	{
		static bool init = false;
		if (!init)
		{
			globalWinTarget.reset(CreateGlobalTarget());
			if (globalWinTarget.get() &&
				WGLInitialize(globalWinTarget->Hdc, glVer.Major, glVer.Minor))
			{
				OpenGLVer = glVer;
				init = true;
			}
			sDebugMode = debugMode;
		}
		return init;
	}


	HGLContext GLContextCreate(HGLContext hShared)
	{
		WGLContext * winContext = CreateContext(GlobalHdc(), OpenGLVer.Major, OpenGLVer.Minor, reinterpret_cast<WGLContext *>(hShared));
		return reinterpret_cast<HGLContext>(winContext);
	}

	void GLContextDestroy(HGLContext hContext)
	{
		if (hContext)
			delete reinterpret_cast<WGLContext *>(hContext);
	}

	HGLRenderSurface GLSurfaceCreate(HGLContext hContext, uint64 params)
	{
		WGLSurface * winSurface = CreateWindowSurface(GetPixelFormat(GlobalHdc()), (HWND)params);
		return reinterpret_cast<HGLContext>(winSurface);
	}

	void GLSurfaceDestroy(HGLRenderSurface hTarget)
	{
		if (hTarget)
			delete reinterpret_cast<WGLSurface *>(hTarget);
	}

	void GLSurfaceUpdate(HGLRenderSurface hTarget, unsigned width, unsigned height)
	{
		WGLSurface * target = reinterpret_cast<WGLSurface *>(hTarget);
		if (target)
			return target->Resize(width, height);
	}

	bool GLContextMakeCurrent(HGLContext hContext)
	{
		if (hContext != 0)
		{
			WGLContext * context = reinterpret_cast<WGLContext *>(hContext);
			return wglMakeCurrent(GlobalHdc(), context->Hglrc) == TRUE;
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLContextMakeCurrent(HGLContext hContext, HGLRenderSurface hTarget)
	{
		if (hContext != 0)
		{
			WGLContext * context = reinterpret_cast<WGLContext *>(hContext);
			if (hTarget)
			{
				WGLSurface * target = reinterpret_cast<WGLSurface *>(hTarget);
				return wglMakeCurrent(target->Hdc, context->Hglrc) == TRUE;
			}
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLContextSwap(HGLContext hContext, HGLRenderSurface hTarget)
	{
		WGLSurface * target = reinterpret_cast<WGLSurface *>(hTarget);
		if (target)
			return target->Swap();
		return false;
	}
}

#endif