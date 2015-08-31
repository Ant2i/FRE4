#include "GLPlatformX11.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

class XDisplay
{
public:
	XDisplay()
	{
		_disp = XOpenDisplay(nullptr);
	}

	~XDisplay()
	{
		XCloseDisplay(_disp);
	}

	operator Display *() const
	{
		return _disp;
	}

private:
	Display * _disp;
};

Display * GetDefaultDisplay()
{
	static XDisplay display;
	return display;
}

GLXFBConfig XGLGetDefaultFBConfig()
{
	static int attribs[] =
	{
	GLX_X_RENDERABLE, True,
	GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
	GLX_RENDER_TYPE, GLX_RGBA_BIT,
	GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
	GLX_RED_SIZE, 8,
	GLX_GREEN_SIZE, 8,
	GLX_BLUE_SIZE, 8,
	GLX_ALPHA_SIZE, 8,
	GLX_DEPTH_SIZE, 24,
	GLX_STENCIL_SIZE, 8,
	GLX_DOUBLEBUFFER, True,
	GLX_SAMPLE_BUFFERS, 0,
	GLX_SAMPLES, 0,
	None
	};

	Display * display = GetDefaultDisplay();

	int fbcount;
	GLXFBConfig * fbc = glXChooseFBConfig(display, DefaultScreen(display), attribs, &fbcount);
	if (!fbc)
	{
		GLXFBConfig config = fbc[0];

		XFree(fbc);
	}

	return 0;
}

//-----------------------------------------------------------------------------

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
	static bool init = false;
	if (!init)
	{

	}
	return init;
}

GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP pShared)
{
	return nullptr;
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
{

}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(uint64 params)
{
	return nullptr;
}

void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
{

}

void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height)
{

}

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	return false;
}

bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	return false;
}

GLPlatformContextP GLPlatformGetCurrentContext()
{

	return nullptr;
}

