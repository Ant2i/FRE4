#pragma once

#include "FreRDResources.h"

namespace FRE
{
	class GLContext;

	class GLResource
	{
	public:
		GLResource(GLuint resource) :
			Name(resource)
		{

		}

		const GLuint Name;
	};

	class GLTexture : public GLResource
	{
	public:
		GLTexture(GLuint name, GLenum target, GLenum attachment);
		~GLTexture();

		void * Lock(uint32 MipIndex, uint32 ArrayIndex, ELockMode lockMode);
		void Unlock(uint32 MipIndex, uint32 ArrayIndex);

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

	class GLBuffer : public GLResource
	{
	public:
		void * Lock(uint32 offset, uint32 size, bool readOnly)
		{

		}

		void UnLock()
		{

		}
	};
}