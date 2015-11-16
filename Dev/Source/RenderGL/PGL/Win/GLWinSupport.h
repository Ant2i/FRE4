#pragma once

#include "windows.h"
#include <GL/gl.h>

struct PGLConfigDesc;

struct WGLInitInfo
{
	int Major;
	int Minor;
	int PixelFormatNum;
};

class GLWinSupport
{
public:
	static bool InitWGL(WGLInitInfo & oInfo);

	static HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
	
	static HGLRC GLCreateContext(HDC hdc, HGLRC shared, unsigned major, unsigned minor, bool debugMode, bool coreProfile = false, bool forward = false);
	static void GLDeleteContext(HGLRC rc);

	static PIXELFORMATDESCRIPTOR GLPixelFormatDesc(const PGLConfigDesc & desc);

	static int ChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR & pfd);
	static bool SetPixelFormat(HDC hdc, int pixelFormat);

	static DWORD WinGetLastError(const char ** msg = nullptr);
};