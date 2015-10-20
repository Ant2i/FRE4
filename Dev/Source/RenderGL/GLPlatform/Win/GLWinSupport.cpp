#include "GLPlatform.h"
#include "GLWinSupport.h"
#include "GLDefs.h"

static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

#define FRE_WINDOW_GL_CLASS "GL_WIN_PLATFORM_GLWNDCLASS"
#define FRE_WINDOW_GL_NAME "GL_WIN_PLATFORM_SURFACE"

PIXELFORMATDESCRIPTOR GLWinSupport::GLPixelFormatDesc(bool stereo)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	memset(&pixelDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pixelDesc.nVersion = 1;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	if (stereo)
		pixelDesc.dwFlags |= PFD_STEREO;
		
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cRedBits = 8;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cColorBits = 24;
	
	return pixelDesc;
}

bool GLWinSupport::SetPixelFormat(HDC hdc, int pixelFormat)
{
	if (pixelFormat)
	{
		PIXELFORMATDESCRIPTOR cpfd;
		BOOL res = ::SetPixelFormat(hdc, pixelFormat, &cpfd);
		return res == TRUE;
	}
	return false;
}

int GLWinSupport::ChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR & pfd)
{
	int pixelFormat = ::ChoosePixelFormat(hdc, &pfd);
	return pixelFormat;
}

HGLRC GLWinSupport::GLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shared, bool debug, bool coreProfile, bool forward)
{
	HGLRC context = 0;

	auto ctxMask = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
	if (coreProfile)
		ctxMask = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;

	auto ctxFlags = 0;
	if (forward)
		ctxFlags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
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
	{
		HGLRC tempRC = wglCreateContext(hdc);
		if (tempRC)
		{
			if (wglMakeCurrent(hdc, tempRC))
			{
				wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
				wglMakeCurrent(hdc, NULL);
			}
			wglDeleteContext(tempRC);
		}
	}

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
