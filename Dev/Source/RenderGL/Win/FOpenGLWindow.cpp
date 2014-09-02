#include "FOpenGLWindow.h"

static bool sDebugMode = false;

FRE::GLVersion OpenGLVer;

typedef FRE::GLWinSurfaceTarget GLGlobalWinTarget;
std::auto_ptr<GLGlobalWinTarget> globalWinTarget;

FRE::ObjectContainer objectCont;

namespace FRE
{
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

	GLGlobalWinTarget * Create()
	{
		HWND hwnd = _CreateWindow("FRE_GLWinPlatform", 1, 1, NULL);
		if (hwnd)
		{
			HDC hdc = GetDC(hwnd);
			if (hdc)
			{
				return new GLGlobalWinTarget(hwnd, hdc);
			}
			_DestroyWindow(hwnd);
		}
		return nullptr;
	}

	//-----------------------------------------------------------------------

	bool GLPlatformInit(const GLVersion & glVer, bool debugMode)
	{
		static bool init = false;
		if (!init)
		{
			globalWinTarget.reset(Create());
			if (globalWinTarget.get() && 
				WGLCheckCapabilities(globalWinTarget->Hdc, glVer.Major, glVer.Minor))
			{
				OpenGLVer = glVer;
				init = true;
			}
			sDebugMode = debugMode;
		}
		return init;
	}

	h_GLContext GLPlatformContextCreate(h_GLContext hShared)
	{
		GLWinContext * winContext = Create(GlobalHdc(), OpenGLVer.Major, OpenGLVer.Minor, objectCont.Get<GLWinContext>(hShared));
		return objectCont.Add(winContext);
	}

	h_GLRenderTarget GLPlatformSurfaceTargetCreate(h_GLContext hContext, uint64 params)
	{
		GLWinSurfaceTarget * winSurface = Create(GetPixelFormat(GlobalHdc()), (HWND)params);
		return objectCont.Add(winSurface);
	}

	void GLPlatformSurfaceTargetUpdate(h_GLRenderTarget hTarget, unsigned width, unsigned height)
	{
		GLWinSurfaceTarget * target = objectCont.Get<GLWinSurfaceTarget>(hTarget);
		if (target)
			return target->Resize(width, height);
	}

	bool GLPlatformContextMakeCurrent(h_GLContext hContext)
	{
		if (hContext != 0)
		{
			GLWinContext * context = objectCont.Get<GLWinContext>(hContext);
			if (context)
				return wglMakeCurrent(GlobalHdc(), context->Hglrc) == TRUE;
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLPlatformContextMakeCurrent(h_GLContext hContext, h_GLRenderTarget hTarget)
	{
		if (hContext != 0)
		{
			GLWinContext * context = objectCont.Get<GLWinContext>(hContext);
			if (context)
			{
				GLWinSurfaceTarget * target = objectCont.Get<GLWinSurfaceTarget>(hTarget);
				if (target)
					return wglMakeCurrent(target->Hdc, context->Hglrc) == TRUE;
			}
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLPlatformContextSwap(h_GLContext hContext, h_GLRenderTarget hTarget)
	{
		GLWinSurfaceTarget * target = objectCont.Get<GLWinSurfaceTarget>(hTarget);
		if (target)
			return target->Swap();
		return false;
	}

	void GLPlatformDestroyEntity(int64 hHandle)
	{
		objectCont.Remove(hHandle);
	}

	//-----------------------------------------------------------------------

    uint32 ObjectContainer::GetIndex(uint64 handle)
    {
        return (uint32)handle;
    }

    uint64 ObjectContainer::FormHandle(GLTypeObject type, uint32 index)
    {
        return (uint64)((uint64)type << 32 | index);
    }
}