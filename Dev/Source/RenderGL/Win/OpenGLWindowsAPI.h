#pragma once

#include "OpenGLWindowsAPIDecl.h"
#include "OpenGL4API.h"

namespace FRE
{
	struct OpenGLWindowsAPI : public OpenGL4API
	{
		static void Init(const char * extensions);

		GL_API_FUNC bool IsDebugContext()
		{
			return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
		}

		GL_API_FUNC void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)
		{
			if (glObjectLabel)
				glObjectLabel(Type, Object, -1, Name);
		}

		GL_API_FUNC void PushGroupMarker(const ANSICHAR * Name)
		{
			if (glPushDebugGroup)
				glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 1, -1, Name);
		}

		GL_API_FUNC void PopGroupMarker()
		{
			if (glPopDebugGroup)
				glPopDebugGroup();
		}

		GL_API_FUNC bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, uint32 Flags)
		{
			if (glTexStorage2D)
			{
				glTexStorage2D(Target, Levels, InternalFormat, Width, Height);
				return true;
			}
			return false;
		}

		GL_API_FUNC void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type)
		{
			if (glTexStorage3D)
			{
				glTexStorage3D(Target, Levels, InternalFormat, Width, Height, Depth);
			}
			else
			{
				__glTexStorage3D(Target, Levels, InternalFormat, Width, Height, Depth, Format, Type);
			}
		}
	};

	typedef OpenGLWindowsAPI FOpenGL;
}