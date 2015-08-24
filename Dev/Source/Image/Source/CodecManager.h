#pragma once

#include "Forward.h"

#include <map>
#include <string>

namespace Image
{
	class CodecType
	{
	public:
		CodecType(const std::string & str);
		CodecType(CodecType && type);

		bool operator<(const CodecType & type) const;

	private:
		static void Format(std::string & str);

	private:
		std::string _str;
	};

	class CodecManager
	{
	public:
		static void RegisterCodec(const CodecP & codec);
		static void UnRegisterCodec(const CodecP & codec);

		static bool IsCodecRegistered(const std::string & type);

		static Codec * GetCodec(const std::string & type);
		static Codec * GetCodec(char * magicNumberPtr, size_t maxbytes);

	private:
		static void Set(const std::string & type, const CodecP & codec);
		static void Remove(const std::string & type);
		static CodecP Find(const std::string & type);

	private:
		typedef std::map<CodecType, CodecP> CodecContainer;
		static CodecContainer _codecs;
	};
}