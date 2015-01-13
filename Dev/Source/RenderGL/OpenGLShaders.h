#pragma once

#include "RDResources.h"
#include "OpenGLBase.h"

namespace FRE
{
	class GLShader
	{
	public:
		GLShader(GLuint name, bool destroy = false) :
			Name(name),
			_destroy(destroy)
		{

		}

		~GLShader()
		{
			if (Name && _destroy)
			{
				glDeleteShader(Name);
			}
		}

		const GLuint Name;

	private:
		bool _destroy = false;
	};

	//------------------------------------------------------------------

	template <GLenum _Type>
	class GLTypeShader : public GLShader
	{
	public:
		enum { Type = _Type };

		GLTypeShader(GLuint shader) : GLShader(shader)
		{

		}
	};

	//------------------------------------------------------------------

	class GLVertexShader : public GLTypeShader<GL_VERTEX_SHADER>, public RDVertexShader
	{
	public:
		GLVertexShader(GLuint shader) : GLTypeShader(shader)
		{

		}
	};

	//------------------------------------------------------------------

	class GLPixelShader : public GLTypeShader<GL_FRAGMENT_SHADER>, public RDPixelShader
	{
	public:
		GLPixelShader(GLuint shader) : GLTypeShader(shader)
		{

		}
	};

	//------------------------------------------------------------------

	class GLGeometryShader : public GLTypeShader<GL_GEOMETRY_SHADER>, public RDGeometryShader
	{
	public:
		GLGeometryShader(GLuint shader) : GLTypeShader(shader)
		{

		}
	};

	//------------------------------------------------------------------

	class GLHullShader : public GLTypeShader<GL_TESS_CONTROL_SHADER>, public RDHullShader
	{
	public:
		GLHullShader(GLuint shader) : GLTypeShader(shader)
		{

		}
	};

	//------------------------------------------------------------------

	class GLDomainShader : public GLTypeShader<GL_TESS_EVALUATION_SHADER>, public RDDomainShader
	{
	public:
		GLDomainShader(GLuint shader) : GLTypeShader(shader)
		{

		}
	};

	//------------------------------------------------------------------

	class GLComputeShader : public GLTypeShader<GL_COMPUTE_SHADER>, public RDComputeShader
	{
	public:
		GLComputeShader(GLuint shader) : GLTypeShader(shader)
		{

		}
	};
}