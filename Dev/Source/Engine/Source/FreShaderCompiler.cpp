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

	bool LoadShaderSourceFile(const sPath & fileName, sString & outCode)
	{
		return false;
	}

	class GLSLShaderCompiler : public IShaderCompiler
	{
	public:
		virtual void Compile(const ShaderCompilerInput & input, ShaderCompilerOutput & output, const sPath & workingDirectory) const override
		{
			
		}
	};
}