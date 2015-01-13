#include "OpenGLDevice.h"
#include "OpenGLTextures.h"
#include "OpenGLPixelFormat.h"

namespace FRE
{
    FORCEINLINE GLenum GetTextureInternalFormat(const OpenGLPixelDataFormat & glformat, bool bSRGB)
    {
        GLenum internalFormat = glformat.InternalFormat;
        
        if (bSRGB)
            internalFormat = glformat.InternalFormatSRGB;
        
        if (internalFormat == GL_NONE)
            FPrintLocal("Texture format not supported.");
        
        return internalFormat;
    }
    
    FORCEINLINE GLuint BindTextureIndex()
    {
        static const GLuint bindIndex = FOpenGL::GetCapability().MaxCombinedTextureImageUnits - 1;
        return bindIndex;
    }
    
    GLint CreateOpenGLTexture2D(GLContext & context, GLenum target, uint32 sizeX, uint32 sizeY, uint32 numMips, GLenum internalFormat)
    {
        GLuint texture = 0;
        FOpenGL::GenTextures(1, &texture);
        context.BindTexture(BindTextureIndex(), texture, target);
        
        FOpenGL::TexParameter(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        FOpenGL::TexParameter(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        FOpenGL::TexParameter(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        FOpenGL::TexParameter(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        if (FOpenGL::GetCapability().SupportTextureBaseLevel)
            FOpenGL::TexParameter(target, GL_TEXTURE_BASE_LEVEL, 0);
        
        if (FOpenGL::GetCapability().SupportTextureMaxLevel)
            FOpenGL::TexParameter(target, GL_TEXTURE_MAX_LEVEL, numMips - 1);

        
        FOpenGL::TexStorage2D(target, numMips, internalFormat, sizeX, sizeY, GL_RED, GL_BYTE, 0);
        return texture;
    }
    
    GLint CreateOpenGLTexture2DMS(GLContext & context, uint32 sizeX, uint32 sizeY, uint32 numSamples, GLenum internalFormat)
    {
        const GLenum target = GL_TEXTURE_2D_MULTISAMPLE;
        
        GLuint texture = 0;
        FOpenGL::GenTextures(1, &texture);
        context.BindTexture(BindTextureIndex(), texture, target);
        FOpenGL::TexImage2DMultisample(target, numSamples, internalFormat, sizeX, sizeY, true);
        return texture;
    }
    
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

	void * GLTexture::Lock(GLContext & context, uint32 mipIndex, uint32 arrayIndex, ELockMode lockMode)
	{
		return nullptr;
	}

	void GLTexture::Unlock(GLContext & context, uint32 mipIndex, uint32 arrayIndex)
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

		const bool needSRGB = IsSetFlags(flags, ETextureCreateFlags::sRGB);
		const OpenGLPixelDataFormat & glFormat = GetGLPixelDataFormat(format);

		GLenum textureInternalFormat = GetTextureInternalFormat(glFormat, needSRGB);


		const GLenum textureTarget = (numSamples > 1) ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		static const GLuint bindIndex = FOpenGL::GetCapability().MaxCombinedTextureImageUnits - 1;
		ctx.BindTexture(bindIndex, textureName, textureTarget);
		ctx.BindPixelUnpackBuffer(0);

		if (numSamples > 1)
		{
			FOpenGL::TexImage2DMultisample(textureTarget, numSamples, textureInternalFormat, sizeX, sizeY, true);
		}
		else
		{
			FOpenGL::TexParameter(textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			FOpenGL::TexParameter(textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			FOpenGL::TexParameter(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			FOpenGL::TexParameter(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			
			if (FOpenGL::GetCapability().SupportTextureBaseLevel)
				FOpenGL::TexParameter(textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
			
			if (FOpenGL::GetCapability().SupportTextureMaxLevel)
				FOpenGL::TexParameter(textureTarget, GL_TEXTURE_MAX_LEVEL, numMips - 1);

            FOpenGL::TexStorage2D(textureTarget, numMips, textureInternalFormat, sizeX, sizeY, glFormat.Format, glFormat.Type, 0);
		}

		return new GLTexture2D(textureName, textureTarget, sizeX, sizeY, numMips, numSamples, format, flags);
	}

	//-------------------------------------------------------------------------

	RDTexture2DRef GLDevice::RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 flags)
	{
		return GLTexture2D::Create(GetCurrentContext(), sizeX, sizeY, numMips, 0, (EPixelFormat)format, flags);
	}
    
    RDTexture2DRef GLDevice::RDCreateTexture2DMS(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numSamples, uint32 flags)
    {
        return nullptr;//GLTexture2D::Create(GetCurrentContext(), sizeX, sizeY, numMips, numSamples, (EPixelFormat)format, flags);
    }
}