#pragma once
#include "GLPlatform.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include <windows.h>
#include <GL/gl.h>

class GLPlatformRenderSurface
{
public:
	GLPlatformRenderSurface(HWND hwnd, HDC hdc);
	~GLPlatformRenderSurface();

	bool Swap() const;
	void Resize(unsigned width, unsigned height);

	const HWND WindowHandle;
	const HDC DeviceContext;
};

//-----------------------------------------------------------------------------

HGLRC CreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shared = nullptr, bool debug = false);
GLPlatformRenderSurface * CreateWindowSurface(int pixelFormat, HWND parent);

//-----------------------------------------------------------------------------

bool WGLInitialize(HDC hdc, unsigned major, unsigned minor);
HGLRC WGLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc, bool debug);
PIXELFORMATDESCRIPTOR WGLGetDefaultPixelFormatDesc();

//-----------------------------------------------------------------------------

HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
void WinDestroyWindow(HWND hwnd);
DWORD WinGetLastError(const char ** msg);

#endif