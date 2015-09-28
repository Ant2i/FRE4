#pragma once

#include "windows.h"

class GLWinSupport
{
public:
	static HGLRC GLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shared, bool debugMode);
	static void GLDeleteContext(HGLRC rc);
	
	static PIXELFORMATDESCRIPTOR GLDefaultPixelFormatDesc();
	static int SetDefaultPixelFormat(HDC hdc);
	
	static HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
	static DWORD WinGetLastError(const char ** msg = nullptr);
};