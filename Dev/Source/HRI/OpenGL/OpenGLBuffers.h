#pragma once

#include "RDResources.h"
#include "OpenGLBase.h"

namespace FRE
{
	class GLContext;

	class GLBuffer
	{
	public:
		enum MappingMode
		{
			ReadOnly,
			WriteOnly
		};

	public:
		const GLuint Name;

		GLBuffer(GLuint name) :
			Name(name)
		{

		}

		virtual ~GLBuffer();
	};

	//------------------------------------------------------------------

	template <GLenum _Type>
	class GLTypeBuffer : public GLBuffer
	{
	public:
		enum { Type = _Type };

		GLTypeBuffer(GLuint buffer) : GLBuffer(buffer)
		{

		}

		void * Lock(GLContext & context, uint32_t offset, uint32_t size, MappingMode mode);
		void Unlock(GLContext & context);

	private:
		bool _locked = false;
	};

	//------------------------------------------------------------------

	class GLVertexBuffer : public GLTypeBuffer<GL_ARRAY_BUFFER>, public RDVertexBuffer
	{
	public:
		GLVertexBuffer(GLuint buffer, GLuint size, uint32_t usage) :
			GLTypeBuffer(buffer),
			RDVertexBuffer(size, usage)
		{

		}

		virtual void Destroy() override;
	};

	//------------------------------------------------------------------

	class GLStructuredBuffer : public GLTypeBuffer<GL_ARRAY_BUFFER>, public RDStructureBuffer
	{
	public:
		GLStructuredBuffer(GLuint buffer, GLuint size, uint32_t usage, GLuint stride) :
			GLTypeBuffer(buffer),
			RDStructureBuffer(size, usage, stride)
		{

		}

		virtual void Destroy() override;
	};

	//------------------------------------------------------------------

	class GLIndexBuffer : public GLTypeBuffer<GL_ELEMENT_ARRAY_BUFFER>, public RDIndexBuffer
	{
	public:
		GLIndexBuffer(GLuint buffer, GLuint size, uint32_t usage, GLuint stride) :
			GLTypeBuffer(buffer),
			RDIndexBuffer(size, usage, stride)
		{

		}

		virtual void Destroy() override;
	};
}
