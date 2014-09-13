#pragma once

#include "FOpenGL4APIGlew.h"
#include "windows.h"

#include <vector>
#include <memory>

struct OpenGLWindowsAPI : public OpenGL4APIGlew
{
	GL_API_FUNC bool IsDebugContext()
	{
		return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}
};

typedef OpenGLWindowsAPI TOpenGLAPI;

//------------------------------------------------------

struct WGLSurface
{
	WGLSurface(HWND hwnd, HDC hdc);
	~WGLSurface();

	bool Swap() const;
	void Resize(unsigned width, unsigned height);

	HWND Hwnd;
	HDC Hdc;
};

struct WGLContext
{
	WGLContext(HGLRC hrc);
	~WGLContext();

	HGLRC Hglrc;
};

WGLContext * CreateContext(HDC hdc, unsigned major, unsigned minor, WGLContext * shared = nullptr, bool debug = false);
WGLSurface * CreateWindowSurface(int pixelFormat, HWND parent);

bool WGLInitialize(HDC hdc, unsigned major, unsigned minor);
HGLRC WGLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc, bool debug);
PIXELFORMATDESCRIPTOR WGLGetDefaultPixelFormatDesc();

HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
void WinDestroyWindow(HWND hwnd);
DWORD WinGetLastError(const char ** msg);
