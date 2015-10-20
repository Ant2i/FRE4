#include "GLPlatformWindows.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "GLWinSupport.h"
#include <memory>
#include <vector>
#include <map>
#include <mutex>
#include <thread>

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

class InternalData
{
public:
	InternalData() :
		DebugMode(false)
	{

	}

	bool DebugMode;
	Version GLVersion;

	void SetCurrentContext(GLPlatformContextP context)
	{
		std::lock_guard<std::mutex> lock(_contextMutex);
		_currentContexts[std::this_thread::get_id()] = context;
	}

	GLPlatformContextP GetCurrentContext()
	{
		std::lock_guard<std::mutex> lock(_contextMutex);
		return _currentContexts[std::this_thread::get_id()];
	}

	GLPlatformRenderSurfaceP GetSurfaceForPixelFormat(unsigned pixelFormat)
	{
		static std::mutex mutex;
		if (SurfaceForPixelFormat.size() > pixelFormat)
		{
			auto & pixelSurface = SurfaceForPixelFormat[pixelFormat];
			if (!pixelSurface)
			{
				std::lock_guard<std::mutex> lock(mutex);
				if (!pixelSurface)
				{
					pixelSurface.reset(GLPlatformRenderSurface::CreateNew());
					if (!GLWinSupport::SetPixelFormat(pixelSurface->DeviceContext, pixelFormat))
						pixelSurface.reset();
				}
			}
			return pixelSurface.get();
		}
		return 0;
	}

	std::vector<std::unique_ptr<GLPlatformRenderSurface>> SurfaceForPixelFormat;

private:
	std::map<std::thread::id, GLPlatformContextP> _currentContexts;
	std::mutex _contextMutex;
};

class GLPlatformContext
{
public:
	GLPlatformContext(HGLRC rc, int pixelFormat) :
		Handle(rc),
		PixelFormat(pixelFormat)
	{

	}

	~GLPlatformContext()
	{
		if (Handle == wglGetCurrentContext())
			wglMakeCurrent(NULL, NULL);
		wglDeleteContext(Handle);
	}

	HGLRC Handle;
	int PixelFormat;
};

static InternalData s_GlobalData;

//-----------------------------------------------------------------------

int GetNumPixelFormats(HDC hdc)
{
	PIXELFORMATDESCRIPTOR  pfd;
	return DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
}

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
	bool result = false;

	std::unique_ptr<GLPlatformRenderSurface> tempSurface(GLPlatformRenderSurface::CreateNew());
	if (tempSurface && tempSurface->DeviceContext)
	{
		const HDC hdc = tempSurface->DeviceContext;

		s_GlobalData.SurfaceForPixelFormat.resize(GetNumPixelFormats(hdc));

		int pixelFormat = GLWinSupport::ChoosePixelFormat(hdc, GLWinSupport::GLPixelFormatDesc(false));
		if (GLWinSupport::SetPixelFormat(hdc, pixelFormat))
		{
			HGLRC hrc = GLWinSupport::GLCreateContext(hdc, majorVer, minorVer, 0, debugMode);
			if (hrc)
			{
				result = wglMakeCurrent(hdc, hrc) == TRUE;
				if (result)
				{
					s_GlobalData.GLVersion.Major = majorVer;
					s_GlobalData.GLVersion.Minor = minorVer;
					s_GlobalData.DebugMode = debugMode;
				}

				wglMakeCurrent(NULL, NULL);
				GLWinSupport::GLDeleteContext(hrc);
			}
		}
	}

	return result;
}

GLPlatformContextP GLPlatformContextCreate(GLSurfaceFormatH hFormat, GLPlatformContextP pSharedContext)
{
	GLPlatformRenderSurface * surface = s_GlobalData.GetSurfaceForPixelFormat((unsigned)hFormat);
	if (surface)
	{
		HGLRC sharedRC = pSharedContext ? pSharedContext->Handle : 0;
		HGLRC hrc = GLWinSupport::GLCreateContext(surface->DeviceContext, s_GlobalData.GLVersion.Major, s_GlobalData.GLVersion.Minor, sharedRC, s_GlobalData.DebugMode);
		if (hrc)
			return new GLPlatformContext(hrc, (int)hFormat);
	}
	return 0;
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
{
	if (pContext)
	{
		if (s_GlobalData.GetCurrentContext() == pContext)
			s_GlobalData.SetCurrentContext(nullptr);
		delete pContext;
	}
}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLSurfaceFormatH hFormat, const SurfaceDesc & surfaceDesc)
{
	if (surfaceDesc.External)
	{
		std::unique_ptr<GLPlatformRenderSurface> surface(new GLPlatformRenderSurface((HWND)surfaceDesc.PlatformData, false));
		if (GLWinSupport::SetPixelFormat(surface->DeviceContext, (int)hFormat))
		{
			return surface.release();
		}
	}
	return nullptr;
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

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	if (pContext)
	{
		bool isMake = false;

		if (pSurface)
			isMake = wglMakeCurrent(pSurface->DeviceContext, pContext->Handle) == TRUE;
		else
		{
			auto & pixelSurface = s_GlobalData.SurfaceForPixelFormat[pContext->PixelFormat];
			if (pixelSurface)
				isMake = wglMakeCurrent(pixelSurface->DeviceContext, pContext->Handle) == TRUE;
		}

		if (isMake)
		{
			s_GlobalData.SetCurrentContext(pContext);
			return true;
		}
	}

	s_GlobalData.SetCurrentContext(nullptr);
	return wglMakeCurrent(NULL, NULL) == TRUE;
}

bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	if (pSurface)
		return pSurface->Swap();
	return false;
}

GLPlatformContextP GLPlatformGetCurrentContext()
{
	return s_GlobalData.GetCurrentContext();
}

GLSurfaceFormatH FindSurfaceFormat(const SurfaceFormatDesc & formatDesc)
{
	std::unique_ptr<GLPlatformRenderSurface> surface(GLPlatformRenderSurface::CreateNew());
	return GLWinSupport::ChoosePixelFormat(surface->DeviceContext, GLWinSupport::GLPixelFormatDesc(formatDesc.Stereo));
}

SurfaceFormatDesc GetDefaultSurfaceFormat()
{
	SurfaceFormatDesc ret;
	ret.Stereo = false;
	return ret;
}

#endif