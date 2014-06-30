#include "FreGLWinContext.h"

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

typedef HGLRC (APIENTRY * PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int *);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

namespace FRE
{
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

	bool GLWinContext::Init(HDC hdc)
	{
		bool result = false;

		HGLRC initHrc = NULL;

		PIXELFORMATDESCRIPTOR pixelDesc = GetDefaultPixelFormatDesc();
		const int pixelFormat = ::ChoosePixelFormat(hdc, &pixelDesc);
		if (pixelFormat > 0)
		{
			if (::SetPixelFormat(hdc, pixelFormat, &pixelDesc))
				initHrc = wglCreateContext(hdc);
		}

		if (initHrc)
		{
			if (wglMakeCurrent(hdc, initHrc))
			{
				wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
				result = wglCreateContextAttribsARB != nullptr;
				wglMakeCurrent(NULL, NULL);
			}
			wglDeleteContext(initHrc);
		}

		return result;
	}

	PIXELFORMATDESCRIPTOR GLWinContext::GetDefaultPixelFormatDesc()
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
}