#include <GL/glx.h>


class GLX11Support
{
public:
	static void InitGLX();

	//static Window CreateWindow(Display * display, const char * name, unsigned width, unsigned height, Window parent);

	static GLXContext GLCreateContext(Display * display, GLXFBConfig config, unsigned major, unsigned minor, HGLRC shared, bool debugMode);
	//static void GLDeleteContext(HGLRC rc);

	//static PIXELFORMATDESCRIPTOR GLPixelFormatDesc(bool stereo);

	//static int ChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR & pfd);
	//static bool SetPixelFormat(HDC hdc, int pixelFormat);

	static int GetLastError(const char ** msg = nullptr);
};
