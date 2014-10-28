#pragma once

#include "OpenGLState.h"
#include "GLPlatform.h"

namespace FRE
{
	class GLContext
	{
		GLContext();
		~GLContext();

	private:
		GLContextState _state;
		GLPlatformContextP _glctx;
	};
}