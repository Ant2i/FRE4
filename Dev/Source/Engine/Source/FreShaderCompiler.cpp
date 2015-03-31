#include "FreShaderCompiler.h"
#include "FStreamMemory.h"

namespace FRE
{
	struct GLSLByteCode
	{
		uint8 NumUniformBuffers;
		uint8 NumSamplers;

		std::string StrCode;
	};

	class GLSLShaderCompiler : public IShaderCompiler
	{
	public:
		virtual void Compile(const ShaderCompilerInput & input, ShaderCompilerOutput & output, const sPath & workingDirectory) const override
		{
			
		}
	};
}