#pragma once

#include "windows.h"
#include "GL/gl.h"
#include "GL/wglext.h"

#include "GLDecl.h"

#define DECLARE_GL_ENTRYPOINTS(Type, Func) extern Type Func;
ENUM_GL_ENTRYPOINTS_ALL(DECLARE_GL_ENTRYPOINTS);
