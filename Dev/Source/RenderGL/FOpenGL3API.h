#pragma once

#include "FOpenGLAPI.h"

#define DEF_OPENGL_3

struct OpenGL3API : public OpenGLAPI
{
	static void Init(const char * & extensions);

	GL_API_FUNC void QueryTimestampCounter(GLuint hQuery)
	{
		glQueryCounter(hQuery, GL_TIMESTAMP);
	}

	GL_API_FUNC void BeginQuery(GLenum type, GLuint hQuery)
	{
		glBeginQuery(type, hQuery);
	}

	GL_API_FUNC void EndQuery(GLenum type)
	{
		glEndQuery(type);
	}

	GL_API_FUNC void GetQueryObject(GLuint hQuery, QueryMode mode, uint64* result)
	{
		GLenum queryName = (mode == QueryMode::Result) ? GL_QUERY_RESULT : GL_QUERY_RESULT_AVAILABLE;
		GLuint64 res = 0;
		glGetQueryObjectui64v(hQuery, queryName, &res);
		*result = res;
	}

	GL_API_FUNC void ReadBuffer(GLenum mode)
	{
		glReadBuffer(mode);
	}

	GL_API_FUNC void DrawBuffer(GLenum mode)
	{
		glDrawBuffer(mode);
	}

	GL_API_FUNC void DeleteSync(UGLsync hSync)
	{
		glDeleteSync(hSync);
	}

	GL_API_FUNC UGLsync FenceSync(GLenum condition, GLbitfield flags)
	{
		return glFenceSync(condition, flags);
	}

	GL_API_FUNC bool IsSync(UGLsync hSync)
	{
		return (glIsSync(hSync) == GL_TRUE) ? true : false;
	}

	GL_API_FUNC FenceResult ClientWaitSync(UGLsync hSync, GLbitfield flags, GLuint64 timeout)
	{
		GLenum result = glClientWaitSync(hSync, flags, timeout);
		switch (result)
		{
		case GL_ALREADY_SIGNALED: return FenceResult::AlreadySignaled;
		case GL_TIMEOUT_EXPIRED: return FenceResult::TimeoutExpired;
		case GL_CONDITION_SATISFIED: return FenceResult::ConditionSatisfied;
		}
		return FenceResult::WaitFailed;
	}

	GL_API_FUNC void GenSamplers(GLsizei count, GLuint* hSamplers)
	{
		glGenSamplers(count, hSamplers);
	}

	GL_API_FUNC void DeleteSamplers(GLsizei count, GLuint* samplers)
	{
		glDeleteSamplers(count, samplers);
	}

	GL_API_FUNC void SetSamplerParameter(GLuint hSampler, GLenum parameter, GLint value)
	{
		glSamplerParameteri(hSampler, parameter, value);
	}

	GL_API_FUNC void BindSampler(GLuint unit, GLuint sampler)
	{
		glBindSampler(unit, sampler);
	}

	GL_API_FUNC void PolygonMode(GLenum face, GLenum mode)
	{
		glPolygonMode(face, mode);
	}

	GL_API_FUNC void VertexAttribDivisor(GLuint index, GLuint divisor)
	{
		glVertexAttribDivisor(index, divisor);
	}

