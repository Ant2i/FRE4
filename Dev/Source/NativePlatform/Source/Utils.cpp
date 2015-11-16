#include "Utils.h"

namespace NativePlatform
{
	Path Utils::AppendPath(const Path & path1, const Path & path2)
	{
		Path ret = path1;

		if (ret.size() > 1 && ret[ret.size() - 2] != L'/' && ret[ret.size() - 2] != L'\\')
			ret += L"/";

		ret += path2;
		return ret;
	}

	Path Utils::GetDirectory(const Path & path)
	{
		const size_t found = path.find_last_of(L"\\/");
		if (std::string::npos != found)
		{
			return path.substr(0, found);
		}
		return path;
	}

	Path Utils::GetFileName(const Path & path)
	{
		const size_t found = path.find_last_of(L"\\/");
		if (std::string::npos != found)
		{
			return path.substr(found + 1, path.size() - found);
		}
		return path;
	}
}