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

		GLPlatformContextP GetPlatformContext() const
		{
			return _platformContext;
		}

	private:
		GLContextState _state;
		GLPlatformContextP _platformContext = nullptr;
	};
}