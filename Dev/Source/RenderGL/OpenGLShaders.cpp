#include "OpenGLShaders.h"
#include "OpenGLDevice.h"

namespace FRE
{
	static GLuint ShaderUniqueId = 0;

	GLShader::GLShader(GLuint name, bool destroy) :
		Name(name),
		_destroy(destroy),
		UniqueId(ShaderUniqueId++)
	{

	}

	GLShader::~GLShader()
	{
		if (Name && _destroy)
		{
			glDeleteShader(Name);
		}
	}

	//-------------------------------------------------------------------------

	template <typename TypeShader>
	TypeShader * GLCreateAndCompileShader(const uint8 * source, unsigned size)
	{
		return new TypeShader(0);
	}

	RDVertexShaderRef GLDevice::RDCreateVertexShader(const uint8 * source, unsigned size)
	{
		return GLCreateAndCompileShader<GLVertexShader>(source, size);
	}

	RDPixelShaderRef GLDevice::RDCreatePixelShader(const uint8 * source, unsigned size)
	{
		return GLCreateAndCompileShader<GLPixelShader>(source, size);
	}

	RDHullShaderRef GLDevice::RDCreateHullShader(const uint8 * source, unsigned size)
	{
		return GLCreateAndCompileShader<GLHullShader>(source, size);
	}

	RDDomainShaderRef GLDevice::RDCreateDomainShader(const uint8 * source, unsigned size)
	{
		return GLCreateAndCompileShader<GLDomainShader>(source, size);
	}

	RDGeometryShaderRef GLDevice::RDCreateGeometryShader(const uint8 * source, unsigned size)
	{
		return GLCreateAndCompileShader<GLGeometryShader>(source, size);
	}
}