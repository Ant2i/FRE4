#include "OpenGLBase.h"
#include "OpenGLResources.h"
#include "OpenGLContext.h"

namespace FRE
{
	GLTexture::GLTexture(GLuint name, GLenum target, GLenum attachment) : 
		Name(name),
		Target(target),
		AttachmentPoint(attachment)
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
		
		return new GLTexture2D(textureName, textureTarget, sizeX, sizeY, numMips, numSamples, format, flags);
	}

	//-------------------------------------------------------------------------

	GLVertexBuffer * GLVertexBuffer::Create(GLContext & ctx, GLuint size, uint32 usage, const void * data)
	{
		GLuint buffer = FOpenGL::GenerateBuffer();
		Bind(ctx, buffer);

		glBufferData(GLVertexBuffer::Target, size, data, false ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

		return new GLVertexBuffer(buffer, size, usage);
	}

	void GLVertexBuffer::Bind(GLContext & ctx, GLuint buffer)
	{
		ctx.BindArrayBuffer(buffer);
	}

	void * GLVertexBuffer::Lock(GLContext & ctx, uint32 offset, uint32 size, bool readOnly)
	{
		Bind(ctx, Name);
		return Map(offset, size, readOnly);
	}

	void GLVertexBuffer::UnLock(GLContext & ctx)
	{
		Bind(ctx, Name);
		UnMap();
	}

    //--
	
	GLIndexBuffer * GLIndexBuffer::Create(GLContext & ctx, GLuint size, uint32 usage, GLuint stride, const void * data)
	{
		GLuint buffer = FOpenGL::GenerateBuffer();
		Bind(ctx, buffer);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, false ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

		return new GLIndexBuffer(buffer, size, usage, stride);
	}

	void GLIndexBuffer::Bind(GLContext & ctx, GLuint buffer)
	{
		ctx.BindElementArrayBuffer(buffer);
	}

	void * GLIndexBuffer::Lock(GLContext & ctx, uint32 offset, uint32 size, bool readOnly)
	{
		Bind(ctx, Name);
		return Map(offset, size, readOnly);
	}

	void GLIndexBuffer::UnLock(GLContext & ctx)
	{
		Bind(ctx, Name);
		UnMap();
	}
}	

