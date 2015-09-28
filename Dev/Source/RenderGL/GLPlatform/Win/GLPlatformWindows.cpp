#include "GLPlatformWindows.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "GLWinSupport.h"
#include <memory>

static bool sDebugMode = false;

struct Version
{
	Version() :
		Major(0),
		Minor(0)
	{

	}

	unsigned Major;
	unsigned Minor;
};

struct InternalData
{
	InternalData() : 
		DebugMode(false),
		PixelFormat(0)
	{

	}

	bool DebugMode;
	std::unique_ptr<GLPlatformRenderSurface> GlobalSurface;
	Version GLVer;
	int PixelFormat;
};

static InternalData s_Data;

//-----------------------------------------------------------------------

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
	bool result = false;

	s_Data.GlobalSurface.reset(GLPlatformRenderSurface::CreateNew(1, 1, NULL));
	if (s_Data.GlobalSurface && s_Data.GlobalSurface->DeviceContext)
	{
		const HDC hdc = s_Data.GlobalSurface->DeviceContext;

		int pixelFormat = GLWinSupport::SetDefaultPixelFormat(hdc);
		if (pixelFormat)
		{
			HGLRC rc = GLWinSupport::GLCreateContext(hdc, majorVer, minorVer, 0, debugMode);
			if (rc)
			{
				result = wglMakeCurrent(hdc, rc) == TRUE;
				if (result)
				{
					s_Data.GLVer.Major = majorVer;
					s_Data.GLVer.Minor = minorVer;
					s_Data.DebugMode = debugMode;
					s_Data.PixelFormat = pixelFormat;
				}

				wglMakeCurrent(hdc, NULL);
				GLWinSupport::GLDeleteContext(rc);
			}
		}
	}

	if (!result)
		s_Data.GlobalSurface.reset();

	return result;
}


GLPlatformContextH GLPlatformContextCreate(const ContextParams & params)
{
	HDC hdc = s_Data.GlobalSurface->DeviceContext;
	HGLRC context = GLWinSupport::GLCreateContext(hdc, s_Data.GLVer.Major, s_Data.GLVer.Minor, reinterpret_cast<HGLRC>(params.HShared), s_Data.DebugMode);
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

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(const SurfaceParams & params)
{
	GLPlatformRenderSurfaceP surface = new GLPlatformRenderSurface((HWND)params.Data, false);
	surface->SetPixelFormat(s_Data.PixelFormat);
	return surface;
}

void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
{
	if (pSurface)
		delete pSurface;
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
			return wglMakeCurrent(s_Data.GlobalSurface->DeviceContext, contextHandle) == TRUE;
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