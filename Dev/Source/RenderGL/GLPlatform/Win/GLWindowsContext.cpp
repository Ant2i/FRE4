#include "GLPlatformWindows.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

GLPlatformContext * CreateContext(HDC hdc, unsigned major, unsigned minor, GLPlatformContext * shared, bool debug)
{
	HGLRC ctx = WGLCreateContext(hdc, major, minor, shared ? shared->ContextHandle : NULL, debug);
	return ctx ? new GLPlatformContext(ctx) : nullptr;
}

GLPlatformContext::GLPlatformContext(HGLRC hrc) :
	ContextHandle(hrc)
{

}

GLPlatformContext::~GLPlatformContext()
{
	if (ContextHandle && ContextHandle == wglGetCurrentContext())
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(ContextHandle);
	}
}

HGLRC WGLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc, bool debug)
{
	HGLRC context = 0;

	auto ctxMask = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
	auto ctxFlags = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
	if (debug)
		ctxFlags |= WGL_CONTEXT_DEBUG_BIT_ARB;

	int ctxAttributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_FLAGS_ARB, ctxFlags,
		WGL_CONTEXT_PROFILE_MASK_ARB, ctxMask,
		0
	};

	if (!wglCreateContextAttribsARB)
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	if (wglCreateContextAttribsARB)
		context = wglCreateContextAttribsARB(hdc, shareHrc, ctxAttributes);

	return context;
}

bool WGLInitialize(HDC hdc, unsigned major, unsigned minor)
{
	bool result = false;

	HGLRC initHrc = NULL;

	PIXELFORMATDESCRIPTOR pixelDesc = WGLGetDefaultPixelFormatDesc();
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
			HGLRC hrc = WGLCreateContext(hdc, major, minor, NULL, false);
			if (hrc)
			{
				if (wglMakeCurrent(hdc, hrc) != FALSE)
				{
					result = true;
				}

				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(hrc);
			}
		}
		wglDeleteContext(initHrc);
	}

	return result;
}

PIXELFORMATDESCRIPTOR WGLGetDefaultPixelFormatDesc()
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

#endif