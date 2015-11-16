#include "GLPlatform.h"
#include "GLWinSupport.h"
#include "GLDefs.h"
#include <stdio.h>

static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

#define FRE_WINDOW_GL_CLASS "GL_WIN_PLATFORM_GLWNDCLASS"
#define FRE_WINDOW_GL_NAME "GL_WIN_PLATFORM_SURFACE"


void GetGLVersion(int & oMajor, int & oMinor)
{
	oMajor = 0;
	oMinor = 0;

	glGetIntegerv(GL_MAJOR_VERSION, &oMajor);
	glGetIntegerv(GL_MINOR_VERSION, &oMinor);

	const GLubyte * strVer = glGetString(GL_VERSION);
	if (oMajor == 0 && strVer)
	{
		sscanf_s((const char *)strVer, "%i.%i", &oMajor, &oMinor);
	}
}

int GetNumPixelFormats(HDC hdc)
{
	PIXELFORMATDESCRIPTOR  pfd;
	return DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
}

bool GLWinSupport::InitWGL(WGLInitInfo & oInfo)
{
	oInfo.Major = 0;
	oInfo.Minor = 0;
	oInfo.PixelFormatNum = 0;

	HWND hwnd = GLWinSupport::WinCreateWindow("InitWGL", 1, 1, NULL);
	if (hwnd)
	{
		HDC hdc = GetDC(hwnd);
		if (hdc)
		{
			PGLConfigDesc desc;
			memset(&desc, 0, sizeof(desc));
			desc.RedSize = desc.GreenSize = desc.BlueSize = 8;

			int pixelFormat = ChoosePixelFormat(hdc, GLPixelFormatDesc(desc));
			if (SetPixelFormat(hdc, pixelFormat))
			{
				HGLRC rc = wglCreateContext(hdc);
				if (rc)
				{
					if (wglMakeCurrent(hdc, rc))
					{
						wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

						oInfo.PixelFormatNum = GetNumPixelFormats(hdc);

						GetGLVersion(oInfo.Major, oInfo.Minor);
						wglMakeCurrent(NULL, NULL);

						return true;
					}
					wglDeleteContext(rc);
				}
			}
			ReleaseDC(hwnd, hdc);
		}
		DestroyWindow(hwnd);
	}

	return false;
}

PIXELFORMATDESCRIPTOR GLWinSupport::GLPixelFormatDesc(const PGLConfigDesc & desc)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	memset(&pixelDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pixelDesc.nVersion = 1;
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	if (desc.Stereo)
		pixelDesc.dwFlags |= PFD_STEREO;
		
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cRedBits = desc.RedSize;
	pixelDesc.cGreenBits = desc.GreenSize;
	pixelDesc.cBlueBits = desc.BlueSize;
	pixelDesc.cColorBits = desc.RedSize + desc.GreenSize + desc.BlueSize;
	pixelDesc.cDepthBits = desc.DepthSize;
	
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

HGLRC GLWinSupport::GLCreateContext(HDC hdc, HGLRC shared, unsigned major, unsigned minor, bool debug, bool core, bool forward)
{
	int attributes[20];
	int n = 0;

	if (core)
	{
		attributes[n++] = WGL_CONTEXT_PROFILE_MASK_ARB;
		attributes[n++] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
	}

	if (forward || debug)
	{
		int flags = 0;
		if (forward)
			flags |= WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
		if (debug)
			flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

		attributes[n++] = WGL_CONTEXT_FLAGS_ARB;
		attributes[n++] = flags;
	}

	if (major)
	{
		attributes[n++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
		attributes[n++] = major;
		attributes[n++] = WGL_CONTEXT_MINOR_VERSION_ARB;
		attributes[n++] = minor;
	}

	attributes[n++] = 0;

	HGLRC context = 0;
	if (core && wglCreateContextAttribsARB)
		context = wglCreateContextAttribsARB(hdc, shared, attributes);
	else
		context = wglCreateContext(hdc);

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
