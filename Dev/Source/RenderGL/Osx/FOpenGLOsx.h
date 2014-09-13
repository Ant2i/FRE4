#pragma once

#include "FOpenGL4APIGlew.h"

struct OpenGLOsxAPI : public OpenGL4APIGlew
{
	GL_API_FUNC bool IsDebugContext()
	{
		return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}
};

typedef OpenGLOsxAPI TOpenGLAPI;
