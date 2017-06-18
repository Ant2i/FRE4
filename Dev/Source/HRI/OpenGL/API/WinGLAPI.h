#pragma once

#include "GL/glew.h"
#include "GLAPI4.h"

namespace FRE
{
	struct OpenGLWindowsAPI : public OpenGL4API
	{
		static void Init(const char * extensions);

		GL_API_FUNC bool IsDebugContext()
		{
			return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
		}

		GL_API_FUNC void LabelObject(GLenum type, GLuint object, const ANSICHAR* name)
		{
			if (glObjectLabel)
				glObjectLabel(type, object, -1, name);
		}

		GL_API_FUNC void PushGroupMarker(const ANSICHAR * name)
		{
			if (glPushDebugGroup)
				glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 1, -1, name);
		}

		GL_API_FUNC void PopGroupMarker()
		{
			if (glPopDebugGroup)
				glPopDebugGroup();
		}

		GL_API_FUNC bool TexStorage2D(GLenum target, GLint levels, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLuint flags)
		{
			if (glTexStorage2D)
			{
				glTexStorage2D(target, levels, internalformat, width, height);
				return true;
			}

			return OpenGL4API::TexStorage2D(target, levels, internalformat, width, height, format, type, flags);
		}

		GL_API_FUNC void TexStorage3D(GLenum target, GLint levels, GLint internalformat, GLsizei width, GLsizei height, GLsizei Depth, GLenum format, GLenum type)
		{
			if (glTexStorage3D)
			{
				glTexStorage3D(target, levels, internalformat, width, height, Depth);
			}
			else
			{
				OpenGL4API::TexStorage3D(target, levels, internalformat, width, height, Depth, format, type);
			}
		}
	};

	typedef OpenGLWindowsAPI FOpenGL;
}
