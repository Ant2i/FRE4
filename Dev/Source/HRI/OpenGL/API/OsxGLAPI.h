#pragma once

#include "GL/glew.h"
#include "GLAPI3.h"

namespace FRE
{
	struct OpenGLOsxAPI : public OpenGL3API
	{
		GL_API_FUNC bool IsDebugContext()
		{
            if (glIsEnabled)
                return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
            return false;
		}
	};

	typedef OpenGLOsxAPI FOpenGL;
}
