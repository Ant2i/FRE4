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
		
		static void CStringToPath(const char * str, Path& path);
		static void CStringToPath(const wchar_t * str, Path& path);
	};
}
