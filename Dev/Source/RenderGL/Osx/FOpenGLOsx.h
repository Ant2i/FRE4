#pragma once

#include <OpenGL/gl4.h>
#include "FOpenGL4API.h"

struct OpenGLOsxAPI : public OpenGL4API
{
	GL_API_FUNC bool IsDebugContext()
	{
		return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}
};

typedef OpenGLOsxAPI TOpenGLAPI;
