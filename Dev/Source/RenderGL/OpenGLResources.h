#pragma once

#include "FreAssert.h"
#include "FreRDResources.h"

namespace FRE
{
	class GLContext;

	class GLTexture
	{
	public:
		GLTexture(GLuint name, GLenum target, GLenum attachment);
		~GLTexture();

		void * Lock(uint32 mipIndex, uint32 arrayIndex, ELockMode lockMode);
		void Unlock(uint32 mipIndex, uint32 arrayIndex);

		const GLuint Name;
		const GLenum Target;
		const GLenum AttachmentPoint;

		static GLenum GetAttachment(EPixelFormat format, uint32 flags);
	};

	class GLTexture2D : public GLTexture, public RDTexture2D
	{
	public:
		GLTexture2D(GLuint name, GLenum target,	uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
			GLTexture(name, target, GetAttachment(format, flags)),
			RDTexture2D(sizeX, sizeY, numMips, numSamples, format, flags)
		{

		}

		static GLTexture2D * Create(GLContext & ctx, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags);
	};

	class GLTexture2DArray : public GLTexture, public RDTexture2DArray
	{
		GLTexture2DArray(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 arraySize, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
		GLTexture(name, target, GetAttachment(format, flags)),
		RDTexture2DArray(sizeX, sizeY, arraySize, numMips, numSamples, format, flags)
		{

		}
	};

	class GLTextureCube : public GLTexture, public RDTextureCube
	{
		GLTextureCube(GLuint name, GLenum target, uint32 sizeXY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
		GLTexture(name, target, GetAttachment(format, flags)),
		RDTextureCube(sizeXY, numMips, numSamples, format, flags)
		{

		}
	};

	class GLTexture3D : public GLTexture, public RDTexture3D
	{
		GLTexture3D(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 sizeZ, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
		GLTexture(name, target, GetAttachment(format, flags)),
		RDTexture3D(sizeX, sizeY, sizeZ, numMips, numSamples, format, flags)
		{

		}
	};

	//-------------------------------------------------------------------------

	class GLBuffer
	{
	public:

		GLBuffer(GLuint name, GLenum target) :
			Name(name),
			Target(target)
		{
			
		}

		const GLuint Name;
		const GLenum Target;

	protected:
		void * Map(GLuint offset, GLuint size, bool readOnly)
		{
			FOpenGL::LockMode lockMode = readOnly ? FOpenGL::LockMode::Read : FOpenGL::LockMode::ReadWrite;
            void * data = FOpenGL::MapBufferRange(Target, offset, size, lockMode);
			return data;
		}

		void UnMap()
		{
			FOpenGL::UnmapBuffer(Target);
		}
	};

	class GLVertexBuffer : public GLBuffer, public RDVertexBuffer
	{
		enum
		{
			Target = GL_ARRAY_BUFFER
		};

	public:
		GLVertexBuffer(GLuint name, GLuint size, uint32 usage) :
			GLBuffer(name, GLVertexBuffer::Target),
			RDVertexBuffer(size, usage)
		{
			
		}

		void * Lock(GLContext & ctx, uint32 offset, uint32 size, bool readOnly);
		void UnLock(GLContext & ctx);

		static GLVertexBuffer * Create(GLContext & ctx, GLuint size, uint32 usage, const void * data = nullptr);
		static FORCEINLINE void Bind(GLContext & ctx, GLuint buffer);
	};

	class GLIndexBuffer : public GLBuffer, public RDIndexBuffer
	{
		enum
		{
			Target = GL_ELEMENT_ARRAY_BUFFER
		};

	public:
		GLIndexBuffer(GLuint name, GLuint size, uint32 usage, GLuint stride) :
			GLBuffer(name, GLIndexBuffer::Target),
			RDIndexBuffer(size, usage, stride)
		{
			
		}

		void * Lock(GLContext & ctx, uint32 offset, uint32 size, bool readOnly);
		void UnLock(GLContext & ctx);

		static GLIndexBuffer * Create(GLContext & ctx, GLuint size, uint32 usage, GLuint stride, const void * data = nullptr);
		static FORCEINLINE void Bind(GLContext & ctx, GLuint buffer);
	};
}