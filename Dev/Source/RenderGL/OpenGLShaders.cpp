#include "OpenGLShaders.h"
#include "OpenGLDevice.h"

namespace FRE
{
	RDVertexShaderRef GLDevice::RDCreateVertexShader(const uint8 * source, unsigned size)
	{
		return new GLVertexShader(0);
	}

	RDPixelShaderRef GLDevice::RDCreatePixelShader(const uint8 * source, unsigned size)
	{
		return nullptr;
	}

	RDHullShaderRef GLDevice::RDCreateHullShader(const uint8 * source, unsigned size)
	{
		return nullptr;
	}

	RDDomainShaderRef GLDevice::RDCreateDomainShader(const uint8 * source, unsigned size)
	{
		return nullptr;
	}

	RDGeometryShaderRef GLDevice::RDCreateGeometryShader(const uint8 * source, unsigned size)
	{
		return nullptr;
	}
}