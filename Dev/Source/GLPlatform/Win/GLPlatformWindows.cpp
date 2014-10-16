#include "GLPlatformWindows.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include <memory>

static bool sDebugMode = false;

struct
{
	unsigned Major;
	unsigned Minor;
} OpenGLVer;


std::auto_ptr<GLPlatformRenderSurface> GlobalWinTarget;

HWND GlobalWindowHandle()
{
	if (GlobalWinTarget.get())
		return GlobalWinTarget->WindowHandle;
	return 0;
}

HDC	GlobalDeviceContext()
{
	if (GlobalWinTarget.get())
		return GlobalWinTarget->DeviceContext;
	return 0;
}

GLPlatformRenderSurfaceP CreateGlobalTarget()
{
	HWND hwnd = WinCreateWindow("GL_WIN_PLATFORM", 1, 1, NULL);
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

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
	static bool init = false;
	if (!init)
	{
		GlobalWinTarget.reset(CreateGlobalTarget());
		if (GlobalWinTarget.get() &&
			WGLInitialize(GlobalWinTarget->DeviceContext, majorVer, minorVer))
		{
			OpenGLVer.Major = majorVer;
			OpenGLVer.Major = majorVer;
			init = true;
		}
		sDebugMode = debugMode;
	}
	return init;
}


GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP pShared)
{
	return CreateContext(GlobalDeviceContext(), OpenGLVer.Major, OpenGLVer.Minor, (GLPlatformContext *)pShared);
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
{
	if (pContext)
		delete reinterpret_cast<GLPlatformContext *>(pContext);
}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLPlatformContextP pContext, uint64 params)
{
	return CreateWindowSurface(GetPixelFormat(GlobalDeviceContext()), (HWND)params);
}

void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pTarget)
{
	if (pTarget)
		delete reinterpret_cast<GLPlatformRenderSurface *>(pTarget);
}

void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pTarget, unsigned width, unsigned height)
{
	GLPlatformRenderSurface * target = reinterpret_cast<GLPlatformRenderSurface *>(pTarget);
	if (target)
		return target->Resize(width, height);
}

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext)
{
	if (pContext != 0)
	{
		GLPlatformContext * context = reinterpret_cast<GLPlatformContext *>(pContext);
		return wglMakeCurrent(GlobalDeviceContext(), context->GLContext) == TRUE;
	}
	else
	{
		return wglMakeCurrent(NULL, NULL) == TRUE;
	}
	return false;
}

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pTarget)
{
	if (pContext != 0)
	{
		GLPlatformContext * context = reinterpret_cast<GLPlatformContext *>(pContext);
		if (pTarget)
		{
			GLPlatformRenderSurface * target = reinterpret_cast<GLPlatformRenderSurface *>(pTarget);
			return wglMakeCurrent(target->DeviceContext, context->GLContext) == TRUE;
		}
	}
	else
	{
		return wglMakeCurrent(NULL, NULL) == TRUE;
	}
	return false;
}

bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pTarget)
{
	GLPlatformRenderSurface * target = reinterpret_cast<GLPlatformRenderSurface *>(pTarget);
	if (target)
		return target->Swap();
	return false;
}

#endif