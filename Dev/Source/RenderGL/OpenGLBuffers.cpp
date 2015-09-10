#include "OpenGLDevice.h"
#include "OpenGLBuffers.h"
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
        F_ASSERT(false);
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
    GLint CreateOpenGLBuffer(GLContext & context, uint32_t size, uint32_t usage, void * data)
    {
		GLuint buffer = FOpenGL::GenerateBuffer();
        BindOpenGLBuffer<Type>(context, buffer);
		glBufferData(Type, size, data, IsSetFlags(usage, EBufferUsageFlags::Dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        return buffer;
    }
    
	//-------------------------------------------------------------------------

	GLBuffer::~GLBuffer()
	{
		if (Name)
		{
			glDeleteBuffers(1, &Name);
		}
	}

	//-------------------------------------------------------------------------

	template <GLenum _Type>
	void * GLTypeBuffer<_Type>::Lock(GLContext & context, uint32_t offset, uint32_t size, MappingMode mode)
	{
		if (Name)
		{
			_locked = true;
			BindOpenGLBuffer<_Type>(context, Name);
			const auto access = mode == ReadOnly ? OpenGLAPI::LockMode::Read : OpenGLAPI::LockMode::Write;
			return FOpenGL::MapBufferRange(_Type, offset, size, access);
		}
		return nullptr;
	}

	template <GLenum _Type>
	void GLTypeBuffer<_Type>::Unlock(GLContext & context)
	{
		if (Name)
		{
			BindOpenGLBuffer<_Type>(context, Name);
			FOpenGL::UnmapBuffer(_Type);
			_locked = true;
		}
	}

	//-------------------------------------------------------------------------

	void GLVertexBuffer::Destroy()
	{
		GLResourceManager::GetInstance().DestroyArrayBuffer(this);
	}

	//-------------------------------------------------------------------------

	void GLStructuredBuffer::Destroy()
	{
		GLResourceManager::GetInstance().DestroyArrayBuffer(this);
	}

	//-------------------------------------------------------------------------

	void GLIndexBuffer::Destroy()
	{
		GLResourceManager::GetInstance().DestroyElementBuffer(this);
	}

	//-------------------------------------------------------------------------

	RDVertexBufferRef GLDevice::RDCreateVertexBuffer(uint32_t size, uint32_t usage, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLVertexBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLVertexBuffer(buffer, size, usage);
	}

	void * GLDevice::RDLockBuffer(RDVertexBufferRef bufferRef, uint32_t offset, uint32_t size, ELockMode access)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(bufferRef.Get());
		return buffer->Lock(GetCurrentContext(), offset, size, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDVertexBufferRef bufferRef)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(bufferRef.Get());
		buffer->Unlock(GetCurrentContext());
	}

	//

	RDStructureBufferRef GLDevice::RDCreateStructureBuffer(uint32_t size, uint32_t usage, uint32_t stride, void * data)
	{
		GLuint buffer = 0;
		if (FOpenGL::GetCapability().SupportStructuredBuffers)
			buffer = CreateOpenGLBuffer<GLStructuredBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLStructuredBuffer(buffer, size, usage, stride);
	}

	void * GLDevice::RDLockBuffer(RDStructureBufferRef bufferRef, uint32_t offset, uint32_t size, ELockMode access)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(bufferRef.Get());
		return buffer->Lock(GetCurrentContext(), offset, size, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDStructureBufferRef bufferRef)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(bufferRef.Get());
		buffer->Unlock(GetCurrentContext());
	}

	//

	RDIndexBufferRef GLDevice::RDCreateIndexBuffer(uint32_t size, uint32_t usage, uint32_t stride, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLIndexBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLIndexBuffer(buffer, size, usage, stride);
	}

	void * GLDevice::RDLockBuffer(RDIndexBufferRef bufferRef, uint32_t offset, uint32_t size, ELockMode access)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(bufferRef.Get());
		return buffer->Lock(GetCurrentContext(), offset, size, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDIndexBufferRef bufferRef)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(bufferRef.Get());
		buffer->Unlock(GetCurrentContext());
	}

}