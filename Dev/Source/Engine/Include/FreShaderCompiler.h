#pragma once

#include "FreTypes.h"
#include "RDEnums.h"
#include <vector>
#include <map>

namespace FRE
{
	struct ShaderTarget
	{
		EShaderType Frequency;
		EShaderPlatform Platform;
	};

	struct ShaderParameterMap
	{
		bool FindParameter(const char * name, uint16 & bufferIndex) const
		{
			auto it = _parameterMap.find(std::string(name));
			if (it != _parameterMap.end())
			{
				bufferIndex = it->second.BufferIndex;
				return true;
			}
			return false;
		}

		void AddParameter(const char * name, uint16 bufferIndex)
		{
			auto & data = _parameterMap[std::string(name)];
			data.BufferIndex = bufferIndex;
		}

	private:
		struct ParameterData
		{
			uint16 BufferIndex;
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
		std::vector<uint8> Code;
	};

	class IShaderCompiler
	{
		public:
			virtual void Compile() const = 0;
	};
}