	GL_API_FUNC void* MapBufferRange(GLenum type, uint32 inOffset, uint32 inSize, ResourceLockMode lockMode)
	{
		GLenum access;
		switch (lockMode)
		{
		case ResourceLockMode::ReadOnly:
			access = GL_MAP_READ_BIT;
			break;
		case ResourceLockMode::WriteOnly:
			access = (GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_WRITE_BIT);
#if 1
			// Temp workaround for synchrnoization when a UBO is discarded while being referenced
			access |= GL_MAP_UNSYNCHRONIZED_BIT;
#endif
			break;
		case ResourceLockMode::WriteOnlyUnsynchronized:
			access = (GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			break;
		case ResourceLockMode::ReadWrite:
		default:
			access = (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
		}
		return glMapBufferRange(type, inOffset, inSize, access);
	}

	GL_API_FUNC void UnmapBuffer(GLenum type)
	{
		glUnmapBuffer(type);
	}

	GL_API_FUNC void UnmapBufferRange(GLenum type, uint32 inOffset, uint32 inSize)
	{
		UnmapBuffer(type);
	}

	GL_API_FUNC void GenQueries(GLsizei numQueries, GLuint* hQueries)
	{
		glGenQueries(numQueries, hQueries);
	}

	GL_API_FUNC void DeleteQueries(GLsizei numQueries, const GLuint* hQueries)
	{
		glDeleteQueries(numQueries, hQueries);
	}

	GL_API_FUNC void GetQueryObject(GLuint hQuery, QueryMode queryMode, GLuint* result)
	{
		GLenum queryName = (queryMode == QueryMode::Result) ? GL_QUERY_RESULT : GL_QUERY_RESULT_AVAILABLE;
		glGetQueryObjectuiv(hQuery, queryName, result);
	}

	GL_API_FUNC void BindBufferBase(GLenum target, GLuint index, GLuint hBuffer)
	{
		glBindBufferBase(target, index, hBuffer);
	}

	GL_API_FUNC GLuint GetUniformBlockIndex(GLuint hProgram, const GLchar* uniformBlockName)
	{
		return glGetUniformBlockIndex(hProgram, uniformBlockName);
	}

	GL_API_FUNC void UniformBlockBinding(GLuint hProgram, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
	{
		glUniformBlockBinding(hProgram, uniformBlockIndex, uniformBlockBinding);
	}

	GL_API_FUNC void BindFragDataLocation(GLuint hProgram, GLuint color, const GLchar* name)
	{
		glBindFragDataLocation(hProgram, color, name);
	}

	GL_API_FUNC void TexParameter(GLenum target, GLenum parameter, GLint value)
	{
		glTexParameteri(target, parameter, value);
	}

	GL_API_FUNC void FramebufferTexture(GLenum target, GLenum attachment, GLuint hTexture, GLint level)
	{
		glFramebufferTexture(target, attachment, hTexture, level);
	}

	GL_API_FUNC void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum texTarget, GLuint hTexture, GLint level, GLint zOffset)
	{
		glFramebufferTexture3D(target, attachment, texTarget, hTexture, level, zOffset);
	}

	GL_API_FUNC void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint hTexture, GLint level, GLint layer)
	{
		glFramebufferTextureLayer(target, attachment, hTexture, level, layer);
	}

	GL_API_FUNC void Uniform4uiv(GLint location, GLsizei count, const GLuint* value)
	{
		glUniform4uiv(location, count, value);
	}

	GL_API_FUNC void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
	{
		glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	}

	GL_API_FUNC void DrawBuffers(GLsizei numBuffers, const GLenum * hBuffers)
	{
		glDrawBuffers(numBuffers, hBuffers);
	}

	GL_API_FUNC void DepthRange(GLdouble Near, GLdouble Far)
	{
		glDepthRange(Near, Far);
	}

	GL_API_FUNC void EnableIndexed(GLenum parameter, GLuint index)
	{
		glEnablei(parameter, index);
	}

	GL_API_FUNC void DisableIndexed(GLenum parameter, GLuint index)
	{
		glDisablei(parameter, index);
	}

	GL_API_FUNC void ColorMaskIndexed(GLuint index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
	{
		glColorMaski(index, red, green, blue, alpha);
	}

	GL_API_FUNC void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	GL_API_FUNC void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)
	{
		glVertexAttribIPointer(index, size, type, stride, pointer);
	}

	GL_API_FUNC void VertexAttrib4Nsv(GLuint index, const GLshort* values)
	{
		glVertexAttrib4Nsv(index, values);
	}

	GL_API_FUNC void VertexAttrib4sv(GLuint index, const GLshort* values)
	{
		glVertexAttrib4sv(index, values);
	}

	GL_API_FUNC void VertexAttribI4sv(GLuint index, const GLshort* values)
	{
		glVertexAttribI4sv(index, values);
	}

	GL_API_FUNC void VertexAttribI4usv(GLuint index, const GLushort* values)
	{
		glVertexAttribI4usv(index, values);
	}

	GL_API_FUNC void VertexAttrib4Nubv(GLuint index, const GLubyte* values)
	{
		glVertexAttrib4Nubv(index, values);
	}

	GL_API_FUNC void VertexAttrib4ubv(GLuint index, const GLubyte* values)
	{
		glVertexAttrib4ubv(index, values);
	}

	GL_API_FUNC void VertexAttribI4ubv(GLuint index, const GLubyte* values)
	{
		glVertexAttribI4ubv(index, values);
	}

	GL_API_FUNC void VertexAttrib4Nbv(GLuint index, const GLbyte* values)
	{
		glVertexAttrib4Nbv(index, values);
	}

	GL_API_FUNC void VertexAttrib4bv(GLuint index, const GLbyte* values)
	{
		glVertexAttrib4bv(index, values);
	}

	GL_API_FUNC void VertexAttribI4bv(GLuint index, const GLbyte* values)
	{
		glVertexAttribI4bv(index, values);
	}

	GL_API_FUNC void VertexAttrib4dv(GLuint index, const GLdouble* values)
	{
		glVertexAttrib4dv(index, values);
	}

	GL_API_FUNC void VertexAttribI4iv(GLuint index, const GLint* values)
	{
		glVertexAttribI4iv(index, values);
	}

	GL_API_FUNC void VertexAttribI4uiv(GLuint index, const GLuint* values)
	{
		glVertexAttribI4uiv(index, values);
	}

	GL_API_FUNC void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
	{
		glDrawArraysInstanced(mode, first, count, instanceCount);
	}

	GL_API_FUNC void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices, GLsizei instanceCount)
	{
		glDrawElementsInstanced(mode, count, type, indices, instanceCount);
	}

