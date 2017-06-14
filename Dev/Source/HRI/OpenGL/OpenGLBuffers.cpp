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
    GLint CreateOpenGLBuffer(GLContext & context, uint32_t iSize, uint32_t iUsage, void * data)
    {
		GLuint buffer = FOpenGL::GenerateBuffer();
        BindOpenGLBuffer<Type>(context, buffer);
		glBufferData(Type, iSize, data, IsSetFlags(iUsage, EBufferUsageFlags::Dynamic) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
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
	void * GLTypeBuffer<_Type>::Lock(GLContext & context, uint32_t offset, uint32_t iSize, MappingMode mode)
	{
		if (Name)
		{
			_locked = true;
			BindOpenGLBuffer<_Type>(context, Name);
			const auto access = mode == ReadOnly ? OpenGLAPI::LockMode::Read : OpenGLAPI::LockMode::Write;
			return FOpenGL::MapBufferRange(_Type, offset, iSize, access);
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

	RDVertexBufferRef GLDevice::RDCreateVertexBuffer(uint32_t iSize, uint32_t iUsage, void * iData)
	{
		GLuint buffer = CreateOpenGLBuffer<GLVertexBuffer::Type>(GetCurrentContext(), iSize, iUsage, iData);
		return new GLVertexBuffer(buffer, iSize, iUsage);
	}

	void * GLDevice::RDLockBuffer(RDVertexBufferP iBuffer, uint32_t iOffset, uint32_t iSize, ELockMode iAccess)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(iBuffer);
		return buffer->Lock(GetCurrentContext(), iOffset, iSize, ConvertLockAccess(iAccess));
	}

	void GLDevice::RDUnlockBuffer(RDVertexBufferP iBuffer)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(iBuffer);
		buffer->Unlock(GetCurrentContext());
	}

	//

	RDStructureBufferRef GLDevice::RDCreateStructureBuffer(uint32_t iSize, uint32_t iUsage, uint32_t iStride, void * data)
	{
		GLuint buffer = 0;
		if (FOpenGL::GetCapability().SupportStructuredBuffers)
			buffer = CreateOpenGLBuffer<GLStructuredBuffer::Type>(GetCurrentContext(), iSize, iUsage, data);
		return new GLStructuredBuffer(buffer, iSize, iUsage, iStride);
	}

	void * GLDevice::RDLockBuffer(RDStructureBufferP iBuffer, uint32_t offset, uint32_t iSize, ELockMode iAccess)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(iBuffer);
		return buffer->Lock(GetCurrentContext(), offset, iSize, ConvertLockAccess(iAccess));
	}

	void GLDevice::RDUnlockBuffer(RDStructureBufferP iBuffer)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(iBuffer);
		buffer->Unlock(GetCurrentContext());
	}

	//

	RDIndexBufferRef GLDevice::RDCreateIndexBuffer(uint32_t iSize, uint32_t iUsage, uint32_t iStride, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLIndexBuffer::Type>(GetCurrentContext(), iSize, iUsage, data);
		return new GLIndexBuffer(buffer, iSize, iUsage, iStride);
	}

	void * GLDevice::RDLockBuffer(RDIndexBufferP iBuffer, uint32_t offset, uint32_t iSize, ELockMode access)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(iBuffer);
		return buffer->Lock(GetCurrentContext(), offset, iSize, ConvertLockAccess(access));
	}

	void GLDevice::RDUnlockBuffer(RDIndexBufferP iBuffer)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(iBuffer);
		buffer->Unlock(GetCurrentContext());
	}

}
