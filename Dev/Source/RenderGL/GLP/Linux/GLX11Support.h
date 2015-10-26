#include <GL/glx.h>

class GLX11Support
{
public:
	static void InitGLX();

	static Window CreateWindow(Display * display, GLXFBConfig config, const char * name, unsigned width, unsigned height);

	static GLXContext CreateContext(Display * display, GLXFBConfig config, unsigned major, unsigned minor, GLXContext shared, bool debugMode);

	static GLXFBConfig GetFBConfigFromDrawable(Display * display, GLXDrawable drawable);
	static GLXFBConfig GetDefaultFBConfig(Display * display);

	static void GLGetCurrentVersion(int & major, int & minor);

	//static void GLDeleteContext(HGLRC rc);

	//static PIXELFORMATDESCRIPTOR GLPixelFormatDesc(bool stereo);

	//static int ChoosePixelFormat(HDC hdc, const PIXELFORMATDESCRIPTOR & pfd);
	//static bool SetPixelFormat(HDC hdc, int pixelFormat);

	static int GetLastError(const char ** msg = nullptr);
};
