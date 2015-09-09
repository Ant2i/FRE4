#include "GLPlatformWindows.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#define FRE_WINDOW_GL_CLASS "GL_WIN_PLATFORM_GLWNDCLASS"
#define FRE_WINDOW_GL_NAME "GL_WIN_PLATFORM_SURFACE"

GLPlatformRenderSurface::GLPlatformRenderSurface(HWND hwnd, HDC hdc) :
	WindowHandle(hwnd),
	DeviceContext(hdc)
{

}

GLPlatformRenderSurface::~GLPlatformRenderSurface()
{
	ReleaseDC(WindowHandle, DeviceContext);
	DestroyWindow(WindowHandle);
}

GLPlatformRenderSurface * CreateWindowSurface(int pixelFormat, HWND parent)
{
	HINSTANCE hinst = GetModuleHandle(nullptr);
	HWND windowHandle = CreateWindowA(FRE_WINDOW_GL_CLASS, FRE_WINDOW_GL_NAME, WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 0, 100, 100, parent, NULL, hinst, NULL);
	if (windowHandle)
	{
		HDC deviceContext = GetDC(windowHandle);
		if (deviceContext)
		{
			PIXELFORMATDESCRIPTOR pixelDest;
			if (SetPixelFormat(deviceContext, pixelFormat, &pixelDest))
				return new GLPlatformRenderSurface(windowHandle, deviceContext);

			ReleaseDC(windowHandle, deviceContext);
		}
		DestroyWindow(windowHandle);
	}
	return nullptr;
}

void GLPlatformRenderSurface::Resize(unsigned width, unsigned height)
{
	MoveWindow(WindowHandle, 0, 0, width, height, TRUE);
}

bool GLPlatformRenderSurface::Swap() const
{
	return SwapBuffers(DeviceContext) == TRUE;
}

//-----------------------------------------------------------------------------

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

void WinDestroyWindow(HWND hwnd)
{
	if (hwnd)
		DestroyWindow(hwnd);
}

#endif