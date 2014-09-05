#pragma once

#include "FOpenGL3.h"

struct OpenGL4API : public OpenGL3API
{
	GL_API_FUNC void BlendFuncSeparatei(GLuint Buf, GLenum SrcRGB, GLenum DstRGB, GLenum SrcAlpha, GLenum DstAlpha)
	{
		glBlendFuncSeparatei(Buf, SrcRGB, DstRGB, SrcAlpha, DstAlpha);
	}
	
	GL_API_FUNC void BlendEquationSeparatei(GLuint Buf, GLenum ModeRGB, GLenum ModeAlpha)
	{
		glBlendEquationSeparatei(Buf, ModeRGB, ModeAlpha);
	}

	GL_API_FUNC void BlendFunci(GLuint Buf, GLenum Src, GLenum Dst)
	{
		glBlendFunci(Buf, Src, Dst);
	}
	
	GL_API_FUNC void BlendEquationi(GLuint Buf, GLenum Mode)
	{
		glBlendEquationi(Buf, Mode);
	}
	
	GL_API_FUNC void PatchParameteri(GLenum Pname, GLint Value)
	{
		glPatchParameteri(Pname, Value);
	}
	
	GL_API_FUNC void BindImageTexture(GLuint Unit, GLuint Texture, GLint Level, GLboolean Layered, GLint Layer, GLenum Access, GLenum Format)
	{
		glBindImageTexture(Unit, Texture, Level, Layered, Layer, Access, Format);
	}
	
	GL_API_FUNC void DispatchCompute(GLuint NumGroupsX, GLuint NumGroupsY, GLuint NumGroupsZ)
	{
		glDispatchCompute(NumGroupsX, NumGroupsY, NumGroupsZ);
	}

	GL_API_FUNC void MemoryBarrier(GLbitfield Barriers)
	{
		glMemoryBarrier(Barriers);
	}

	static void ProcessQueryGLInt();
	static void ProcessExtensions(const char * & ext);

	//GL_API_FUNC GLint GetMaxComputeTextureImageUnits() { check(MaxComputeTextureImageUnits != -1); return MaxComputeTextureImageUnits; }
	//GL_API_FUNC GLint GetMaxComputeUniformComponents() { check(MaxComputeUniformComponents != -1); return MaxComputeUniformComponents; }

//protected:
	//static GLint MaxComputeTextureImageUnits;
	//static GLint MaxComputeUniformComponents;
};
