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
		GLTexture(GLuint name, GLenum target, EPixelFormat format, uint32 flags);
		~GLTexture();

		void * Lock(GLContext & context, uint32 mipIndex, uint32 arrayIndex, ELockMode lockMode);
		void Unlock(GLContext & context, uint32 mipIndex, uint32 arrayIndex);

		const GLuint Name;
		const GLenum Target;
		const GLenum AttachmentPoint;

		static GLenum GetAttachment(EPixelFormat format, uint32 flags);
	};

	//------------------------------------------------------------------

	class GLTexture2D : public GLTexture, public RDTexture2D
	{
	public:
		GLTexture2D(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
			GLTexture(name, target, format, flags),
			RDTexture2D(sizeX, sizeY, numSamples == 0 ? numMips : 0, numSamples, format, flags)
		{

		}

		static GLTexture2D * Create(GLContext & ctx, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags);
	};

	//------------------------------------------------------------------

	class GLTexture2DArray : public GLTexture, public RDTexture2DArray
	{
		GLTexture2DArray(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 arraySize, uint32 numMips, EPixelFormat format, uint32 flags) :
			GLTexture(name, target, format, flags),
			RDTexture2DArray(sizeX, sizeY, arraySize, numMips, format, flags)
		{

		}
	};

	//------------------------------------------------------------------

	class GLTextureCube : public GLTexture, public RDTextureCube
	{
		GLTextureCube(GLuint name, GLenum target, uint32 sizeXY, uint32 numMips, EPixelFormat format, uint32 flags) :
			GLTexture(name, target, format, flags),
			RDTextureCube(sizeXY, numMips, format, flags)
		{

		}
	};

	//------------------------------------------------------------------

	class GLTexture3D : public GLTexture, public RDTexture3D
	{
		GLTexture3D(GLuint name, GLenum target, uint32 sizeX, uint32 sizeY, uint32 sizeZ, uint32 numMips, EPixelFormat format, uint32 flags) :
			GLTexture(name, target, format, flags),
			RDTexture3D(sizeX, sizeY, sizeZ, numMips, format, flags)
		{

		}
	};
}