#pragma once

#include "GL/glew.h"
#include "GLAPI4.h"

namespace FRE
{
	struct OpenGLX11API : public OpenGL4API
	{
	};

	typedef OpenGLX11API FOpenGL;
}