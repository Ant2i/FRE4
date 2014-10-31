#pragma once

#include "FreRDResources.h"

namespace FRE
{
	class GLResource
	{
	public:
		GLResource(GLuint resource) :
			ResName(resource)
		{

		}

		const GLuint ResName;
	};

	class GLTexture : public GLResource
	{
	public:
		GLTexture(GLuint name, GLenum target, GLenum attachment) : GLResource(name),
			Target(target),
			Attachment(attachment)
		{

		}

		const GLenum Target;
		const GLenum Attachment;

		uint32 GetMemorySize() const
		{
			return _size;
		}

	protected:
		void SetMemorySize(uint32 size)
		{
			_size = size;
		}

	private:
		unsigned _size = 0;
	};

	//struct TextureInfo
	//{
	//	uint32 SizeX = 0;
	//	uint32 SizeY = 0;
	//	uint32 SizeZ = 0;
	//	uint32 NumMips = 0;
	//	uint32 NumSamples = 0;
	//	uint32 ArraySize = 0;
	//	EPixelFormat Format = EPixelFormat::Unknown;
	//};

	class GLTexture2D : public GLTexture, public RDTexture2D
	{
	public:
		GLTexture2D(GLuint name, GLenum target,	GLenum attachment, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) :
			GLTexture(name, target, attachment),
			RDTexture2D(sizeX, sizeY, numMips, numSamples, format, flags)
		{

		}
	};
}