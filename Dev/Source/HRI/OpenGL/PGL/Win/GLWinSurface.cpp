#include "GLWinPlatform.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include "GLWinSupport.h"

#include <memory>

GLPlatformRenderSurface::GLPlatformRenderSurface(HWND hwnd, bool destroy) :
	WindowHandle(hwnd),
	DeviceContext(GetDC(hwnd)),
	_destroy(destroy)
{

}

GLPlatformRenderSurface::~GLPlatformRenderSurface()
{
	ReleaseDC(WindowHandle, DeviceContext);
	if (_destroy)
		DestroyWindow(WindowHandle);
}

void GLPlatformRenderSurface::Resize(unsigned width, unsigned height) const
{
	MoveWindow(WindowHandle, 0, 0, width, height, TRUE);
}

bool GLPlatformRenderSurface::Swap() const
{
	return SwapBuffers(DeviceContext) == TRUE;
}

GLPlatformRenderSurface * GLPlatformRenderSurface::CreateNew(unsigned w, unsigned h, HWND parent)
{
	HWND hwnd = GLWinSupport::WinCreateWindow("GLRenderSurface", w, h, parent);
	if (hwnd)
	{
		std::unique_ptr<GLPlatformRenderSurface> surface(new GLPlatformRenderSurface(hwnd, true));
		return surface.release();
	}
	return nullptr;
}

#endif