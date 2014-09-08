#pragma once

#include "FOpenGL3API.h"

struct OpenGL4API : public OpenGL3API
{
	static void Init(const char * & extensions);

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
	
	GL_API_FUNC void BindImageTexture(GLuint unit, GLuint hTexture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
	{
		glBindImageTexture(unit, hTexture, level, layered, layer, access, format);
	}
	
	GL_API_FUNC void DispatchCompute(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ)
	{
		glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
	}

	GL_API_FUNC void MemoryBarrier(GLbitfield barriers)
	{
		glMemoryBarrier(barriers);
	}

	static void ProcessQueryGLInt();
	static void ProcessExtensions(const char * & ext);

	//GL_API_FUNC GLint GetMaxComputeTextureImageUnits() { check(MaxComputeTextureImageUnits != -1); return MaxComputeTextureImageUnits; }
	//GL_API_FUNC GLint GetMaxComputeUniformComponents() { check(MaxComputeUniformComponents != -1); return MaxComputeUniformComponents; }

//protected:
	//static GLint MaxComputeTextureImageUnits;
	//static GLint MaxComputeUniformComponents;
};
