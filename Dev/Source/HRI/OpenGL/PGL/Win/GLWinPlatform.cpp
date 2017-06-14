﻿#include "GLWinPlatform.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "GLWinSupport.h"
#include <memory>
#include <vector>
#include <map>
#include <mutex>
#include <thread>

#pragma warning (disable: 4100)

class GLPlatformContext;
class GLPlatformRenderSurface;

class InternalData
{
public:
	InternalData() :
		DebugMode(false)
	{

	}

	bool DebugMode;
	unsigned Major;
	unsigned Minor;

	void SetCurrentContext(GLPlatformContext * context)
	{
		std::lock_guard<std::mutex> lock(_contextMutex);
		_currentContexts[std::this_thread::get_id()] = context;
	}

	GLPlatformContext * GetCurrentContext()
	{
		std::lock_guard<std::mutex> lock(_contextMutex);
		const auto & it = _currentContexts.find(std::this_thread::get_id());
		if (it != _currentContexts.end())
			return it->second;
		return nullptr;
	}

	GLPlatformRenderSurface * GetSurfaceForPixelFormat(unsigned pixelFormat)
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
	std::map<std::thread::id, GLPlatformContext *> _currentContexts;
	std::mutex _contextMutex;
};

//-----------------------------------------------------------------------

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

//-----------------------------------------------------------------------

static InternalData s_GlobalData;

bool PGLInitialize(unsigned * oMajorVer, unsigned * oMinorVer, bool iDebugMode)
{
	WGLInitInfo info;
	bool result = GLWinSupport::InitWGL(info);

	s_GlobalData.SurfaceForPixelFormat.resize(info.PixelFormatNum);

	s_GlobalData.Major = info.Major;
	s_GlobalData.Minor = info.Minor;

	if (oMajorVer) *oMajorVer = info.Major;
	if (oMinorVer) *oMinorVer = info.Minor;

	return result;
}

void PGLTerminate()
{

}

PGLContext PGLContextCreate(PGLSurface iConfig, PGLContext iSharedContext, const PGLContextDesc * iDesc)
{
	GLPlatformRenderSurface * surface = s_GlobalData.GetSurfaceForPixelFormat(reinterpret_cast<intptr_t>(iConfig));
	if (surface)
	{
		HGLRC shared = iSharedContext ? ((GLPlatformContext *)iSharedContext)->Handle : 0;
		HGLRC hrc = 0;

		int major = s_GlobalData.Major;
		int minor = s_GlobalData.Minor;

		if (iDesc)
		{
			hrc = GLWinSupport::GLCreateContext(surface->DeviceContext, shared, major, minor, s_GlobalData.DebugMode, iDesc->CoreProfile, false);
		}
		else
		{
			hrc = GLWinSupport::GLCreateContext(surface->DeviceContext, shared, major, minor, s_GlobalData.DebugMode, true, false);
			if (!hrc)
				hrc = wglCreateContext(surface->DeviceContext);
		}

		if (hrc)
			return new GLPlatformContext(hrc, reinterpret_cast<intptr_t>(iConfig));
	}
	return 0;
}

void PGLContextDestroy(PGLContext iContext)
{
	if (iContext)
	{
		GLPlatformContext * context = (GLPlatformContext *)iContext;

		if (s_GlobalData.GetCurrentContext() == context)
			s_GlobalData.SetCurrentContext(nullptr);
		delete context;
	}
}

PGLSurface PGLSurfaceCreate(PGLSurface iConfig, PGLNativeWindowType iWindow, const PGLSurfaceDesc * iDesc)
{
	std::unique_ptr<GLPlatformRenderSurface> surface(new GLPlatformRenderSurface((HWND)iWindow, false));
	if (GLWinSupport::SetPixelFormat(surface->DeviceContext, reinterpret_cast<intptr_t>(iConfig)))
	{
		return surface.release();
	}
	return nullptr;
}

void PGLSurfaceDestroy(PGLSurface iSurface)
{
	if (iSurface)
	{
		GLPlatformRenderSurface * surface = (GLPlatformRenderSurface *)iSurface;
		delete surface;
	}
}

bool PGLContextMakeCurrent(PGLContext iContext, PGLSurface iSurface)
{
	if (iContext)
	{
		GLPlatformContext * context = (GLPlatformContext *)iContext;

		GLPlatformRenderSurface * surface = iSurface ? 
			(GLPlatformRenderSurface *)iSurface : s_GlobalData.GetSurfaceForPixelFormat(context->PixelFormat);

		BOOL isOk = FALSE;
		if (surface)
			isOk = wglMakeCurrent(surface->DeviceContext, context->Handle) == TRUE;

		if (isOk)
		{
			s_GlobalData.SetCurrentContext(context);
			return true;
		}
	}

	s_GlobalData.SetCurrentContext(nullptr);
	return wglMakeCurrent(NULL, NULL) == TRUE;
}

bool PGLSwapBuffers(PGLSurface iSurface)
{
	if (iSurface)
	{
		GLPlatformRenderSurface * surface = (GLPlatformRenderSurface *)iSurface;
		return surface->Swap();
	}
	return false;
}

PGLContext PGLGetCurrentContext()
{
	return s_GlobalData.GetCurrentContext();
}

PGLConfigDesc PGLDefaultConfigDesc()
{
	PGLConfigDesc config;
	memset(&config, 0, sizeof(config));
	config.RedSize = 8;
	config.GreenSize = 8;
	config.BlueSize = 8;
	config.DepthSize = 0;
	config.Stereo = false;
	return config;
}

PGLSurface PGLChooseConfig(const PGLConfigDesc * iDesc)
{
	std::unique_ptr<GLPlatformRenderSurface> surface(GLPlatformRenderSurface::CreateNew());
	int pixelFormat = GLWinSupport::ChoosePixelFormat(surface->DeviceContext, GLWinSupport::GLPixelFormatDesc(iDesc ? *iDesc : PGLDefaultConfigDesc()));
	return reinterpret_cast<PGLSurface>(pixelFormat);
}

bool PGLGetConfigDesc(PGLSurface iConfig, PGLConfigDesc * oDesc)
{
	return false;
}

#endif
