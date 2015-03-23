#include "OpenGLWindowsAPI.h"

namespace FRE
{
	void OpenGLWindowsAPI::Init(const char * extensions)
	{
		__super::Init(extensions);
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