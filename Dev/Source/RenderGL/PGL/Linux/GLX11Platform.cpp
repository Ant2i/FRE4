#include "GLX11Platform.h"
#include "GLX11Support.h"

#include <map>
#include <cstring>

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
		Direct(false),
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
	bool Direct;

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

GLXContext CreateBestContext(Display * display, GLXFBConfig config, bool debug)
{
	struct
	{
		bool core;
		bool direct;
	}
	params[4] =
	{
		{true, true},
		{true, false},
		{false, true},
		{false, false}
	};

	for (int i = 0; i < 4; ++i)
	{
		auto & p = params[i];
		GLXContext context = GLX11Support::CreateContext(display, config, nullptr, p.core, debug, p.direct);
		if (context)
			return context;
	}

	return 0;

	//GLXContext context = GLX11Support::CreateContext(display, config, nullptr, true, debug);
	//if (!context)
		//context = GLX11Support::CreateContext(display, config, nullptr, false, debug);
	//return context;
}

bool PGLInitialize(unsigned * oMajorVer, unsigned * oMinorVer, bool iDebugMode)
{
	bool result = false;
	Display * display = s_GlobalData.GetDisplay();
	if (display)
	{
		int glx_major, glx_minor;
		glXQueryVersion(display, &glx_major, &glx_minor);

		//Check glx version >= 1.3
		if (!(glx_minor < 3 || glx_major < 1))
		{
			GLXFBConfig config = GLX11Support::GetFBConfig(display, PGLDefaultConfigDesc());
			GLXContext ctx = CreateBestContext(display, config, iDebugMode);
			if (ctx)
			{
				auto drawable = s_GlobalData.GetDrawable(config);
				if (drawable)
				{
					if (glXMakeCurrent(s_GlobalData.GetDisplay(), drawable, ctx))
					{
						int major, minor;
						GLX11Support::GLGetCurrentVersion(major, minor);

						s_GlobalData.GLMajor = major;
						s_GlobalData.GLMinor = minor;
						s_GlobalData.Debug = iDebugMode;
						s_GlobalData.Direct = glXIsDirect(display, ctx);
						result = true;
					}
				}

				glXDestroyContext(display, ctx);
			}
		}
	}

	if (oMajorVer) *oMajorVer = s_GlobalData.GLMajor;
	if (oMinorVer) *oMinorVer = s_GlobalData.GLMinor;

	return result;
}

void PGLTerminate()
{

}

PGLContext PGLContextCreate(PGLConfig iConfig, PGLContext iSharedContext, const PGLContextDesc * iDesc)
{
	if (iConfig)
	{
		GLXFBConfig fbConfig = (GLXFBConfig)iConfig;
		GLXContext context = 0;
		GLXContext shared = iSharedContext ? ((GLPlatformContext*)iSharedContext)->Context : 0;

		if (iDesc)
		{
			context = GLX11Support::CreateContext(s_GlobalData.GetDisplay(), fbConfig, shared, iDesc->CoreProfile, s_GlobalData.Debug, s_GlobalData.Direct);
		}
		else
		{
			context = GLX11Support::CreateContext(s_GlobalData.GetDisplay(), fbConfig, shared, true, s_GlobalData.Debug, s_GlobalData.Direct);
			if (!context)
				context = GLX11Support::CreateContext(s_GlobalData.GetDisplay(), fbConfig, shared, false, s_GlobalData.Debug, s_GlobalData.Direct);
		}

		if (context)
			return new GLPlatformContext(s_GlobalData.GetDisplay(), context, fbConfig);
	}

	return nullptr;
}

void PGLContextDestroy(PGLContext iContext)
{
	if (iContext)
	{
		GLPlatformContext * context = (GLPlatformContext*)iContext;
		delete context;
	}
}


PGLSurface PGLSurfaceCreate(PGLConfig iConfig, PGLNativeWindowType iWindow, const PGLSurfaceDesc * iDesc)
{
	if (iWindow && iConfig)
	{
		GLXDrawable drawable = (GLXDrawable)iWindow;
		GLXFBConfig config = (GLXFBConfig)iConfig;

		if (GLX11Support::GetFBConfigFromDrawable(s_GlobalData.GetDisplay(), drawable) == config)
			return new GLPlatformRenderSurface((GLXDrawable)iWindow);
	}
	return nullptr;
}

void PGLSurfaceDestroy(PGLSurface iSurface)
{
	if (iSurface)
	{
		GLPlatformRenderSurface * surface = (GLPlatformRenderSurface *)iSurface;
		delete surface;
	}
}

bool PGLContextMakeCurrent(PGLContext iContext, PGLSurface iSurface)
{
	s_GlobalData.CurrentContext = 0;
	Bool res = false;

	GLPlatformContext * context = (GLPlatformContext*)iContext;
	GLPlatformRenderSurface * surface = (GLPlatformRenderSurface *)iSurface;

	if (context)
	{
		if (surface)
		{
			GLXFBConfig fbConfig = GLX11Support::GetFBConfigFromDrawable(s_GlobalData.GetDisplay(), surface->Drawable);
			res = glXMakeCurrent(s_GlobalData.GetDisplay(), surface->Drawable, context->Context);
		}
		else
		{
			auto drawable = s_GlobalData.GetDrawable(context->Config);
			if (drawable)
				res = glXMakeCurrent(s_GlobalData.GetDisplay(), drawable, context->Context);
		}
	}
	else
	{
		res = glXMakeCurrent(s_GlobalData.GetDisplay(), 0, 0);
	}

	if (res)
		s_GlobalData.CurrentContext = context;

	return res;
}

bool PGLSwapBuffers(PGLSurface iSurface)
{
	bool res = false;

	GLPlatformRenderSurface * surface = (GLPlatformRenderSurface *)iSurface;
	if (surface)
	{
		glXSwapBuffers(s_GlobalData.GetDisplay(), surface->Drawable);
		res = true;
	}

	return res;
}

PGLContext PGLGetCurrentContext()
{
	return s_GlobalData.CurrentContext;
}

PGLConfigDesc PGLDefaultConfigDesc()
{
	PGLConfigDesc desc;
	memset(&desc, 0, sizeof(desc));
	desc.RedSize = desc.GreenSize = desc.BlueSize = 8;
	return desc;
}

PGLConfig PGLChooseConfig(const PGLConfigDesc * iDesc)
{
	if (iDesc)
		return GLX11Support::GetFBConfig(s_GlobalData.GetDisplay(), *iDesc);
	return 0;
}

bool PGLGetConfigDesc(PGLConfig iConfig, PGLConfigDesc * oDesc)
{
	return false;
}
