#pragma once

#include "FOpenGLBase.h"

struct OpenGL3API : public OpenGLBaseAPI
{
	//GL_API_FUNC bool IsDebugContent()					{ return bDebugContext; }

	//GL_API_FUNC bool SupportsTimestampQueries()			{ return TimestampQueryBits > 0; }
	//GL_API_FUNC bool SupportsSeamlessCubeMap()			{ return bSupportsSeamlessCubemap; }

	// Optional
	GL_API_FUNC void QueryTimestampCounter(GLuint QueryID)
	{
		glQueryCounter(QueryID, GL_TIMESTAMP);
	}

	GL_API_FUNC void BeginQuery(GLenum QueryType, GLuint QueryId)
	{
		glBeginQuery(QueryType, QueryId);
	}

	GL_API_FUNC void EndQuery(GLenum QueryType)
	{
		glEndQuery(QueryType);
	}

	GL_API_FUNC void GetQueryObject(GLuint QueryId, QueryMode QueryMode, uint64* OutResult)
	{
		GLenum QueryName = (QueryMode == QueryMode::Result) ? GL_QUERY_RESULT : GL_QUERY_RESULT_AVAILABLE;
		GLuint64 Result = 0;
		glGetQueryObjectui64v(QueryId, QueryName, &Result);
		*OutResult = Result;
	}

	GL_API_FUNC void ReadBuffer(GLenum Mode)
	{
		glReadBuffer(Mode);
	}

	GL_API_FUNC void DrawBuffer(GLenum Mode)
	{
		glDrawBuffer(Mode);
	}

	GL_API_FUNC void DeleteSync(UGLsync Sync)
	{
		glDeleteSync(Sync);
	}

	GL_API_FUNC UGLsync FenceSync(GLenum Condition, GLbitfield Flags)
	{
		return glFenceSync(Condition, Flags);
	}

	GL_API_FUNC bool IsSync(UGLsync Sync)
	{
		return (glIsSync(Sync) == GL_TRUE) ? true : false;
	}

	GL_API_FUNC FenceResult ClientWaitSync(UGLsync Sync, GLbitfield Flags, GLuint64 Timeout)
	{
		GLenum Result = glClientWaitSync(Sync, Flags, Timeout);
		switch (Result)
		{
		case GL_ALREADY_SIGNALED: return FenceResult::AlreadySignaled;
		case GL_TIMEOUT_EXPIRED: return FenceResult::TimeoutExpired;
		case GL_CONDITION_SATISFIED: return FenceResult::ConditionSatisfied;
		}
		return FenceResult::WaitFailed;
	}

	GL_API_FUNC void GenSamplers(GLsizei Count, GLuint* Samplers)
	{
		glGenSamplers(Count, Samplers);
	}

	GL_API_FUNC void DeleteSamplers(GLsizei Count, GLuint* Samplers)
	{
		glDeleteSamplers(Count, Samplers);
	}

	GL_API_FUNC void SetSamplerParameter(GLuint Sampler, GLenum Parameter, GLint Value)
	{
		glSamplerParameteri(Sampler, Parameter, Value);
	}

	GL_API_FUNC void BindSampler(GLuint Unit, GLuint Sampler)
	{
		glBindSampler(Unit, Sampler);
	}

	GL_API_FUNC void PolygonMode(GLenum Face, GLenum Mode)
	{
		glPolygonMode(Face, Mode);
	}

	GL_API_FUNC void VertexAttribDivisor(GLuint Index, GLuint Divisor)
	{
		glVertexAttribDivisor(Index, Divisor);
	}

