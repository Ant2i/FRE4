#pragma once

#include "RDResources.h"
#include "OpenGLBase.h"

namespace FRE
{
	class GLContext;

	class GLTexture
	{
	public:
		GLTexture(GLuint name, GLenum target, GLenum attachment);
		GLTexture(GLuint name, GLenum target, EPixelFormat format, uint32_t flags);
		~GLTexture();

		void * Lock(GLContext & context, uint32_t mipIndex, uint32_t arrayIndex, ELockMode lockMode);
		void Unlock(GLContext & context, uint32_t mipIndex, uint32_t arrayIndex);

		const GLuint Name;
		const GLenum Target;
		const GLenum AttachmentPoint;

		static GLenum GetAttachment(EPixelFormat format, uint32_t flags);
	};

	//------------------------------------------------------------------

	class GLTexture2D : public GLTexture, public RDTexture2D
	{
	public:
		GLTexture2D(GLuint name, GLenum target, uint32_t sizeX, uint32_t sizeY, uint32_t numMips, uint32_t numSamples, EPixelFormat format, uint32_t flags) :
			GLTexture(name, target, format, flags),
			RDTexture2D(sizeX, sizeY, numSamples == 0 ? numMips : 0, numSamples, format, flags)
		{

		}

		static GLTexture2D * Create(GLContext & ctx, uint32_t sizeX, uint32_t sizeY, uint32_t numMips, uint32_t numSamples, EPixelFormat format, uint32_t flags);
	};

	//------------------------------------------------------------------

	class GLTexture2DArray : public GLTexture, public RDTexture2DArray
	{
		GLTexture2DArray(GLuint name, GLenum target, uint32_t sizeX, uint32_t sizeY, uint32_t arraySize, uint32_t numMips, EPixelFormat format, uint32_t flags) :
			GLTexture(name, target, format, flags),
			RDTexture2DArray(sizeX, sizeY, arraySize, numMips, format, flags)
		{

		}
	};

	//------------------------------------------------------------------

	class GLTextureCube : public GLTexture, public RDTextureCube
	{
		GLTextureCube(GLuint name, GLenum target, uint32_t sizeXY, uint32_t numMips, EPixelFormat format, uint32_t flags) :
			GLTexture(name, target, format, flags),
			RDTextureCube(sizeXY, numMips, format, flags)
		{

		}
	};

	//------------------------------------------------------------------

	class GLTexture3D : public GLTexture, public RDTexture3D
	{
		GLTexture3D(GLuint name, GLenum target, uint32_t sizeX, uint32_t sizeY, uint32_t sizeZ, uint32_t numMips, EPixelFormat format, uint32_t flags) :
			GLTexture(name, target, format, flags),
			RDTexture3D(sizeX, sizeY, sizeZ, numMips, format, flags)
		{

		}
	};
}