#include "GLWinPlatform.h"
#include <gl/GL.h>

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x0002
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096

#define FRE_WINDOW_GL_CLASS "FRE_GLWNDCLASS"

typedef HGLRC (APIENTRY * PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int *);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

static FRE::GLWinPlatform sWinPlatform;

namespace FRE
{
	bool PlatformInit()
	{
		return sWinPlatform.Init();
	}

	h_GLContext PlatformCreateContext(h_GLContext shared)
	{
		return sWinPlatform.CreateContext(shared);
	}

	h_GLRenderTarget PlatformCreateSurfaceTarget(h_GLContext context, const DarkParams & params)
	{
		return sWinPlatform.CreateSurfaceTarget(context, params);
	}

	bool PlatformMakeCurrentContext(h_GLContext context)
	{
		return sWinPlatform.MakeCurrentContext(context);
	}

	bool PlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target)
	{
		return sWinPlatform.MakeCurrentContext(context, target);
	}

	bool PlatformSwapContext(h_GLContext context, h_GLRenderTarget target)
	{
		return sWinPlatform.SwapContext(context, target);
	}

	void PlatformDestroyEntity(int64 handle)
	{
		sWinPlatform.Destroy(handle);
	}

    class GLWinContext
    {
	public:
		enum
		{
			Type = GLTypeObject::Context
		};

		~GLWinContext();

		HGLRC GetHglrc() const { return _hglrc; }

		static GLWinContext * Create(HDC hdc, GLWinContext * shared = nullptr);
		static HGLRC CreateGLContext(HDC hdc, HGLRC shareHrc);

	private:
		GLWinContext(HGLRC hrc);

		HGLRC _hglrc;
		unsigned _pixelFormat;
    };

	GLWinContext * GLWinContext::Create(HDC hdc, GLWinContext * shared)
	{
		HGLRC ctx = GLWinContext::CreateGLContext(hdc, shared ? shared->_hglrc : NULL);
		return ctx ? new GLWinContext(ctx) : nullptr;
	}

	GLWinContext::GLWinContext(HGLRC hrc) :
		_hglrc(hrc)
	{

	}

	GLWinContext::~GLWinContext()
	{
		if (_hglrc)
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_hglrc);
		}
	}

	HGLRC GLWinContext::CreateGLContext(HDC hdc, HGLRC shareHrc)
	{
		HGLRC context = 0;

		auto ctxMask = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
		auto ctxFlags = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
#ifdef _DEBUG
		ctxFlags |= WGL_CONTEXT_DEBUG_BIT_ARB;
#endif

		int ctxAttributes[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 0,
			WGL_CONTEXT_FLAGS_ARB, ctxFlags,
			WGL_CONTEXT_PROFILE_MASK_ARB, ctxMask,
			0
		};

		if (wglCreateContextAttribsARB)
			context = wglCreateContextAttribsARB(hdc, shareHrc, ctxAttributes);

		return context;
	}

	//-------------------------------------------------------------

    class GLWinSurfaceTarget
    {
    public:
		enum
		{
			Type = GLTypeObject::Surface
		};

		~GLWinSurfaceTarget();

		static GLWinSurfaceTarget * Create(int pixelFormat, HWND parent);

		HDC GetHDC() const { return _hdc; }

		bool Swap() const
		{
			return SwapBuffers(_hdc) == TRUE;
		}

	private:
        GLWinSurfaceTarget(HWND hwnd, HDC hdc);

		HWND _hwnd;
		HDC _hdc;
    };

	GLWinSurfaceTarget::GLWinSurfaceTarget(HWND hwnd, HDC hdc) :
		_hwnd(hwnd),
		_hdc(hdc)
	{

	}

	GLWinSurfaceTarget::~GLWinSurfaceTarget()
	{
		ReleaseDC(_hwnd, _hdc);
		DestroyWindow(_hwnd);
	}

	GLWinSurfaceTarget * GLWinSurfaceTarget::Create(int pixelFormat, HWND parent)
	{
		HINSTANCE hinst = GetModuleHandle(nullptr);
		HWND hwnd = CreateWindowA(FRE_WINDOW_GL_CLASS, "FRE_GLWinSurfaceTarget", WS_POPUP | WS_CLIPCHILDREN, 0, 0, 100, 100, parent, NULL, hinst, NULL);
		if (hwnd)
		{
			HDC hdc = GetDC(hwnd);
			if (hdc)
			{
				PIXELFORMATDESCRIPTOR pixelDest;
				if (SetPixelFormat(hdc, pixelFormat, &pixelDest))
				{
					return new GLWinSurfaceTarget(hwnd, hdc);
				}
				ReleaseDC(hwnd, hdc);
			}
			DestroyWindow(hwnd);
		}
		return nullptr;
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

	DWORD _GetLastError(const char ** msg)
	{
		DWORD error = GetLastError();
		const unsigned msgBufferSize = 1024;
		static LPTSTR msgBuffer[msgBufferSize];
		memset(msgBuffer, 0, sizeof(msgBuffer));
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, (LPTSTR)&msgBuffer, msgBufferSize, NULL);
		*msg = (char *)msgBuffer;
		return error;
	}

	HWND _CreateWindow(const char * name, unsigned width, unsigned height, HWND parent)
	{
		HINSTANCE hinst = GetModuleHandle(nullptr);

		WNDCLASSA wclass;
		memset(&wclass, 0, sizeof(WNDCLASSA));

		wclass.style = CS_OWNDC;
		wclass.hInstance = hinst;
		wclass.lpfnWndProc = DefWindowProc;
		wclass.lpszClassName = FRE_WINDOW_GL_CLASS;

		if (!GetClassInfoA(hinst, FRE_WINDOW_GL_CLASS, &wclass))
			RegisterClassA(&wclass);

		return CreateWindowA(FRE_WINDOW_GL_CLASS, name, WS_POPUP | WS_CLIPCHILDREN, 0, 0, width, height, parent, NULL, hinst, NULL);
	}

	void _DestroyWindow(HWND hwnd)
	{
		if (hwnd)
			DestroyWindow(hwnd);
	}

	PIXELFORMATDESCRIPTOR GetDefaultPixelFormatDesc()
	{
		PIXELFORMATDESCRIPTOR pixelDesc;
		memset(&pixelDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));

		pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelDesc.nVersion = 1;
		pixelDesc.iPixelType = PFD_TYPE_RGBA;
		pixelDesc.cColorBits = 32;
		return pixelDesc;
	}

	//-----------------------------------------------------------------------

	GLWinPlatform::GLWinPlatform() :
		_hwnd(0),
		_hdc(0),
		_initialize(false)
	{

	}

	GLWinPlatform::~GLWinPlatform()
	{
		_DestroyWindow(_hwnd);
	}

	bool GLWinPlatform::Init()
	{
		if (!_initialize)
		{
			_hwnd = _CreateWindow("FRE_GLWinPlatform", 1, 1, NULL);
			if (_hwnd)
			{
				_hdc = GetDC(_hwnd);
				if (_hdc)
				{
					HGLRC initHrc = NULL;

					PIXELFORMATDESCRIPTOR pixelDesc = GetDefaultPixelFormatDesc();

					const int pixelFormat = ::ChoosePixelFormat(_hdc, &pixelDesc);
					if (pixelFormat > 0)
					{
						if (::SetPixelFormat(_hdc, pixelFormat, &pixelDesc))
							initHrc = wglCreateContext(_hdc);
					}

					if (initHrc)
					{
						if (wglMakeCurrent(_hdc, initHrc))
						{
							wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
							_initialize = wglCreateContextAttribsARB != nullptr;
							wglMakeCurrent(NULL, NULL);
						}
						wglDeleteContext(initHrc);
					}
				}
			}
		}

		return _initialize;
	}

    h_GLContext GLWinPlatform::CreateContext(h_GLContext shared)
    {
		GLWinContext * winContext = GLWinContext::Create(sWinPlatform.GlobalHdc(), GetTypedObject<GLWinContext>(shared));
		if (winContext)
		{
			const uint32 index = _objects.Add(std::shared_ptr<GLWinContext>(winContext));
			return FormHandle((GLTypeObject)GLWinContext::Type, index);
		}
		return 0;
    }

    h_GLRenderTarget GLWinPlatform::CreateSurfaceTarget(h_GLContext context, const DarkParams & params)
    {
		GLWinSurfaceTarget * winSurface = GLWinSurfaceTarget::Create(GetPixelFormat(sWinPlatform.GlobalHdc()), (HWND)params.params[0]);
		if (winSurface)
		{
			const uint32 index = _objects.Add(std::shared_ptr<GLWinSurfaceTarget>(winSurface));
			return FormHandle((GLTypeObject)GLWinSurfaceTarget::Type, index);
		}
        return 0;
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
			return wglMakeCurrent(NULL, NULL) == TRUE;
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
			return wglMakeCurrent(NULL, NULL) == TRUE;
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