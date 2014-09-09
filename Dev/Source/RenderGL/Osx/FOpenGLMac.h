#pragma once

#include "GL/glew.h"
#include "FOpenGL3API.h"

struct OpenGLMacAPI : public OpenGL3API
{
	GL_API_FUNC bool IsDebugContext()
	{
		return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}

	//static void ProcessExtensions(const char * & extensions);
};

typedef OpenGLMacAPI TOpenGLAPI;
