#include "OpenGLDevice.h"
#include "OpenGLResources.h"

namespace FRE
{
	GLTexture::GLTexture(GLuint name, GLenum target, GLenum attachment) :
		Name(name),
		Target(target),
		AttachmentPoint(attachment)
	{

	}

	GLTexture::GLTexture(GLuint name, GLenum target, EPixelFormat format, uint32 flags) :
		Name(name),
		Target(target),
		AttachmentPoint(GetAttachment(format, flags))
	{

	}

	GLTexture::~GLTexture()
	{
		if (Name)
			glDeleteTextures(1, &Name);
	}

	void * GLTexture::Lock(uint32 MipIndex, uint32 ArrayIndex, ELockMode lockMode)
	{
		return nullptr;
	}

	void GLTexture::Unlock(uint32 MipIndex, uint32 ArrayIndex)
	{

	}

	GLenum GLTexture::GetAttachment(EPixelFormat format, uint32 flags)
	{
		GLenum attachment = GL_COLOR_ATTACHMENT0;

		if (format == EPixelFormat::DepthStencil && FOpenGL::GetCapability().SupportCombinedDepthStencilAttachment)
			attachment = GL_DEPTH_STENCIL_ATTACHMENT;
		else if (format == EPixelFormat::Depth)
			attachment = GL_DEPTH_ATTACHMENT;

		return attachment;
	}

	GLTexture2D * GLTexture2D::Create(GLContext & ctx, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags)
	{
		GLuint textureName = 0;
		FOpenGL::GenTextures(1, &textureName);

		GLenum textureTarget = (numSamples > 1) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;

		const bool bSRGB = IsSetFlags(flags, ETextureCreateFlags::sRGB);

		GLuint bindIndex = FOpenGL::GetCapability().MaxCombinedTextureImageUnits - 1;
		ctx.BindTexture(bindIndex, textureName, textureTarget, numMips);

		return new GLTexture2D(textureName, textureTarget, sizeX, sizeY, numMips, numSamples, format, flags);
	}

	//-------------------------------------------------------------------------

	RDTexture2DRef GLDevice::RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags)
	{
		return GLTexture2D::Create(GetCurrentContext(), sizeX, sizeY, numMips, numSamples, (EPixelFormat)format, flags);
	}
}