#include "GLX11Support.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <string>

#define GLX_CONTEXT_MAJOR_VERSION_ARB		0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB		0x2092

typedef int (*PFNGLXQUERYCONTEXTINFOEXTPROC) (Display* dpy, GLXContext context, int attribute, int *value);
typedef Display* (*PFNGLXGETCURRENTDISPLAYPROC) (void);
typedef GLXContext(*PFNGLXCREATECONTEXTATTRIBSARBPROC) (Display* dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);
typedef GLXFBConfig* (*PFNGLXCHOOSEFBCONFIGPROC) (Display *dpy, int screen, const int *attrib_list, int *nelements);
typedef XVisualInfo* (*PFNGLXGETVISUALFROMFBCONFIGPROC) (Display *dpy, GLXFBConfig config);
typedef GLXContext (*PFNGLXCREATENEWCONTEXTPROC) (Display *dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);
typedef void ( * PFNGLXQUERYDRAWABLEPROC) (Display *dpy, GLXDrawable draw, int attribute, unsigned int *value);

//static PFNGLXQUERYCONTEXTINFOEXTPROC glXQueryContext;
//static PFNGLXGETCURRENTDISPLAYPROC glXGetCurrentDisplay;
static PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = 0;
//static PFNGLXQUERYDRAWABLEPROC glXQueryDrawable;
//static PFNGLXCHOOSEFBCONFIGPROC glXChooseFBConfig;
//static PFNGLXGETVISUALFROMFBCONFIGPROC glXGetVisualFromFBConfig;
//static PFNGLXCREATENEWCONTEXTPROC glXCreateNewContext;

template <typename T>
T XGetProcAddress(const std::string & procname)
{
	return (T)glXGetProcAddressARB((const GLubyte *)procname.c_str());
}

void GLX11Support::InitGLX()
{
	//glXQueryContext = XGetProcAddress<decltype(glXQueryContext)>("glXQueryContext");
	//glXGetCurrentDisplay = XGetProcAddress<decltype(glXGetCurrentDisplay)>("glXGetCurrentDisplay");
	glXCreateContextAttribsARB = XGetProcAddress<decltype(glXCreateContextAttribsARB)>("glXCreateContextAttribsARB");
	//glXQueryDrawable = XGetProcAddress<decltype(glXQueryDrawable)>("glXQueryDrawable");
	//glXChooseFBConfig = XGetProcAddress<decltype(glXChooseFBConfig)>("glXChooseFBConfig");
	//glXGetVisualFromFBConfig = XGetProcAddress<decltype(glXGetVisualFromFBConfig)>("glXGetVisualFromFBConfig");
	//glXCreateNewContext = XGetProcAddress<decltype(glXCreateNewContext)>("glXCreateNewContext");
}

//Window GLX11Window::CreateWindow(Display * display, const char * name, unsigned width, unsigned height, Window parent)
//{
//	XVisualInfo * vi = visualInfo;
//
//	/*
//	XVisualInfo * vi = support.XGetVisualFromFBConfig(fbConfig);
//	if (vi == nullptr)
//	return 0;
//	*/
//
//	Colormap colorMap = XCreateColormap(display, XRootWindow(display, vi->screen), vi->visual, AllocNone);
//
//	XSetWindowAttributes attributes;
//	attributes.colormap = colorMap;
//	//attributes.event_mask = ExposureMask | KeyPressMask;
//
//	Window win = XCreateWindow(display, XRootWindow(display, vi->screen),
//		0, 0, 600, 600, 0,
//		vi->depth, InputOutput,
//		vi->visual, CWColormap /*| CWEventMask*/, &attributes);
//
//	XFreeColormap(display, colorMap);
//	//XFree(vi);
//
//	return win;
//}

GLXFBConfig GLX11Support::GetDefaultFBConfig(Display * display)
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

	GLXFBConfig ret = nullptr;

	int fbcount;
	GLXFBConfig * fbc = glXChooseFBConfig(display, DefaultScreen(display), attribs, &fbcount);
	if (fbc)
	{
		ret = fbc[0];
		XFree(fbc);
	}

	return ret;
}

GLXContext GLX11Support::CreateContext(Display * display, GLXFBConfig config, unsigned major, unsigned minor, GLXContext shared, bool debugMode)
{
	if (glXCreateContextAttribsARB)
	{
		int attribs[] =
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB, (int)major,
			GLX_CONTEXT_MINOR_VERSION_ARB, (int)minor,
			0
		};

		GLXContext ctx = glXCreateContextAttribsARB(display, config, shared, true, attribs);
		return ctx;
	}
	return 0;
}

GLXFBConfig GLX11Support::GetFBConfigFromDrawable(Display * display, GLXDrawable drawable)
{
	GLXFBConfig fbConfig = 0;

	//if (glXQueryDrawable)
	{
		int attribs[] =
		{
			GLX_FBCONFIG_ID, 0,
			None
		};

		int numConfigs = 0;
		glXQueryDrawable(display, drawable, GLX_FBCONFIG_ID, (unsigned int *)attribs);
		GLXFBConfig * fbConfigs = glXChooseFBConfig(display, XDefaultScreen(display), attribs, &numConfigs);
		if (numConfigs)
		{
			fbConfig = fbConfigs[0];
			XFree(fbConfigs);
		}
	}

	return fbConfig;
}
