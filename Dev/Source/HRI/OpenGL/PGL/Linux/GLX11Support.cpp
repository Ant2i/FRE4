#include "GLPlatform.h"
#include "GLX11Support.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <string>
#include <cstring>

#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092

#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C

typedef int(*PFNGLXQUERYCONTEXTINFOEXTPROC)(Display* dpy, GLXContext context,
	int attribute, int *value);
typedef Display* (*PFNGLXGETCURRENTDISPLAYPROC)(void);
typedef GLXContext(*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display* dpy,
	GLXFBConfig config, GLXContext share_context, Bool direct,
	const int *attrib_list);
typedef GLXFBConfig* (*PFNGLXCHOOSEFBCONFIGPROC)(Display *dpy, int screen,
	const int *attrib_list, int *nelements);
typedef XVisualInfo* (*PFNGLXGETVISUALFROMFBCONFIGPROC)(Display *dpy,
	GLXFBConfig config);
typedef GLXContext(*PFNGLXCREATENEWCONTEXTPROC)(Display *dpy,
	GLXFBConfig config, int render_type, GLXContext share_list,
	Bool direct);
typedef void(*PFNGLXQUERYDRAWABLEPROC)(Display *dpy, GLXDrawable draw,
	int attribute, unsigned int *value);

static PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = 0;

template<typename T>
T XGetProcAddress(const std::string & procname)
{
	return (T)glXGetProcAddressARB((const GLubyte *)procname.c_str());
}

Window GLX11Support::CreateWindow(Display * display, GLXFBConfig config, const char * name, unsigned width, unsigned height)
{
	XVisualInfo * vi = glXGetVisualFromFBConfig(display, config);
	if (vi == nullptr)
		return 0;

	Colormap colorMap = XCreateColormap(display,
		XRootWindow(display, vi->screen), vi->visual, AllocNone);

	XSetWindowAttributes attributes;
	attributes.colormap = colorMap;

	Window win = XCreateWindow(display, XRootWindow(display, vi->screen), 0, 0,
		width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap,
		&attributes);
	XFreeColormap(display, colorMap);

	return win;
}

void GLX11Support::GLGetCurrentVersion(int & major, int & minor)
{
	major = 0;
	minor = 0;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	const GLubyte * strVer = glGetString(GL_VERSION);
	if (major == 0 && strVer)
	{
		sscanf((const char *)strVer, "%i.%i", &major, &minor);
	}
}

GLXFBConfig GLX11Support::GetFBConfig(Display * display,
	const PGLConfigDesc & desc)
{
	static int attribs[] =
	{
		GLX_X_RENDERABLE, True,
		GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
		GLX_RED_SIZE, desc.RedSize,
		GLX_GREEN_SIZE, desc.GreenSize,
		GLX_BLUE_SIZE, desc.BlueSize,
		GLX_ALPHA_SIZE, 0,
		GLX_DEPTH_SIZE, desc.DepthSize,
		GLX_STENCIL_SIZE, 0,
		GLX_DOUBLEBUFFER, True,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES, 0,
		GLX_STEREO, desc.Stereo,
		None };

	GLXFBConfig ret = nullptr;

	int fbcount;
	GLXFBConfig * fbc = glXChooseFBConfig(display, DefaultScreen(display),
		attribs, &fbcount);
	if (fbc)
	{
		ret = fbc[0];

		XVisualInfo * vi = glXGetVisualFromFBConfig(display, ret);
		if (vi)
			printf("Visual ID = 0x%x\n", (unsigned int)vi->visualid);
		XFree(fbc);
	}

	return ret;
}

struct GLVer
{
	int major, minor;
};

static const GLVer glVersionList[] =
{
	{ 4, 5 },
	{ 4, 4 },
	{ 4, 3 },
	{ 4, 2 },
	{ 4, 1 },
	{ 4, 0 },
	{ 3, 3 },
	{ 3, 2 },
	{ 3, 1 },
	{ 3, 0 },
	{ 2, 1 },
	{ 2, 0 },
	{ 1, 5 },
	{ 1, 4 },
	{ 1, 3 },
	{ 1, 2 },
	{ 1, 1 },
	{ 1, 0 },
	{ 0, 0 }
};

GLboolean ExtensionSupported(const char *ext, const char *extensionsList)
{
	while (1)
	{
		const char *p = std::strstr(extensionsList, ext);
		if (p)
		{
			int extLen = std::strlen(ext);
			if (p[extLen] == 0 || p[extLen] == ' ')
			{
				return GL_TRUE;
			}
			else
			{
				extensionsList += extLen;
			}
		}
		else
		{
			break;
		}
	}
	return 0;
}

