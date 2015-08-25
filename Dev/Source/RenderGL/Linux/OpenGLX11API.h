#pragma once

#include "GL/glew.h"
//#include "GL/glx.h"
//#include "GL/glxext.h"

//#include "GLDecl.h"

//#define DECLARE_GL_ENTRYPOINTS(Type, Func) Type Func;
//ENUM_GL_ENTRYPOINTS_ALL(DECLARE_GL_ENTRYPOINTS);

#include "OpenGL4API.h"

namespace FRE
{
	struct OpenGLX11API : public OpenGL4API
	{
	};

	typedef OpenGLX11API FOpenGL;
}
