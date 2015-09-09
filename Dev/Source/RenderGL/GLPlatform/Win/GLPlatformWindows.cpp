#include "GLPlatformWindows.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "FSafeCont.h"

#include <memory>
#include <set>

static bool sDebugMode = false;

struct
{
	unsigned Major;
	unsigned Minor;
} OpenGLVer;

typedef std::unique_ptr<GLPlatformRenderSurface> GLPlatformRenderSurfacePtr;
GLPlatformRenderSurfacePtr GlobalWinTarget;

struct GLSurfaceLess
{
	typedef HDC CompareType;

	bool operator()(const GLPlatformRenderSurfaceP left, const GLPlatformRenderSurfaceP right) const
	{
		return left->DeviceContext < right->DeviceContext;
	}

	bool operator()(const GLPlatformRenderSurfaceP left, CompareType value) const
	{
		return left->DeviceContext < value;
	}
};

//struct GLContextLess
//{
//	typedef HGLRC CompareType;
//
//	bool operator()(const GLPlatformContextP left, const GLPlatformContextP right) const
//	{
//		return left->ContextHandle < right->ContextHandle;
//	}
//
//	bool operator()(const GLPlatformContextP left, CompareType value) const
//	{
//		return left->ContextHandle < value;
//	}
//};

SafeSet<GLPlatformRenderSurfaceP, GLSurfaceLess> s_GLSurfaceContainer;
//SafeSet<GLPlatformContextP, GLContextLess> s_GLContextContainer;

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


GLPlatformContextH GLPlatformContextCreate(GLPlatformContextH hShared)
{
	HGLRC context = CreateContext(GlobalDeviceContext(), OpenGLVer.Major, OpenGLVer.Minor, reinterpret_cast<HGLRC>(hShared), sDebugMode);
	return reinterpret_cast<GLPlatformContextH>(context);
}

void GLPlatformContextDestroy(GLPlatformContextH hContext)
{
	HGLRC contextHandle = reinterpret_cast<HGLRC>(hContext);
	if (contextHandle == wglGetCurrentContext())
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(contextHandle);
	}
}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(uint64 params)
{
	GLPlatformRenderSurfaceP surface = CreateWindowSurface(GetPixelFormat(GlobalDeviceContext()), (HWND)params);
	if (surface)
		s_GLSurfaceContainer.Insert(surface);
	return surface;
}

void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
{
	if (pSurface)
	{
		s_GLSurfaceContainer.Remove(pSurface);
		delete pSurface;
	}
}

void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height)
{
	if (pSurface)
		return pSurface->Resize(width, height);
}

bool GLPlatformContextMakeCurrent(GLPlatformContextH hContext, GLPlatformRenderSurfaceP pSurface)
{
	HGLRC contextHandle = reinterpret_cast<HGLRC>(hContext);
	if (contextHandle)
	{
		if (pSurface)
			return wglMakeCurrent(pSurface->DeviceContext, contextHandle) == TRUE;
		else
			return wglMakeCurrent(GlobalDeviceContext(), contextHandle) == TRUE;
	}

	return wglMakeCurrent(NULL, NULL) == TRUE;
}

bool GLPlatformContextSwap(GLPlatformContextH hContext, GLPlatformRenderSurfaceP pSurface)
{
	if (pSurface)
		return pSurface->Swap();
	return false;
}

GLPlatformContextH GLPlatformGetCurrentContext()
{
	return reinterpret_cast<GLPlatformContextH>(wglGetCurrentContext());
}

#endif