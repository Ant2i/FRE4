#include "FPlatform.h"

#ifdef PLATFORM_WIN

#include "WinGLAPI.h"

namespace FRE
{
	void OpenGLWindowsAPI::Init(const char * extensions)
	{
		OpenGL4API::Init(extensions);
	}

	bool PlatformInitOpenGL()
	{
		bool isInit = glewInit() == GLEW_OK;
		if (isInit)
			FOpenGL::Init(FOpenGL::GetExtensionString());

#ifdef _DEBUG
		auto capaility = FOpenGL::GetCapability();
#endif

		return isInit;
	}
}

#endif
