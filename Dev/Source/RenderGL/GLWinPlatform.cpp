#include "GLWinPlatform.h"
#include <gl/GL.h>

//typedef BOOL (APIENTRY * PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);
//PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;

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

typedef HGLRC (APIENTRY * PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int *);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

static FRE::GLWinPlatform sWinPlatform;

#define FRE_WINDOW_GL_CLASS "FRE_GLWNDCLASS"

namespace FRE
{
    class GLObject
    {
    public:
        GLObject()
        {

        }

		virtual GLTypeObject GetType() const = 0;
    };

    class GLWinContext : public GLObject
    {
    public:
		~GLWinContext();

		static const GLTypeObject Type = GLTypeObject::Context;
		virtual GLTypeObject GetType() const { return Type; }

		static GLWinContext * Create(GLWinContext * shared = nullptr);
		static HGLRC CreateGLContext(HDC hdc, HGLRC shareHrc);

	private:
		GLWinContext(HGLRC hrc);

		HGLRC _hglrc;
		unsigned _pixelFormat;
    };

	GLWinContext * GLWinContext::Create(GLWinContext * shared)
	{
		HGLRC hglrc = GLWinContext::CreateGLContext(GetDC(sWinPlatform.GetGlobalWindow()), shared ? shared->_hglrc : NULL);
		if (hglrc)
			return new GLWinContext(hglrc);
		return nullptr;
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
		HGLRC hrc = 0;

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
			hrc = wglCreateContextAttribsARB(hdc, shareHrc, ctxAttributes);

		return hrc;
	}

	//-------------------------------------------------------------

    class GLWinSurfaceTarget : public GLObject
    {
    public:
		static const GLTypeObject Type = GLTypeObject::Surface;
		virtual GLTypeObject GetType() const { return Type; }

        GLWinSurfaceTarget()
        {

        }
    };

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
		const unsigned MsgBufferSize = 1024;
		static LPTSTR MsgBuffer[MsgBufferSize];
		memset(MsgBuffer, 0, sizeof(MsgBuffer));
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, (LPTSTR)&MsgBuffer, MsgBufferSize, NULL);
		*msg = (char *)MsgBuffer;
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
		_window(0)
	{

	}

	GLWinPlatform::~GLWinPlatform()
	{
		_DestroyWindow(_window);
	}

	void GLWinPlatform::Init()
	{
		_DestroyWindow(_window);
		_window = _CreateWindow("FRE_GLWinPlatform", 1, 1, NULL);
		if (_window)
		{
			HDC hdc = GetDC(_window);
			HGLRC hrc = NULL;

			PIXELFORMATDESCRIPTOR pixelDesc = GetDefaultPixelFormatDesc();

			const int pixelFormat = ::ChoosePixelFormat(hdc, &pixelDesc);
			if (pixelFormat > 0)
			{
				if (::SetPixelFormat(hdc, pixelFormat, &pixelDesc))
					hrc = wglCreateContext(hdc);
			}

			if (hrc)
			{
				wglMakeCurrent(hdc, hrc);

				wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(hrc);
			}
		}
	}

    h_GLContext GLWinPlatform::CreateContext(h_GLContext shared)
    {
		GLObjectPtr object(GLWinContext::Create());
		const uint32 index = Push(object);
        return FormHandle(object->GetType(), index);
    }

    h_GLRenderTarget GLWinPlatform::CreateSurfaceTarget(h_GLContext context, const DarkParams & params)
    {
        return 0;
    }

	bool GLWinPlatform::MakeCurrentContext(h_GLContext context)
	{
		GetTypedObject<GLWinContext>(context);
		return false;
	}

	bool GLWinPlatform::MakeCurrentContext(h_GLContext context, h_GLRenderTarget target)
	{
		GetTypedObject<GLWinContext>(context);
		GetTypedObject<GLWinSurfaceTarget>(target);
		return false;
	}

	bool GLWinPlatform::SwapContext(h_GLContext context, h_GLRenderTarget target)
	{
		GetTypedObject<GLWinContext>(context);
		GetTypedObject<GLWinSurfaceTarget>(target);
		return false;
	}

	void GLWinPlatform::Destroy(int64 handle)
	{
		Erase(GetIndex(handle));
	}

	uint32 GLWinPlatform::Push(const GLObjectPtr & object)
	{
		size_t index = 0;
		for (; index < _objects.size(); ++index)
		{
			if (_objects[index] == nullptr)
			{
				_objects[index] = object;
				return index;
			}
		}

		_objects.push_back(object);
		return index;
	}

	void GLWinPlatform::Erase(uint32 index)
	{
		if (index < _objects.size())
			_objects[index].reset();
	}

	GLObject * GLWinPlatform::Get(uint32 index) const
	{
		if (index < _objects.size())
			return _objects[index].get();
		return nullptr;
	}

	//-----------------------------------------------------------------------

	GLPlatform * GetPlatform()
	{
		return nullptr;
	}
}