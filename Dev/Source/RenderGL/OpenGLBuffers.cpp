#include "OpenGLDevice.h"
#include "OpenGLResources.h"

namespace FRE
{
	template <GLenum Type>
	GLint CreateOpenGLBuffer(GLContext & context, uint32 size, uint32 usage, void * data)
	{
		GLuint buffer = FOpenGL::GenerateBuffer();
		context.BindBuffer<Type>(buffer);
		glBufferData(Type, size, data, false ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		return buffer;
	}

	FORCEINLINE GLBuffer::MappingMode ConvertLockAccess(ELockMode access)
	{
		return access == ELockMode::Read ? GLBuffer::ReadOnly : GLBuffer::WriteOnly;
	}

	//-------------------------------------------------------------------------

	RDVertexBufferRef GLDevice::RDCreateVertexBuffer(uint32 size, uint32 usage, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLVertexBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLVertexBuffer(buffer, size, usage);
	}

	void * GLDevice::RHILockBuffer(RDVertexBufferRef bufferRef, uint32 offset, uint32 size, ELockMode access)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(bufferRef.Get());
		if (buffer)
			return buffer->Lock(GetCurrentContext(), offset, size, ConvertLockAccess(access));
		return nullptr;
	}

	void GLDevice::RHIUnlockBuffer(RDVertexBufferRef bufferRef)
	{
		GLVertexBuffer * buffer = static_cast<GLVertexBuffer *>(bufferRef.Get());
		if (buffer)
			return buffer->Unlock(GetCurrentContext());
	}

	//

	RDStructureBufferRef GLDevice::RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data)
	{
		GLuint buffer = 0;
		if (FOpenGL::GetCapability().SupportStructuredBuffers)
			buffer = CreateOpenGLBuffer<GLStructuredBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLStructuredBuffer(buffer, size, usage, stride);
	}

	void * GLDevice::RHILockBuffer(RDStructureBufferRef bufferRef, uint32 offset, uint32 size, ELockMode access)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(bufferRef.Get());
		if (buffer)
			return buffer->Lock(GetCurrentContext(), offset, size, ConvertLockAccess(access));
		return nullptr;
	}

	void GLDevice::RHIUnlockBuffer(RDStructureBufferRef bufferRef)
	{
		GLStructuredBuffer * buffer = static_cast<GLStructuredBuffer *>(bufferRef.Get());
		if (buffer)
			return buffer->Unlock(GetCurrentContext());
	}

	//

	RDIndexBufferRef GLDevice::RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data)
	{
		GLuint buffer = CreateOpenGLBuffer<GLIndexBuffer::Type>(GetCurrentContext(), size, usage, data);
		return new GLIndexBuffer(buffer, size, usage, stride);
	}

	void * GLDevice::RHILockBuffer(RDIndexBufferRef bufferRef, uint32 offset, uint32 size, ELockMode access)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(bufferRef.Get());
		if (buffer)
			return buffer->Lock(GetCurrentContext(), offset, size, ConvertLockAccess(access));
		return nullptr;
	}

	void GLDevice::RHIUnlockBuffer(RDIndexBufferRef bufferRef)
	{
		GLIndexBuffer * buffer = static_cast<GLIndexBuffer *>(bufferRef.Get());
		if (buffer)
			return buffer->Unlock(GetCurrentContext());
	}

}