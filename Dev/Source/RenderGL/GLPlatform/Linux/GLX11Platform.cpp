#include "GLPlatformX11.h"
#include "GLX11Support.h"

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

//static GLXFBConfig DefaultFBConfig = nullptr;

Display * GetDefaultDisplay()
{
	static XDisplay display;
	return display;
}

class InternalData
{
public:
	InternalData() :
		Debug(false),
		GLMajor(0),
		GLMinor(0),
		_display(nullptr)
	{
		_display = XOpenDisplay(nullptr);
	}

	~InternalData()
	{
		if (_display)
			XCloseDisplay(_display);
	}
	
	Display * GetDisplay() const { return _display; }

	unsigned GLMajor;
	unsigned GLMinor;
	bool Debug;

private:
	Display * _display;
}

static InternalData s_GlobalData;

//-----------------------------------------------------------------------------

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
	GLX11Support::InitGLX();

	bool result = false;
	Display * display = s_GlobalData.GetDisplay();
	if (display)
	{
		GLXFBConfig config = GLX11Support::GetDefaultFBConfig(display);
		GLXContext ctx = GLX11Support::CreateContext(display, config, majorVer, minorVer, nullptr, debugMode);
		if (ctx)
		{
			s_GlobalData.GLMajor = majorVer;
			s_GlobalData.GLMinor = minorVer;
			s_GlobalData.Debug = debugMode;

			result = true;
			glXDestroyContext(display, ctx);
		}
	}
	return result;
}

GLPlatformContextP GLPlatformContextCreate(GLSurfaceFormatH hPixelFormat, GLPlatformContextP pSharedContext)
{
	return nullptr;
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
{
	
}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLSurfaceFormatH hPixelFormat, const SurfaceDesc & surfaceDesc)
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

GLSurfaceFormatH FindSurfaceFormat(const SurfaceFormatDesc & pixelFormatDesc)
{
	return 0;
}