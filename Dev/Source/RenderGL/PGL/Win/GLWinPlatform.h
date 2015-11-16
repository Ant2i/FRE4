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

	const HWND WindowHandle;
	const HDC DeviceContext;

	static GLPlatformRenderSurface * CreateNew(unsigned w = 1, unsigned h = 1, HWND parent = NULL);

private:
	bool _destroy;
};


#endif