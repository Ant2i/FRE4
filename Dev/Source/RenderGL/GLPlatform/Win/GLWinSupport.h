#pragma once

#include "windows.h"

struct SurfaceFormatDesc;

class GLWinSupport
{
public:
	static HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
	
	static HGLRC GLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shared, bool debugMode, bool coreProfile = true, bool forward = true);
	static void GLDeleteContext(HGLRC rc);

	static PIXELFORMATDESCRIPTOR GLPixelFormatDesc(bool stereo);

	static int ChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR & pfd);
	static bool SetPixelFormat(HDC hdc, int pixelFormat);

	static DWORD WinGetLastError(const char ** msg = nullptr);
};