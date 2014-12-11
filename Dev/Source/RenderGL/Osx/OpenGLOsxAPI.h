#pragma once

#include <OpenGL/gl3.h>
#include "OpenGL3API.h"

namespace FRE
{
	struct OpenGLOsxAPI : public OpenGL3API
	{
		GL_API_FUNC bool IsDebugContext()
		{
            return false; //glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
		}
	};

	typedef OpenGLOsxAPI FOpenGL;
}