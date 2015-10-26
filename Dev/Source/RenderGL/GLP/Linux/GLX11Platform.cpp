#include "GLX11Platform.h"
#include "GLX11Support.h"

#include <map>

class GLPlatformContext
{
public:
	GLPlatformContext(Display * display, GLXContext context, GLXFBConfig config) :
		Context(context),
		Config(config),
		_display(display)
	{

	}

	~GLPlatformContext()
	{
		glXDestroyContext(_display, Context);
	}

	const GLXContext Context;
	const GLXFBConfig Config;

private:
	Display * _display;
};

class GLPlatformRenderSurface
{
public:
	GLPlatformRenderSurface(GLXDrawable drawable) :
		Drawable(drawable)
	{

	}

	const GLXDrawable Drawable;
};

class InternalData
{
public:
	InternalData() :
		Debug(false),
		GLMajor(0),
		GLMinor(0),
		_display(nullptr),
		CurrentContext(nullptr)
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

	GLPlatformContext * CurrentContext;

	GLXDrawable GetDrawable(GLXFBConfig config)
	{
		GLXDrawable ret = 0;
		auto it = _tempDrawable.find(config);
		if (it != _tempDrawable.end())
		{
			ret = it->second;
		}
		else
		{
			ret = GLX11Support::CreateWindow(GetDisplay(), config, "Temp", 1, 1);
			_tempDrawable[config] = ret;
		}

		return ret;
	}

private:
	std::map<GLXFBConfig, GLXDrawable> _tempDrawable;

	Display * _display;
};

static InternalData s_GlobalData;

//-----------------------------------------------------------------------------

bool PGLInitialize(unsigned * oMajorVer, unsigned * oMinorVer, bool iDebugMode)
{
	GLX11Support::InitGLX();

	bool result = false;
	Display * display = s_GlobalData.GetDisplay();
	if (display)
	{
		GLXFBConfig config = GLX11Support::GetDefaultFBConfig(display);
		GLXContext ctx = GLX11Support::CreateContext(display, config, 0, 0, nullptr, iDebugMode);
		if (ctx)
		{
			auto drawable = s_GlobalData.GetDrawable(config);
			if (drawable)
			{
				if (glXMakeCurrent(s_GlobalData.GetDisplay(), drawable, nullptr))
				{
					glGetIntegerv​(GL_MAJOR_VERSION, *);
					glGetIntegerv​(GL_MINOR_VERSION, *);

					//s_GlobalData.GLMajor = majorVer;
					//s_GlobalData.GLMinor = minorVer;
					s_GlobalData.Debug = debugMode;

					result = true;
				}
			}

			glXDestroyContext(display, ctx);
		}
	}
	return result;
}

GLPlatformContextP GLPlatformContextCreate(GLSurfaceFormatH hPixelFormat, GLPlatformContextP pSharedContext)
{
	GLXFBConfig fbConfig = (GLXFBConfig)hPixelFormat;

	GLXContext ctx = GLX11Support::CreateContext(s_GlobalData.GetDisplay(), fbConfig, s_GlobalData.GLMajor, s_GlobalData.GLMinor,
			pSharedContext ? pSharedContext->Context : 0, s_GlobalData.Debug);

	if (ctx)
		return new GLPlatformContext(s_GlobalData.GetDisplay(), ctx, fbConfig);

	return nullptr;
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
{
	if (pContext)
		delete pContext;
}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLSurfaceFormatH hPixelFormat, const SurfaceDesc & surfaceDesc)
{
	if (surfaceDesc.External)
	{
		return new GLPlatformRenderSurface((GLXDrawable)surfaceDesc.PlatformData);
	}
	return nullptr;
}

void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
{
	if (pSurface)
		delete pSurface;
}

void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height)
{
}

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	s_GlobalData.CurrentContext = pContext;
	Bool res = false;

	if (pContext)
	{
		if (pSurface)
		{
			GLXFBConfig fbConfig = GLX11Support::GetFBConfigFromDrawable(s_GlobalData.GetDisplay(), pSurface->Drawable);
			res = glXMakeCurrent(s_GlobalData.GetDisplay(), pSurface->Drawable, pContext->Context);
		}
		else
		{
			auto drawable = s_GlobalData.GetDrawable(pContext->Config);
			if (drawable)
				res = glXMakeCurrent(s_GlobalData.GetDisplay(), drawable, pContext->Context);
		}
	}
	else
		res = glXMakeCurrent(s_GlobalData.GetDisplay(), 0, 0);



	if (glXGetCurrentContext() == pContext->Context)
		s_GlobalData.CurrentContext = pContext;

	return res;
}

bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	bool res = false;

	if (pSurface)
	{
		glXSwapBuffers(s_GlobalData.GetDisplay(), pSurface->Drawable);
		res = true;
	}

	return res;
}

GLPlatformContextP GLPlatformGetCurrentContext()
{
	return s_GlobalData.CurrentContext;
}

GLSurfaceFormatH FindSurfaceFormat(const SurfaceFormatDesc & pixelFormatDesc)
{
	return (GLSurfaceFormatH)GLX11Support::GetDefaultFBConfig(s_GlobalData.GetDisplay());
}
