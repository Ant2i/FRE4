#pragma once

#include "FreTypes.h"

#include "RDEnums.h"
#include <vector>
#include <map>

namespace FRE
{
	struct ShaderTarget
	{
		EShaderPlatform Platform;
		EShaderType Frequency;
	};

	struct ShaderParameterMap
	{
		bool FindParameter(const char * name, unsigned & bufferIndex) const
		{
			auto it = _parameterMap.find(std::string(name));
			if (it != _parameterMap.end())
			{
				bufferIndex = it->second.BufferIndex;
				return true;
			}
			return false;
		}

		void AddParameter(const char * name, unsigned bufferIndex)
		{
			auto & data = _parameterMap[std::string(name)];
			data.BufferIndex = bufferIndex;
		}

	private:
		struct ParameterData
		{
			unsigned BufferIndex;
		};

		std::map<std::string, ParameterData> _parameterMap;
	};

	struct ShaderCompilerInput
	{
		ShaderTarget Target;
		sPath SourceFilePrefix;
		sPath SourceFilename;
	};

	struct ShaderCompilerOutput
	{
		ShaderTarget Target;
		ShaderParameterMap ParameterMap;
		std::vector<uint8_t> Code;
	};

	class IShaderCompiler
	{
	public:
		virtual void Compile(const ShaderCompilerInput & input, ShaderCompilerOutput & output, const sPath & workingDirectory) const = 0;
	};
}