GLXContext _CreateContextAttribs(Display * dpy, GLXFBConfig config, int major, int minor,
	GLXContext shared, bool core, bool direct, bool debug)
{
	GLXContext context = 0;

	static bool init = false;
	if (!init)
	{
		const char * glxExt = glXQueryExtensionsString(dpy, 0);
		if (ExtensionSupported("GLX_ARB_create_context_profile", glxExt))
		{
			glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddress((const GLubyte *) "glXCreateContextAttribsARB");
		}
		init = true;
	}

	if (!glXCreateContextAttribsARB)
		return 0;

	int attribList[20];
	int n = 0;

	if (major)
	{
		attribList[n++] = GLX_CONTEXT_MAJOR_VERSION_ARB;
		attribList[n++] = major;
		attribList[n++] = GLX_CONTEXT_MINOR_VERSION_ARB;
		attribList[n++] = minor;
	}
	if (core)
	{
		attribList[n++] = GLX_CONTEXT_PROFILE_MASK_ARB;
		attribList[n++] = GLX_CONTEXT_CORE_PROFILE_BIT_ARB;
	}
	attribList[n++] = 0;

	context = glXCreateContextAttribsARB(dpy, config, shared, direct, attribList);

	if (context && direct)
	{
		if (!glXIsDirect(dpy, context))
		{
			glXDestroyContext(dpy, context);
			context = 0;
		}
	}

	return context;
}

GLXContext _CreateNewContext(Display * dpy, GLXFBConfig config, GLXContext shared, bool direct)
{
	GLXContext context = glXCreateNewContext(dpy, config, GLX_RGBA_TYPE, shared, direct);

	if (context && direct)
	{
		if (!glXIsDirect(dpy, context))
		{
			glXDestroyContext(dpy, context);
			context = 0;
		}
	}

	return context;
}

GLXContext CreateContext(Display *dpy, GLXFBConfig config, GLXContext shared, bool core, bool debug, bool direct)
{
	GLXContext context = 0;

	if (core)
	{
		int i = 0;
		while (glVersionList[i].major != 0)
		{
			if (glVersionList[i].major == 3 && glVersionList[i].minor == 0)
				break;

			context = _CreateContextAttribs(dpy, config, glVersionList[i].major, glVersionList[i].minor, shared, core, direct, debug);
			if (context)
				break;
			++i;
		}
	}
	else
	{
		context = _CreateNewContext(dpy, config, shared, direct);
	}

	return context;
}

GLXContext GLX11Support::CreateContext(Display * display, GLXFBConfig config, GLXContext shared, bool core, bool debug, bool direct)
{
	return ::CreateContext(display, config, shared, core, debug, direct);

//	GLXContext context = 0;
//	if (core)
//	{
	//	context = ::CreateContext(display, config, shared, true, true);
	//	if (!context)
	//		context = ::CreateContext(display, config, shared, true, false);
//	}
//	else
//	{
//		context = ::CreateContext(display, config, shared, false, true);
//	}
//	return context;
}

GLXFBConfig GetFBConfigFromVisualID(Display * dpy, VisualID visualid)
{
	GLXFBConfig fbConfig = 0;

	if (!fbConfig)
	{
		int minAttribs[] =
		{
			GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT || GLX_PIXMAP_BIT,
			GLX_RENDER_TYPE, GLX_RGBA_BIT,
			GLX_RED_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			None };
		int nConfigs = 0;

		GLXFBConfig * fbConfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy),
			minAttribs, &nConfigs);

		for (int i = 0; i < nConfigs && !fbConfig; i++)
		{
			XVisualInfo *visualInfo = glXGetVisualFromFBConfig(dpy,
				fbConfigs[i]);

			if (visualInfo->visualid == visualid)
				fbConfig = fbConfigs[i];

			XFree(visualInfo);
		}

		XFree(fbConfigs);
	}

	return fbConfig;
}

GLXFBConfig GLX11Support::GetFBConfigFromDrawable(Display * display,
	GLXDrawable drawable)
{
	GLXFBConfig fbConfig = 0;

	unsigned int configId = 0;
	glXQueryDrawable(display, drawable, GLX_FBCONFIG_ID, &configId);
	unsigned int visualId = 0;
	glXQueryDrawable(display, drawable, GLX_VISUAL_ID, &visualId);
	unsigned int width = 0;
	glXQueryDrawable(display, drawable, GLX_WIDTH, &width);

	int attribs[] =
	{
		GLX_FBCONFIG_ID, (int)configId,
		None
	};

	int numConfigs = 0;
	GLXFBConfig * fbConfigs = glXChooseFBConfig(display, XDefaultScreen(display), attribs, &numConfigs);
	if (numConfigs)
	{
		fbConfig = fbConfigs[0];
		XFree(fbConfigs);
	}

	if (!fbConfig)
	{
		XWindowAttributes windowAttrib;
		if (XGetWindowAttributes(display, drawable, &windowAttrib))
		{
			VisualID visualid = XVisualIDFromVisual(windowAttrib.visual);
			fbConfig = GetFBConfigFromVisualID(display, visualid);
		}
	}

	return fbConfig;
}
