#include "GLWinSupport.h"
#include "GLDefs.h"

#include <memory>

static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

#define FRE_WINDOW_GL_CLASS "GL_WIN_PLATFORM_GLWNDCLASS"
#define FRE_WINDOW_GL_NAME "GL_WIN_PLATFORM_SURFACE"

PIXELFORMATDESCRIPTOR GLWinSupport::GLDefaultPixelFormatDesc()
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

int GLWinSupport::SetDefaultPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd = GLDefaultPixelFormatDesc();
	int pixelformat = ChoosePixelFormat(hdc, &pfd);
	if (pixelformat)
	{
		BOOL res = SetPixelFormat(hdc, pixelformat, &pfd);
		if (res)
			return pixelformat;
	}

	return 0;
}

HGLRC GLWinSupport::GLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shared, bool debug)
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
		context = wglCreateContextAttribsARB(hdc, shared, ctxAttributes);

	return context;
}

void GLWinSupport::GLDeleteContext(HGLRC rc)
{
	BOOL res = wglDeleteContext(rc);
}

HWND GLWinSupport::WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent)
{
	HINSTANCE hInst = GetModuleHandle(nullptr);

	WNDCLASSA wClass;
	memset(&wClass, 0, sizeof(WNDCLASSA));

	wClass.style = CS_OWNDC;
	wClass.hInstance = hInst;
	wClass.lpfnWndProc = DefWindowProc;
	wClass.lpszClassName = FRE_WINDOW_GL_CLASS;

	if (!GetClassInfoA(hInst, FRE_WINDOW_GL_CLASS, &wClass))
		RegisterClassA(&wClass);

	return CreateWindowA(FRE_WINDOW_GL_CLASS, name, WS_POPUP | WS_CLIPCHILDREN, 0, 0, width, height, parent, NULL, hInst, NULL);
}

DWORD GLWinSupport::WinGetLastError(const char ** msg)
{
	DWORD error = GetLastError();
	const unsigned msgBufferSize = 1024;
	static LPTSTR msgBuffer[msgBufferSize];
	if (msg)
	{
		memset(msgBuffer, 0, sizeof(msgBuffer));
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, (LPTSTR)&msgBuffer, msgBufferSize - 1, NULL);
		*msg = (char *)msgBuffer;
	}
	return error;
}
