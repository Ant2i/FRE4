#include "OpenGLWindowsAPI.h"
#include "FreAssert.h"

#define DEFINE_GL_ENTRYPOINTS(Type,Func) Type Func = NULL;
ENUM_GL_ENTRYPOINTS_ALL(DEFINE_GL_ENTRYPOINTS);

#define WIN_GET_GL_ENTRYPOINTS(Type,Func) Func = (Type)wglGetProcAddress(#Func);
#define WIN_CHECK_GL_ENTRYPOINTS(Type, Func) WIN_CheckNullPtr &= Func != nullptr;

namespace FRE
{
	void OpenGLWindowsAPI::Init(const char * extensions)
	{
		__super::Init(extensions);
	}

	bool PlatformInitOpenGL()
	{
		ENUM_GL_ENTRYPOINTS_ALL(WIN_GET_GL_ENTRYPOINTS);
		bool WIN_CheckNullPtr = true;
		ENUM_GL_ENTRYPOINTS(WIN_CHECK_GL_ENTRYPOINTS);
		FRE_ASSERT(WIN_CheckNullPtr == true);

		if (WIN_CheckNullPtr)
			FOpenGL::Init(FOpenGL::GetExtensionString());

#ifdef _DEBUG
		auto capaility = FOpenGL::GetCapability();
#endif

		return WIN_CheckNullPtr;
	}
}