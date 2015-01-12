#pragma once

#include "OpenGLBase.h"
#include "RDResources.h"

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
		GLTexture(GLuint name, GLenum target, EPixelFormat format, uint32 flags);
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
			GLTexture(name, target, format, flags),
			RDTexture2D(sizeX, sizeY, numMips, numSamples, format, flags)
		{

		}

		static GLTexture2D * Create(GLContext & ctx, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags);
	};

	class GLTexture2DArray : public GLTexture, public RDTexture2DArray
	{
		GLTexture2DArray(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 arraySize, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
		GLTexture(name, target, format, flags),
		RDTexture2DArray(sizeX, sizeY, arraySize, numMips, numSamples, format, flags)
		{

		}
	};

	class GLTextureCube : public GLTexture, public RDTextureCube
	{
		GLTextureCube(GLuint name, GLenum target, uint32 sizeXY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
		GLTexture(name, target, format, flags),
		RDTextureCube(sizeXY, numMips, numSamples, format, flags)
		{

		}
	};

	class GLTexture3D : public GLTexture, public RDTexture3D
	{
		GLTexture3D(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 sizeZ, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
		GLTexture(name, target, format, flags),
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

		virtual ~GLBuffer();

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
	
	template <GLenum Type>
	class GLLockBuffer : public GLBuffer
	{
	public:
		enum { Type = Type };

		GLLockBuffer(GLuint buffer) :
			GLBuffer(buffer, Type)
		{

		}

		void * Lock(GLContext & context, uint32 offset, uint32 size, MappingMode mode);
		void Unlock(GLContext & context);
	};

	class GLVertexBuffer : public GLLockBuffer<GL_ARRAY_BUFFER>, public RDVertexBuffer
	{
	public:
		GLVertexBuffer(GLuint buffer, GLuint size, uint32 usage) :
			GLLockBuffer(buffer),
			RDVertexBuffer(size, usage)
		{

		}

		virtual void Destroy() override;
	};

	class GLStructuredBuffer : public GLLockBuffer<GL_ARRAY_BUFFER>, public RDStructureBuffer
	{
	public:
		GLStructuredBuffer(GLuint buffer, GLuint size, uint32 usage, GLuint stride) :
			GLLockBuffer(buffer),
			RDStructureBuffer(size, usage, stride)
		{

		}

		virtual void Destroy() override;
	};

	class GLIndexBuffer : public GLLockBuffer<GL_ELEMENT_ARRAY_BUFFER>, public RDIndexBuffer
	{
	public:
        GLIndexBuffer(GLuint buffer, GLuint size, uint32 usage, GLuint stride) :
			GLLockBuffer(buffer),
			RDIndexBuffer(size, usage, stride)
		{

		}

		virtual void Destroy() override;
	};
}