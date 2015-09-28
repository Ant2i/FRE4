#pragma once
#include "GLPlatform.h"

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#include <windows.h>
#include <GL/gl.h>

class GLPlatformRenderSurface
{
public:
	GLPlatformRenderSurface(HWND hwnd, bool destroy);
	~GLPlatformRenderSurface();

	bool Swap() const;
	void Resize(unsigned width, unsigned height) const;

	void SetPixelFormat(int pixelFormat) const;

	const HWND WindowHandle;
	const HDC DeviceContext;

	static GLPlatformRenderSurface * CreateNew(unsigned w, unsigned h, HWND parent);

private:
	bool _destroy;
};

//-----------------------------------------------------------------------------

//HGLRC CreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shared = nullptr, bool debug = false);

#endif