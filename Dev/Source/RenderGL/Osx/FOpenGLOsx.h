#pragma once

#include <OpenGL/gl3.h>
#include "FOpenGL3API.h"

struct OpenGLOsxAPI : public OpenGL3API
{
	GL_API_FUNC bool IsDebugContext()
	{
        return false;//glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}
};

typedef OpenGLOsxAPI TOpenGLAPI;
