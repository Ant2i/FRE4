#include "OpenGLBase.h"
#include "OpenGLResources.h"
#include "OpenGLContext.h"

namespace FRE
{
	GLTexture::GLTexture(GLuint name, GLenum target, GLenum attachment) : GLResource(name),
		Target(target),
		AttachmentPoint(attachment)
	{

	}

	GLTexture::~GLTexture()
	{
		if (ResName)
		{
			glDeleteTextures(1, &ResName);
		}
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
		else if (format == EPixelFormat::Depth || format == EPixelFormat::D24)
			attachment = GL_DEPTH_ATTACHMENT;

		return attachment;
	}

	//----------------------------------------------------------------------------

	GLTexture2D * GLTexture2D::Create(GLContext & ctx, uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags)
	{
		GLuint textureName = 0;
		FOpenGL::GenTextures(1, &textureName);

		GLenum textureTarget = (numSamples > 1) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;

		const bool bSRGB = IsSetFlags(flags, ETextureCreateFlags::sRGB);
		
		if (textureName)
			return new GLTexture2D(textureName, textureTarget, sizeX, sizeY, numMips, numSamples, format, flags);
		return nullptr;
	}
}	

