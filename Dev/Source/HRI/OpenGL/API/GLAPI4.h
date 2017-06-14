#pragma once

#include "GLAPI3.h"

#define OPENGL4_API

namespace FRE
{
	struct OpenGL4API : public OpenGL3API
	{
		static void Init(const char * extensions);

		GL_API_FUNC void BlendFuncSeparatei(GLuint indexDrawBuffer, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
		{
			glBlendFuncSeparatei(indexDrawBuffer, srcRGB, dstRGB, srcAlpha, dstAlpha);
		}

		GL_API_FUNC void BlendEquationSeparatei(GLuint indexDrawBuffer, GLenum modeRGB, GLenum modeAlpha)
		{
			glBlendEquationSeparatei(indexDrawBuffer, modeRGB, modeAlpha);
		}

		GL_API_FUNC void BlendFunci(GLuint indexDrawBuffer, GLenum src, GLenum dst)
		{
			glBlendFunci(indexDrawBuffer, src, dst);
		}

		GL_API_FUNC void BlendEquationi(GLuint indexDrawBuffer, GLenum mode)
		{
			glBlendEquationi(indexDrawBuffer, mode);
		}

		GL_API_FUNC void PatchParameteri(GLenum pName, GLint value)
		{
			glPatchParameteri(pName, value);
		}

		GL_API_FUNC void BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
		{
			glBindImageTexture(unit, texture, level, layered, layer, access, format);
		}

		GL_API_FUNC void DispatchCompute(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ)
		{
			glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
		}

		GL_API_FUNC void MemoryBarrier(GLbitfield barriers)
		{
			glMemoryBarrier(barriers);
		}

		GL_API_FUNC void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth)
		{
			glCopyImageSubData(SrcName, SrcTarget, SrcLevel, SrcX, SrcY, SrcZ, DstName, DstTarget, DstLevel, DstX, DstY, DstZ, Width, Height, Depth);
		}
	};
}
