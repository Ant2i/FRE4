#pragma once

#include "OpenGLBase.h"
#include "OpenGLState.h"

namespace FRE
{
	class GLContext
	{
	public:
		GLContext();
		~GLContext();

	private:
		GLContextState _state;
		GLPlatformContextP _glctx;
	};
}