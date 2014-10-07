#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "FOpenGLWindow.h"
#include "FOpenGLPlatform.h"

static bool sDebugMode = false;

GLVersion OpenGLVer;

std::auto_ptr<GLPlatformRenderSurface> globalWinTarget;

HWND GlobalWindowHandle()
{
	if (globalWinTarget.get())
		return globalWinTarget->WindowHandle;
	return 0;
}

HDC	GlobalDeviceContext()
{
	if (globalWinTarget.get())
		return globalWinTarget->DeviceContext;
	return 0;
}

GLPlatformRenderSurfaceP CreateGlobalTarget()
{
	HWND hwnd = WinCreateWindow("FRE_GLWinPlatform", 1, 1, NULL);
	if (hwnd)
	{
		HDC hdc = GetDC(hwnd);
		if (hdc)
		{
			return new GLPlatformRenderSurface(hwnd, hdc);
		}
		WinDestroyWindow(hwnd);
	}
	return nullptr;
}

//-----------------------------------------------------------------------
// Platform function implementation for windows.

bool GLPlatformInit(const GLVersion & glVer, bool debugMode)
{
	static bool init = false;
	if (!init)
	{
		globalWinTarget.reset(CreateGlobalTarget());
		if (globalWinTarget.get() &&
			WGLInitialize(globalWinTarget->DeviceContext, glVer.Major, glVer.Minor))
		{
			OpenGLVer = glVer;
			init = true;
		}
		sDebugMode = debugMode;
	}
	return init;
}


GLPlatformContextP GLContextCreate(GLPlatformContextP hShared)
{
	return CreateContext(GlobalDeviceContext(), OpenGLVer.Major, OpenGLVer.Minor, (GLPlatformContext *)hShared);
}

void GLContextDestroy(GLPlatformContextP hContext)
{
	if (hContext)
		delete reinterpret_cast<GLPlatformContext *>(hContext);
}

GLPlatformRenderSurfaceP GLSurfaceCreate(GLPlatformContextP hContext, uint64 params)
{
	return CreateWindowSurface(GetPixelFormat(GlobalDeviceContext()), (HWND)params);
}

void GLSurfaceDestroy(GLPlatformRenderSurfaceP hTarget)
{
	if (hTarget)
		delete reinterpret_cast<GLPlatformRenderSurface *>(hTarget);
}

void GLSurfaceUpdate(GLPlatformRenderSurfaceP hTarget, unsigned width, unsigned height)
{
	GLPlatformRenderSurface * target = reinterpret_cast<GLPlatformRenderSurface *>(hTarget);
	if (target)
		return target->Resize(width, height);
}

bool GLContextMakeCurrent(GLPlatformContextP hContext)
{
	if (hContext != 0)
	{
		GLPlatformContext * context = reinterpret_cast<GLPlatformContext *>(hContext);
		return wglMakeCurrent(GlobalDeviceContext(), context->GLContext) == TRUE;
	}
	else
	{
		return wglMakeCurrent(NULL, NULL) == TRUE;
	}
	return false;
}

bool GLContextMakeCurrent(GLPlatformContextP hContext, GLPlatformRenderSurfaceP hTarget)
{
	if (hContext != 0)
	{
		GLPlatformContext * context = reinterpret_cast<GLPlatformContext *>(hContext);
		if (hTarget)
		{
			GLPlatformRenderSurface * target = reinterpret_cast<GLPlatformRenderSurface *>(hTarget);
			return wglMakeCurrent(target->DeviceContext, context->GLContext) == TRUE;
		}
	}
	else
	{
		return wglMakeCurrent(NULL, NULL) == TRUE;
	}
	return false;
}

bool GLContextSwap(GLPlatformContextP hContext, GLPlatformRenderSurfaceP hTarget)
{
	GLPlatformRenderSurface * target = reinterpret_cast<GLPlatformRenderSurface *>(hTarget);
	if (target)
		return target->Swap();
	return false;
}

#endif