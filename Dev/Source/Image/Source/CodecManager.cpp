#include "CodecManager.h"
#include "Codec.h"
#include <algorithm>

namespace Image
{
	CodecManager::CodecContainer CodecManager::_codecs;

	//-------------------------------------------------------------------------

	void CodecManager::RegisterCodec(const CodecP & codec)
	{
		Set(codec->GetType(), codec);
	}

	bool CodecManager::IsCodecRegistered(const std::string & type)
	{
		return Find(type).get() != nullptr;
	}

	void CodecManager::UnRegisterCodec(const CodecP & codec)
	{
		Remove(codec->GetType());
	}

	Codec * CodecManager::GetCodec(const std::string & type)
	{
		return Find(type).get();
	}

	Codec * CodecManager::GetCodec(char * magicNumberPtr, size_t maxbytes)
	{
		return nullptr;
		//TODO
		for (auto & it : _codecs)
		{
			const CodecP & codec = it.second;
			std::string type = codec->MagicNumberToFileExt(magicNumberPtr, maxbytes);

			if (!type.empty())
			{
				if (type == codec->GetType())
					return codec.get();
				else
					return GetCodec(type);
			}
		}
		return nullptr;
	}

	void CodecManager::Set(const std::string & type, const CodecP & codec)
	{
		_codecs[type] = codec;
	}

	void CodecManager::Remove(const std::string & type)
	{
		_codecs.erase(type);
	}

	CodecP CodecManager::Find(const std::string & type)
	{
		auto it = _codecs.find(type);
		if (it != _codecs.end())
			return it->second;
		return nullptr;
	}

	//-------------------------------------------------------------------------

	CodecType::CodecType(const std::string & str) :
		_str(str)
	{
		Format(_str);
	}

	CodecType::CodecType(CodecType && type) :
		_str(std::move(type._str))
	{

	}

	bool CodecType::operator<(const CodecType & type) const
	{
		return _str < type._str;
	}

	void CodecType::Format(std::string & str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}
}
