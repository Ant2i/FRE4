#pragma once

#include "NativePlatform.h"

namespace NativePlatform
{
	class Utils
	{
	public:
		static Path AppendPath(const Path & path1, const Path & path2);
		static Path GetDirectory(const Path & path);
		static Path GetFileName(const Path & path);
		static void GetFileName(const Path & path, Path & name, Path & dir);
	};
}
