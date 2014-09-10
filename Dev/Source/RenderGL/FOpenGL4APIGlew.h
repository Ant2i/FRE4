#pragma once 

#include "gl\glew.h"
#include "FOpenGL4API.h"

#define FGL_MAX(a, b) a > b ? a : b

struct OpenGL4APIGlew : public OpenGL4API
{
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
			const bool bArrayTexture = Target == GL_TEXTURE_2D_ARRAY || Target == GL_TEXTURE_CUBE_MAP_ARRAY;

			for (uint32 MipIndex = 0; MipIndex < uint32(Levels); ++MipIndex)
			{
				glTexImage3D(
					Target,
					MipIndex,
					InternalFormat,
					FGL_MAX(1, (Width >> MipIndex)),
					FGL_MAX(1, (Height >> MipIndex)),
					bArrayTexture ? Depth : FGL_MAX(1, (Depth >> MipIndex)),
					0,
					Format,
					Type,
					nullptr
					);
			}
		}
	}
};