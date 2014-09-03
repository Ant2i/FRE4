#include "FOpenGLWindow.h"

#define FRE_WINDOW_GL_CLASS "FRE_GLWNDCLASS"

namespace FRE
{
	GLWinSurfaceTarget::GLWinSurfaceTarget(HWND hwnd, HDC hdc) :
		Hwnd(hwnd),
		Hdc(hdc)
	{

	}

	GLWinSurfaceTarget::~GLWinSurfaceTarget()
	{
		ReleaseDC(Hwnd, Hdc);
		DestroyWindow(Hwnd);
	}

	GLWinSurfaceTarget * CreateTarget(int pixelFormat, HWND parent)
	{
		HINSTANCE hinst = GetModuleHandle(nullptr);
		HWND hwnd = CreateWindowA(FRE_WINDOW_GL_CLASS, "FRE_GLWinSurfaceTarget", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 0, 100, 100, parent, NULL, hinst, NULL);
		if (hwnd)
		{
			HDC hdc = GetDC(hwnd);
			if (hdc)
			{
				PIXELFORMATDESCRIPTOR pixelDest;
				if (SetPixelFormat(hdc, pixelFormat, &pixelDest))
				{
					return new GLWinSurfaceTarget(hwnd, hdc);
				}
				ReleaseDC(hwnd, hdc);
			}
			DestroyWindow(hwnd);
		}
		return nullptr;
	}

	void GLWinSurfaceTarget::Resize(unsigned width, unsigned height)
	{
		MoveWindow(Hwnd, 0, 0, width, height, TRUE);
	}

	bool GLWinSurfaceTarget::Swap() const
	{
		return SwapBuffers(Hdc) == TRUE;
	}

	DWORD WinGetLastError(const char ** msg)
	{
		DWORD error = GetLastError();
		const unsigned msgBufferSize = 1024;
		static LPTSTR msgBuffer[msgBufferSize];
		memset(msgBuffer, 0, sizeof(msgBuffer));
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, (LPTSTR)&msgBuffer, msgBufferSize, NULL);
		*msg = (char *)msgBuffer;
		return error;
	}

	HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent)
	{
		HINSTANCE hinst = GetModuleHandle(nullptr);

		WNDCLASSA wclass;
		memset(&wclass, 0, sizeof(WNDCLASSA));

		wclass.style = CS_OWNDC;
		wclass.hInstance = hinst;
		wclass.lpfnWndProc = DefWindowProc;
		wclass.lpszClassName = FRE_WINDOW_GL_CLASS;

		if (!GetClassInfoA(hinst, FRE_WINDOW_GL_CLASS, &wclass))
			RegisterClassA(&wclass);

		return CreateWindowA(FRE_WINDOW_GL_CLASS, name, WS_POPUP | WS_CLIPCHILDREN, 0, 0, width, height, parent, NULL, hinst, NULL);
	}

	void WinDestroyWindow(HWND hwnd)
	{
		if (hwnd)
			DestroyWindow(hwnd);
	}
}