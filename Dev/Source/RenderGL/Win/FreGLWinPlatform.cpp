#include "FreGLWinPlatform.h"
#include "FreGLWinContext.h"
#include "FreGLWinTarget.h"

static FRE::GLWinPlatform sWinPlatform;
static bool sDebugMode = false;

namespace FRE
{
	bool GLPlatformInit(const GLVersion & ver, bool debugMode)
	{
		static bool init = false;
		if (!init)
		{
			init = sWinPlatform.Init(ver);
			sDebugMode = debugMode;
		}
		return init;
	}

	h_GLContext GLPlatformCreateContext(h_GLContext shared)
	{
		return sWinPlatform.CreateContext(shared, sDebugMode);
	}

	h_GLRenderTarget GLPlatformCreateSurfaceTarget(h_GLContext context, uint64 params)
	{
		return sWinPlatform.CreateSurfaceTarget(context, params);
	}

	void GLPlatformUpdateSurfaceTarget(h_GLRenderTarget target, unsigned width, unsigned height)
	{
		return sWinPlatform.UpdateTarget(target, width, height);
	}

	bool GLPlatformMakeCurrentContext(h_GLContext context)
	{
		return sWinPlatform.MakeCurrentContext(context);
	}

	bool GLPlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target)
	{
		return sWinPlatform.MakeCurrentContext(context, target);
	}

	bool GLPlatformSwapContext(h_GLContext context, h_GLRenderTarget target)
	{
		return sWinPlatform.SwapContext(context, target);
	}

	void GLPlatformDestroyEntity(int64 handle)
	{
		sWinPlatform.Destroy(handle);
	}

	//-----------------------------------------------------------------------

    GLTypeObject GLWinPlatform::GetType(uint64 handle)
    {
        return (GLTypeObject)(handle >> 32);
    }

    uint32 GLWinPlatform::GetIndex(uint64 handle)
    {
        return (uint32)handle;
    }

    uint64 GLWinPlatform::FormHandle(GLTypeObject type, uint32 index)
    {
        return (uint64)((uint64)type << 32 | index);
    }

	//-----------------------------------------------------------------------

	GLWinPlatform::GLWinPlatform() :
		_hwnd(0),
		_hdc(0)
	{

	}

	GLWinPlatform::~GLWinPlatform()
	{
		_DestroyWindow(_hwnd);
	}

	bool GLWinPlatform::Init(const GLVersion & version)
	{
	    _DestroyWindow(_hwnd);
	    _hdc = 0;

	    _hwnd = _CreateWindow("FRE_GLWinPlatform", 1, 1, NULL);
	    if (_hwnd)
	    {
	        _hdc = GetDC(_hwnd);
            if (_hdc && GLWinContext::CheckGLCapabilities(_hdc, version.Major, version.Minor))
			{
				_glVersion = version;
				return true;
			}
	    }
	    return false;
	}

    h_GLContext GLWinPlatform::CreateContext(h_GLContext shared, bool debug)
    {
		GLWinContext * winContext = GLWinContext::Create(sWinPlatform.GlobalHdc(), _glVersion.Major, _glVersion.Minor, GetTypedObject<GLWinContext>(shared));
		if (winContext)
		{
			const uint32 index = _objects.Add(std::shared_ptr<GLWinContext>(winContext));
			return FormHandle((GLTypeObject)GLWinContext::Type, index);
		}
		return 0;
    }

    h_GLRenderTarget GLWinPlatform::CreateSurfaceTarget(h_GLContext context, uint64 params)
    {
		GLWinSurfaceTarget * winSurface = GLWinSurfaceTarget::Create(GetPixelFormat(sWinPlatform.GlobalHdc()), (HWND)params);
		if (winSurface)
		{
			const uint32 index = _objects.Add(std::shared_ptr<GLWinSurfaceTarget>(winSurface));
			return FormHandle((GLTypeObject)GLWinSurfaceTarget::Type, index);
		}
        return 0;
    }

	void GLWinPlatform::UpdateTarget(h_GLRenderTarget target, unsigned width, unsigned height)
	{
		GLWinSurfaceTarget * winTarget = GetTypedObject<GLWinSurfaceTarget>(target);
		if (winTarget)
			return winTarget->Resize(width, height);
	}

	bool GLWinPlatform::MakeCurrentContext(h_GLContext context)
	{
		if (context != 0)
		{
			GLWinContext * winContext = GetTypedObject<GLWinContext>(context);
			if (winContext)
				return wglMakeCurrent(sWinPlatform.GlobalHdc(), winContext->GetHglrc()) == TRUE;
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLWinPlatform::MakeCurrentContext(h_GLContext context, h_GLRenderTarget target)
	{
		if (context != 0)
		{
			GLWinContext * winContext = GetTypedObject<GLWinContext>(context);
			if (winContext)
			{
				GLWinSurfaceTarget * winTarget = GetTypedObject<GLWinSurfaceTarget>(target);
				if (winTarget)
					return wglMakeCurrent(winTarget->GetHDC(), winContext->GetHglrc()) == TRUE;
			}
		}
		else
		{
			return wglMakeCurrent(NULL, NULL) == TRUE;
		}
		return false;
	}

	bool GLWinPlatform::SwapContext(h_GLContext context, h_GLRenderTarget target)
	{
		GLWinSurfaceTarget * winTarget = GetTypedObject<GLWinSurfaceTarget>(target);
		if (winTarget)
			return winTarget->Swap();
		return false;
	}

	void GLWinPlatform::Destroy(int64 handle)
	{
		_objects.Remove(GetIndex(handle));
	}

}