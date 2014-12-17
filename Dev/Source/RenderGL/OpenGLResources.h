#pragma once

#include "FreAssert.h"
#include "FreRDResources.h"

namespace FRE
{
	class GLContext;

	namespace OpenGLSystemParams
	{
		extern int32 UseMapBuffer;
	};

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

	template <GLenum T>
	class GLTypedTexture : public GLTexture
	{

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
		enum MappingMode
		{
			ReadOnly,
			WriteOnly
		};

	public:
		GLBuffer(GLuint name, GLenum target) :
			Name(name),
			Target(target)
		{
			
		}

		const GLuint Name;
		const GLenum Target;

		void * Map(GLuint offset, GLuint size, MappingMode mode)
		{
			_locked = true;
			auto access = mode == ReadOnly ? OpenGLAPI::LockMode::Read : OpenGLAPI::LockMode::Write;
			return FOpenGL::MapBufferRange(Target, offset, size, access);
		}

		void Unmap()
		{
			FOpenGL::UnmapBuffer(Target);
			_locked = false;
		}

	private:
		bool _locked = false;
	};

	template <GLenum T>
	class GLTypedBuffer : public GLBuffer
	{
	public:
		enum { Type = T };

	public:
		GLTypedBuffer(GLuint name) :
			GLBuffer(name, Type)
		{

		}

		virtual ~GLTypedBuffer()
		{
			//TODO!!!!!!!
		}

		void * Lock(GLContext & ctx, uint32 offset, uint32 size, MappingMode mode)
		{
			if (Name)
			{
				ctx.BindBuffer<Type>(Name);
				return Map(offset, size, mode);
			}
			return nullptr;
		}

		void Unlock(GLContext & ctx)
		{
			if (Name)
			{
				ctx.BindBuffer<Type>(Name);
				Unmap();
			}
		}
	};

	class GLVertexBuffer : public GLTypedBuffer<GL_ARRAY_BUFFER>, public RDVertexBuffer
	{
	public:
		GLVertexBuffer(GLuint buffer, GLuint size, uint32 usage) :
			GLTypedBuffer(buffer),
			RDVertexBuffer(size, usage)
		{

		}
	};

	class GLStructuredBuffer : public GLTypedBuffer<GL_ARRAY_BUFFER>, public RDStructureBuffer
	{
	public:
		GLStructuredBuffer(GLuint buffer, GLuint size, uint32 usage, GLuint stride) :
			GLTypedBuffer(buffer),
			RDStructureBuffer(size, usage, stride)
		{

		}
	};

	class GLIndexBuffer : public GLTypedBuffer<GL_ELEMENT_ARRAY_BUFFER>, public RDIndexBuffer
	{
	public:
		GLIndexBuffer(GLuint buffer, GLuint size, uint32 usage, GLuint stride) :
			GLTypedBuffer(buffer),
			RDIndexBuffer(size, usage, stride)
		{

		}
	};
}