#include <GL/glx.h>

struct PGLConfigDesc;

class GLX11Support
{
public:
	static Window CreateWindow(Display * display, GLXFBConfig config, const char * name, unsigned width, unsigned height);

	static GLXContext CreateContext(Display * display, GLXFBConfig config, GLXContext shared, bool core, bool debug, bool direct);

	static GLXFBConfig GetFBConfigFromDrawable(Display * display, GLXDrawable drawable);
	static GLXFBConfig GetFBConfig(Display * display, const PGLConfigDesc & desc);

	static void GLGetCurrentVersion(int & major, int & minor);

	static int GetLastError(const char ** msg = nullptr);
};
