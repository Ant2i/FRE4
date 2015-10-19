#include "GLX11Support.h"
#include <GL/gl.h>
#include <GL/glx.h>

typedef int (*PFNGLXQUERYCONTEXTINFOEXTPROC) (Display* dpy, GLXContext context, int attribute, int *value);
typedef Display* (*PFNGLXGETCURRENTDISPLAYPROC) (void);
typedef GLXContext(*PFNGLXCREATECONTEXTATTRIBSARBPROC) (Display* dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list);
typedef GLXFBConfig* (*PFNGLXCHOOSEFBCONFIGPROC) (Display *dpy, int screen, const int *attrib_list, int *nelements);
typedef XVisualInfo* (*PFNGLXGETVISUALFROMFBCONFIGPROC) (Display *dpy, GLXFBConfig config);
typedef GLXContext (*PFNGLXCREATENEWCONTEXTPROC) (Display *dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);

static PFNGLXQUERYCONTEXTINFOEXTPROC glXQueryContext;
static PFNGLXGETCURRENTDISPLAYPROC glXGetCurrentDisplay;
static PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
static PFNGLXCHOOSEFBCONFIGPROC glXChooseFBConfig;
static PFNGLXGETVISUALFROMFBCONFIGPROC glXGetVisualFromFBConfig;
static PFNGLXCREATENEWCONTEXTPROC glXCreateNewContext;

template <typename T>
T XGetProcAddress(const string & procname)
{
	return (T)glXGetProcAddressARB((const GLubyte *)procname.c_str());
}

void GLX11Window::InitGLX()
{
	glXQueryContext = XGetProcAddress<decltype(glXQueryContext)>("glXQueryContext");
	glXGetCurrentDisplay = XGetProcAddress<decltype(glXGetCurrentDisplay)>("glXGetCurrentDisplay");
	glXCreateContextAttribsARB = XGetProcAddress<decltype(glXCreateContextAttribsARB)>("glXCreateContextAttribsARB");
	glXChooseFBConfig = XGetProcAddress<decltype(glXChooseFBConfig)>("glXChooseFBConfig");
	glXGetVisualFromFBConfig = XGetProcAddress<decltype(glXGetVisualFromFBConfig)>("glXGetVisualFromFBConfig");
	glXCreateNewContext = XGetProcAddress<decltype(glXCreateNewContext)>("glXCreateNewContext");
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

GLXContext GLX11Window::GLCreateContext(Display * display, GLXFBConfig config, unsigned major, unsigned minor, HGLRC shared, bool debugMode)
{
	if (glXCreateContextAttribsARB)
	{
		int attribs[] =
		{
			GLX_CONTEXT_MAJOR_VERSION_ARB, (int)major,
			GLX_CONTEXT_MINOR_VERSION_ARB, (int)minor,
			0
		};

		GLXContext ctx = glXCreateContextAttribsARB(dpy, fbConfig, 0, true, attribs);
		return ctx;
	}
	return 0;
}