	GL_API_FUNC void* MapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize, ResourceLockMode LockMode)
	{
		GLenum Access;
		switch (LockMode)
		{
		case ResourceLockMode::ReadOnly:
			Access = GL_MAP_READ_BIT;
			break;
		case ResourceLockMode::WriteOnly:
			Access = (GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_WRITE_BIT);
#if 1
			// Temp workaround for synchrnoization when a UBO is discarded while being referenced
			Access |= GL_MAP_UNSYNCHRONIZED_BIT;
#endif
			break;
		case ResourceLockMode::WriteOnlyUnsynchronized:
			Access = (GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			break;
		case ResourceLockMode::ReadWrite:
		default:
			Access = (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
		}
		return glMapBufferRange(Type, InOffset, InSize, Access);
	}

	GL_API_FUNC void UnmapBuffer(GLenum Type)
	{
		glUnmapBuffer(Type);
	}

	GL_API_FUNC void UnmapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize)
	{
		UnmapBuffer(Type);
	}

	GL_API_FUNC void GenQueries(GLsizei NumQueries, GLuint* QueryIDs)
	{
		glGenQueries(NumQueries, QueryIDs);
	}

	GL_API_FUNC void DeleteQueries(GLsizei NumQueries, const GLuint* QueryIDs)
	{
		glDeleteQueries(NumQueries, QueryIDs);
	}

	GL_API_FUNC void GetQueryObject(GLuint QueryId, QueryMode QueryMode, GLuint* OutResult)
	{
		GLenum QueryName = (QueryMode == QueryMode::Result) ? GL_QUERY_RESULT : GL_QUERY_RESULT_AVAILABLE;
		glGetQueryObjectuiv(QueryId, QueryName, OutResult);
	}

	GL_API_FUNC void BindBufferBase(GLenum Target, GLuint Index, GLuint Buffer)
	{
		glBindBufferBase(Target, Index, Buffer);
	}

	GL_API_FUNC GLuint GetUniformBlockIndex(GLuint Program, const GLchar* UniformBlockName)
	{
		return glGetUniformBlockIndex(Program, UniformBlockName);
	}

	GL_API_FUNC void UniformBlockBinding(GLuint Program, GLuint UniformBlockIndex, GLuint UniformBlockBinding)
	{
		glUniformBlockBinding(Program, UniformBlockIndex, UniformBlockBinding);
	}

	GL_API_FUNC void BindFragDataLocation(GLuint Program, GLuint Color, const GLchar* Name)
	{
		glBindFragDataLocation(Program, Color, Name);
	}

	GL_API_FUNC void TexParameter(GLenum Target, GLenum Parameter, GLint Value)
	{
		glTexParameteri(Target, Parameter, Value);
	}

	GL_API_FUNC void FramebufferTexture(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level)
	{
		glFramebufferTexture(Target, Attachment, Texture, Level);
	}

	GL_API_FUNC void FramebufferTexture3D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint ZOffset)
	{
		glFramebufferTexture3D(Target, Attachment, TexTarget, Texture, Level, ZOffset);
	}

	GL_API_FUNC void FramebufferTextureLayer(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint Layer)
	{
		glFramebufferTextureLayer(Target, Attachment, Texture, Level, Layer);
	}

	GL_API_FUNC void Uniform4uiv(GLint Location, GLsizei Count, const GLuint* Value)
	{
		glUniform4uiv(Location, Count, Value);
	}

	GL_API_FUNC void BlitFramebuffer(GLint SrcX0, GLint SrcY0, GLint SrcX1, GLint SrcY1, GLint DstX0, GLint DstY0, GLint DstX1, GLint DstY1, GLbitfield Mask, GLenum Filter)
	{
		glBlitFramebuffer(SrcX0, SrcY0, SrcX1, SrcY1, DstX0, DstY0, DstX1, DstY1, Mask, Filter);
	}

	GL_API_FUNC void DrawBuffers(GLsizei NumBuffers, const GLenum* Buffers)
	{
		glDrawBuffers(NumBuffers, Buffers);
	}

	GL_API_FUNC void DepthRange(GLdouble Near, GLdouble Far)
	{
		glDepthRange(Near, Far);
	}

	GL_API_FUNC void EnableIndexed(GLenum Parameter, GLuint Index)
	{
		glEnablei(Parameter, Index);
	}

	GL_API_FUNC void DisableIndexed(GLenum Parameter, GLuint Index)
	{
		glDisablei(Parameter, Index);
	}

	GL_API_FUNC void ColorMaskIndexed(GLuint Index, GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha)
	{
		glColorMaski(Index, Red, Green, Blue, Alpha);
	}

	GL_API_FUNC void VertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid* Pointer)
	{
		glVertexAttribPointer(Index, Size, Type, Normalized, Stride, Pointer);
	}

	GL_API_FUNC void VertexAttribIPointer(GLuint Index, GLint Size, GLenum Type, GLsizei Stride, const GLvoid* Pointer)
	{
		glVertexAttribIPointer(Index, Size, Type, Stride, Pointer);
	}

	GL_API_FUNC void VertexAttrib4Nsv(GLuint AttributeIndex, const GLshort* Values)
	{
		glVertexAttrib4Nsv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttrib4sv(GLuint AttributeIndex, const GLshort* Values)
	{
		glVertexAttrib4sv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttribI4sv(GLuint AttributeIndex, const GLshort* Values)
	{
		glVertexAttribI4sv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttribI4usv(GLuint AttributeIndex, const GLushort* Values)
	{
		glVertexAttribI4usv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttrib4Nubv(GLuint AttributeIndex, const GLubyte* Values)
	{
		glVertexAttrib4Nubv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttrib4ubv(GLuint AttributeIndex, const GLubyte* Values)
	{
		glVertexAttrib4ubv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttribI4ubv(GLuint AttributeIndex, const GLubyte* Values)
	{
		glVertexAttribI4ubv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttrib4Nbv(GLuint AttributeIndex, const GLbyte* Values)
	{
		glVertexAttrib4Nbv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttrib4bv(GLuint AttributeIndex, const GLbyte* Values)
	{
		glVertexAttrib4bv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttribI4bv(GLuint AttributeIndex, const GLbyte* Values)
	{
		glVertexAttribI4bv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttrib4dv(GLuint AttributeIndex, const GLdouble* Values)
	{
		glVertexAttrib4dv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttribI4iv(GLuint AttributeIndex, const GLint* Values)
	{
		glVertexAttribI4iv(AttributeIndex, Values);
	}

	GL_API_FUNC void VertexAttribI4uiv(GLuint AttributeIndex, const GLuint* Values)
	{
		glVertexAttribI4uiv(AttributeIndex, Values);
	}

	GL_API_FUNC void DrawArraysInstanced(GLenum Mode, GLint First, GLsizei Count, GLsizei InstanceCount)
	{
		glDrawArraysInstanced(Mode, First, Count, InstanceCount);
	}

	GL_API_FUNC void DrawElementsInstanced(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid* Indices, GLsizei InstanceCount)
	{
		glDrawElementsInstanced(Mode, Count, Type, Indices, InstanceCount);
	}

	GL_API_FUNC void DrawRangeElements(GLenum Mode, GLuint Start, GLuint End, GLsizei Count, GLenum Type, const GLvoid* Indices)
	{
		glDrawRangeElements(Mode, Start, End, Count, Type, Indices);
	}

	GL_API_FUNC void ClearBufferfv(GLenum Buffer, GLint DrawBufferIndex, const GLfloat* Value)
	{
		glClearBufferfv(Buffer, DrawBufferIndex, Value);
	}

	GL_API_FUNC void ClearBufferfi(GLenum Buffer, GLint DrawBufferIndex, GLfloat Depth, GLint Stencil)
	{
		glClearBufferfi(Buffer, DrawBufferIndex, Depth, Stencil);
	}

	GL_API_FUNC void ClearBufferiv(GLenum Buffer, GLint DrawBufferIndex, const GLint* Value)
	{
		glClearBufferiv(Buffer, DrawBufferIndex, Value);
	}

	GL_API_FUNC void ClearDepth(GLdouble Depth)
	{
		glClearDepth(Depth);
	}

	GL_API_FUNC void TexImage3D(GLenum Target, GLint Level, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLenum Format, GLenum Type, const GLvoid* PixelData)
	{
		glTexImage3D(Target, Level, InternalFormat, Width, Height, Depth, Border, Format, Type, PixelData);
	}

	GL_API_FUNC void CompressedTexImage3D(GLenum Target, GLint Level, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLsizei ImageSize, const GLvoid* PixelData)
	{
		glCompressedTexImage3D(Target, Level, InternalFormat, Width, Height, Depth, Border, ImageSize, PixelData);
	}

	GL_API_FUNC void CompressedTexSubImage2D(GLenum Target, GLint Level, GLsizei Width, GLsizei Height, GLenum Format, GLsizei ImageSize, const GLvoid * PixelData)
	{
		glCompressedTexSubImage2D(Target, Level, 0, 0, Width, Height, Format, ImageSize, PixelData);
	}

	GL_API_FUNC void TexImage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations)
	{
		glTexImage2DMultisample(Target, Samples, InternalFormat, Width, Height, FixedSampleLocations);
	}

	GL_API_FUNC void TexBuffer(GLenum Target, GLenum InternalFormat, GLuint Buffer)
	{
		glTexBuffer(Target, InternalFormat, Buffer);
	}

	GL_API_FUNC void TexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type, const GLvoid* PixelData)
	{
		glTexSubImage3D(Target, Level, XOffset, YOffset, ZOffset, Width, Height, Depth, Format, Type, PixelData);
	}

	GL_API_FUNC void	CopyTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height)
	{
		glCopyTexSubImage3D(Target, Level, XOffset, YOffset, ZOffset, X, Y, Width, Height);
	}

	GL_API_FUNC void GetCompressedTexImage(GLenum Target, GLint Level, GLvoid* OutImageData)
	{
		glGetCompressedTexImage(Target, Level, OutImageData);
	}

	GL_API_FUNC void GetTexImage(GLenum Target, GLint Level, GLenum Format, GLenum Type, GLvoid* OutPixelData)
	{
		glGetTexImage(Target, Level, Format, Type, OutPixelData);
	}

	GL_API_FUNC void CopyBufferSubData(GLenum ReadTarget, GLenum WriteTarget, GLintptr ReadOffset, GLintptr WriteOffset, GLsizeiptr Size)
	{
		glCopyBufferSubData(ReadTarget, WriteTarget, ReadOffset, WriteOffset, Size);
	}

	GL_API_FUNC void GenBuffers(GLsizei n, GLuint *buffers)
	{
#if USE_OPENGL_NAME_CACHE
		if (n < OPENGL_NAME_CACHE_SIZE - NextBufferName)
		{
			FMemory::Memcpy(buffers, &BufferNamesCache[NextBufferName], sizeof(GLuint)*n);
			NextBufferName += n;
		}
		else
		{
			if (n >= OPENGL_NAME_CACHE_SIZE)
			{
				glGenBuffers(n, buffers);
			}
			else
			{
				GLsizei Leftover = OPENGL_NAME_CACHE_SIZE - NextBufferName;

				FMemory::Memcpy(buffers, &BufferNamesCache[NextBufferName], sizeof(GLuint)*Leftover);

				glGenBuffers(OPENGL_NAME_CACHE_SIZE, BufferNamesCache);

				n -= Leftover;
				buffers += Leftover;

				FMemory::Memcpy(buffers, BufferNamesCache, sizeof(GLuint)*n);
				NextBufferName = n;
			}
		}
#else
		glGenBuffers(n, buffers);
#endif
	}

	GL_API_FUNC void GenTextures(GLsizei n, GLuint *textures)
	{
#if USE_OPENGL_NAME_CACHE
		if (n < OPENGL_NAME_CACHE_SIZE - NextTextureName)
		{
			FMemory::Memcpy(textures, &TextureNamesCache[NextTextureName], sizeof(GLuint)*n);
			NextTextureName += n;
		}
		else
		{
			if (n >= OPENGL_NAME_CACHE_SIZE)
			{
				glGenTextures(n, textures);
			}
			else
			{
				GLsizei Leftover = OPENGL_NAME_CACHE_SIZE - NextTextureName;

				FMemory::Memcpy(textures, &TextureNamesCache[NextTextureName], sizeof(GLuint)*Leftover);

				glGenTextures(OPENGL_NAME_CACHE_SIZE, TextureNamesCache);

				n -= Leftover;
				textures += Leftover;

				FMemory::Memcpy(textures, TextureNamesCache, sizeof(GLuint)*n);
				NextTextureName = n;
			}
		}
#else
		glGenTextures(n, textures);
#endif
	}

	GL_API_FUNC void CompressedTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLsizei ImageSize, const GLvoid* PixelData)
	{
		glCompressedTexSubImage3D(Target, Level, XOffset, YOffset, ZOffset, Width, Height, Depth, Format, ImageSize, PixelData);
	}

	GL_API_FUNC const ANSICHAR* GetStringIndexed(GLenum Name, GLuint Index)
	{
		return (const ANSICHAR*)glGetStringi(Name, Index);
	}

	GL_API_FUNC GLuint GetMajorVersion()
	{
		GLint MajorVersion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
		return MajorVersion;
	}

	GL_API_FUNC GLuint GetMinorVersion()
	{
		GLint MinorVersion = 0;
		glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);
		return MinorVersion;
	}

	//GL_API_FUNC ERHIFeatureLevel::Type GetFeatureLevel()
	//{
	//	if (FParse::Param(FCommandLine::Get(), TEXT("FeatureLevelES2")))
	//	{
	//		return ERHIFeatureLevel::ES2;
	//	}
	//	// Shader platform & RHI feature level
	//	switch (GetMajorVersion())
	//	{
	//	case 2:
	//		return ERHIFeatureLevel::ES2;
	//	case 3:
	//		return ERHIFeatureLevel::SM4;
	//	case 4:
	//		return GetMinorVersion() > 2 ? ERHIFeatureLevel::SM5 : ERHIFeatureLevel::SM4;
	//	default:
	//		return ERHIFeatureLevel::SM4;
	//	}
	//}

	//GL_API_FUNC EShaderPlatform GetShaderPlatform()
	//{
	//	static bool bForceFeatureLevelES2 = FParse::Param(FCommandLine::Get(), TEXT("FeatureLevelES2"));
	//	if (bForceFeatureLevelES2)
	//	{
	//		return SP_OPENGL_PCES2;
	//	}

	//	// Shader platform
	//	switch (GetMajorVersion())
	//	{
	//	case 3:
	//		return SP_OPENGL_SM4;
	//	case 4:
	//		return GetMinorVersion() > 2 ? SP_OPENGL_SM5 : SP_OPENGL_SM4;
	//	default:
	//		return SP_OPENGL_SM4;
	//	}
	//}

	//GL_API_FUNC FString GetAdapterName()
	//{
	//	return ANSI_TO_TCHAR((const ANSICHAR*)glGetString(GL_RENDERER));
	//}

	//static FPlatformOpenGLDevice *	CreateDevice()	UGL_REQUIRED(NULL)
	//static FPlatformOpenGLContext *	CreateContext(FPlatformOpenGLDevice* Device, void* WindowHandle)	UGL_REQUIRED(NULL)

	//static void ProcessQueryGLInt();
	//static void ProcessExtensions(const FString& ExtensionsString);

//protected:
	//static GLsizei NextTextureName;
	//static GLuint TextureNamesCache[OPENGL_NAME_CACHE_SIZE];
	//static GLsizei NextBufferName;
	//static GLuint BufferNamesCache[OPENGL_NAME_CACHE_SIZE];

	//static GLint TimestampQueryBits;

	//static bool bDebugContext;
};