	GL_API_FUNC void DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices)
	{
		glDrawRangeElements(mode, start, end, count, type, indices);
	}

	GL_API_FUNC void ClearBufferfv(GLenum buffer, GLint drawBufferIndex, const GLfloat* value)
	{
		glClearBufferfv(buffer, drawBufferIndex, value);
	}

	GL_API_FUNC void ClearBufferfi(GLenum buffer, GLint drawBufferIndex, GLfloat depth, GLint stencil)
	{
		glClearBufferfi(buffer, drawBufferIndex, depth, stencil);
	}

	GL_API_FUNC void ClearBufferiv(GLenum buffer, GLint drawBufferIndex, const GLint* value)
	{
		glClearBufferiv(buffer, drawBufferIndex, value);
	}

	GL_API_FUNC void ClearDepth(GLdouble depth)
	{
		glClearDepth(depth);
	}

	GL_API_FUNC void TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixelData)
	{
		glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixelData);
	}

	GL_API_FUNC void CompressedTexImage3D(GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* pixelData)
	{
		glCompressedTexImage3D(target, level, internalFormat, width, height, depth, border, imageSize, pixelData);
	}

	GL_API_FUNC void CompressedTexSubImage2D(GLenum target, GLint level, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * pixelData)
	{
		glCompressedTexSubImage2D(target, level, 0, 0, width, height, format, imageSize, pixelData);
	}

	GL_API_FUNC void TexImage2DMultisample(GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
	{
		glTexImage2DMultisample(target, samples, internalFormat, width, height, fixedSampleLocations);
	}

	GL_API_FUNC void TexBuffer(GLenum target, GLenum internalFormat, GLuint hBuffer)
	{
		glTexBuffer(target, internalFormat, hBuffer);
	}

	GL_API_FUNC void TexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixelData)
	{
		glTexSubImage3D(target, level, xOffset, yOffset, zOffset, width, height, depth, format, type, pixelData);
	}

	GL_API_FUNC void CopyTexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLint x, GLint y, GLsizei width, GLsizei height)
	{
		glCopyTexSubImage3D(target, level, xOffset, yOffset, zOffset, x, y, width, height);
	}

	GL_API_FUNC void GetCompressedTexImage(GLenum target, GLint level, GLvoid* outImageData)
	{
		glGetCompressedTexImage(target, level, outImageData);
	}

	GL_API_FUNC void GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* outPixelData)
	{
		glGetTexImage(target, level, format, type, outPixelData);
	}

	GL_API_FUNC void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
	{
		glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	}

	GL_API_FUNC void GenBuffers(GLsizei num, GLuint *hBuffers)
	{
		glGenBuffers(num, hBuffers);
	}

	GL_API_FUNC void GenTextures(GLsizei num, GLuint * hTextures)
	{
		glGenTextures(num, hTextures);
	}

	GL_API_FUNC void CompressedTexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* pixelData)
	{
		glCompressedTexSubImage3D(target, level, xOffset, yOffset, zOffset, width, height, depth, format, imageSize, pixelData);
	}

	GL_API_FUNC const ANSICHAR* GetStringIndexed(GLenum name, GLuint index)
	{
		return (const ANSICHAR*)glGetStringi(name, index);
	}
};