#include "FOpenGLPlatform.h"

static bool sDebugMode = false;

GLVersion OpenGLVer;

typedef GLWinSurfaceTarget GLGlobalWinTarget;
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

void OpenGLWindowsAPI::ProcessExtensions(const char * & extensions)
{

}

//-----------------------------------------------------------------------

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


	h_GLContext GLContextCreate(h_GLContext hShared)
	{
		GLWinContext * winContext = CreateContext(GlobalHdc(), OpenGLVer.Major, OpenGLVer.Minor, reinterpret_cast<GLWinContext *>(hShared));
		return reinterpret_cast<h_GLContext>(winContext);
	}

	void GLContextDestroy(h_GLContext hContext)
	{
		if (hContext)
			delete reinterpret_cast<GLWinContext *>(hContext);
	}

	h_GLRenderTarget GLTargetCreate(h_GLContext hContext, uint64 params)
	{
		GLWinSurfaceTarget * winSurface = CreateTarget(GetPixelFormat(GlobalHdc()), (HWND)params);
		return reinterpret_cast<h_GLContext>(winSurface);
	}

	void GLTargetDestroy(h_GLRenderTarget hTarget)
	{
		if (hTarget)
			delete reinterpret_cast<GLWinSurfaceTarget *>(hTarget);
	}

	void GLTargetUpdate(h_GLRenderTarget hTarget, unsigned width, unsigned height)
	{
		GLWinSurfaceTarget * target = reinterpret_cast<GLWinSurfaceTarget *>(hTarget);
		if (target)
			return target->Resize(width, height);
	}

	bool GLContextMakeCurrent(h_GLContext hContext)
	{
		if (hContext != 0)
		{
			GLWinContext * context = reinterpret_cast<GLWinContext *>(hContext);
			return wglMakeCurrent(GlobalHdc(), context->Hglrc) == TRUE;
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLContextMakeCurrent(h_GLContext hContext, h_GLRenderTarget hTarget)
	{
		if (hContext != 0)
		{
			GLWinContext * context = reinterpret_cast<GLWinContext *>(hContext);
			if (hTarget)
			{
				GLWinSurfaceTarget * target = reinterpret_cast<GLWinSurfaceTarget *>(hTarget);
				return wglMakeCurrent(target->Hdc, context->Hglrc) == TRUE;
			}
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLContextSwap(h_GLContext hContext, h_GLRenderTarget hTarget)
	{
		GLWinSurfaceTarget * target = reinterpret_cast<GLWinSurfaceTarget *>(hTarget);
		if (target)
			return target->Swap();
		return false;
	}
}
