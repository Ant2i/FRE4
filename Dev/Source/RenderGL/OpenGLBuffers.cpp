#include "OpenGLDevice.h"
#include "OpenGLResources.h"
#include "OpenGLResourceManager.h"

namespace FRE
{
	FORCEINLINE GLBuffer::MappingMode ConvertLockAccess(ELockMode access)
	{
		return access == ELockMode::Read ? GLBuffer::ReadOnly : GLBuffer::WriteOnly;
	}

    template <GLenum target>
    void BindOpenGLBuffer(GLContext & context, GLuint buffer)
    {
        FRE_ASSERT(false);
    }
    
    template <>
    void BindOpenGLBuffer<GL_ARRAY_BUFFER>(GLContext & context, GLuint buffer)
    {
        context.BindArrayBuffer(buffer);
    }
    
    template <>
    void BindOpenGLBuffer<GL_ELEMENT_ARRAY_BUFFER>(GLContext & context, GLuint buffer)
    {
        context.BindElementArrayBuffer(buffer);
    }
    
    template <GLenum Type>
    GLint CreateOpenGLBuffer(GLContext & context, uint32 size, uint32 usage, void * data)
    {
		GLuint buffer = FOpenGL::GenerateBuffer();
        BindOpenGLBuffer<Type>(context, buffer);
		glBufferData(Type, size, data, IsSetFlags(usage, EBufferUsageFlags::Dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        return buffer;
    }
    
	template <typename T>
    void * LockBuffer(GLContext & context, T * buffer, uint32 offset, uint32 size, GLBuffer::MappingMode mode)
    {
        if (buffer && buffer->Name)
        {
            BindOpenGLBuffer<T::Type>(context, buffer->Name);
            return buffer->Map(offset, size, mode);
        }
        return nullptr;
    }
    
    template <typename T>
    void UnlockBuffer(GLContext & context, T * buffer)
    {
        if (buffer && buffer->Name)
        {
            BindOpenGLBuffer<T::Type>(context, buffer->Name);
            buffer->Unmap();
        }
    }
    
	//-------------------------------------------------------------------------

	GLBuffer::~GLBuffer()
	{
		if (Name)
		{
			glDeleteBuffers(1, &Name);
		}
	}

	void GLVertexBuffer::Destroy()
	{
		GLResourceManager::GetInstance().Destroy(this);
	}

	void GLStructuredBuffer::Destroy()
	{
		GLResourceManager::GetInstance().Destroy(this);
	}

	void GLIndexBuffer::Destroy()
	{
		GLResourceManager::GetInstance().Destroy(this);
	}

	//-------------------------------------------------------------------------

	RDVertexBufferRef GLDevice::RDCreateVertexBuffer(uint32 size, uint32 usage, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLVertexBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLVertexBuffer(buffer, size, usage);
	}

	void * GLDevice::RDLockBuffer(RDVertexBufferRef bufferRef, uint32 offset, uint32 size, ELockMode access)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(bufferRef.Get());
        return LockBuffer(GetCurrentContext(), buffer, offset, size, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDVertexBufferRef bufferRef)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(bufferRef.Get());
        UnlockBuffer(GetCurrentContext(), buffer);
	}

	//

	RDStructureBufferRef GLDevice::RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data)
	{
		GLuint buffer = 0;
		if (FOpenGL::GetCapability().SupportStructuredBuffers)
			buffer = CreateOpenGLBuffer<GLStructuredBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLStructuredBuffer(buffer, size, usage, stride);
	}

	void * GLDevice::RDLockBuffer(RDStructureBufferRef bufferRef, uint32 offset, uint32 size, ELockMode access)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(bufferRef.Get());
		return LockBuffer(GetCurrentContext(), buffer, offset, size, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDStructureBufferRef bufferRef)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(bufferRef.Get());
		UnlockBuffer(GetCurrentContext(), buffer);
	}

	//

	RDIndexBufferRef GLDevice::RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLIndexBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLIndexBuffer(buffer, size, usage, stride);
	}

	void * GLDevice::RDLockBuffer(RDIndexBufferRef bufferRef, uint32 offset, uint32 size, ELockMode access)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(bufferRef.Get());
		return LockBuffer(GetCurrentContext(), buffer, offset, size, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDIndexBufferRef bufferRef)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(bufferRef.Get());
		UnlockBuffer(GetCurrentContext(), buffer);
	}

}