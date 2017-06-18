#pragma once

#include "Platform.h"
#include <string>

namespace Platform
{
	class Path
	{
	public:
		Path();
		Path(const Path&);
		~Path();

		void Append(const tchar*, uint32 size);

		Path GetDirectory() const;
		Path GetFileName() const;
		
		//Without null terminate.
		const tchar* GetCharData() const;
		int GetSize() const;

	public:
		static Path ConvertToPath(const tchar* str, uint32 size)
		{
			Path path;
			path.Append(str, size);
			return path;
		}

		static Path ConvertToPath(const std::wstring& str)
		{
			return ConvertToPath(str.data(), (uint32)str.size());
		}

		static Path ConvertToPath(const std::string& str)
		{
			return ConvertToPath(std::wstring(str.begin(), str.end()));
		}

		//return count copy elems.
		static uint32 Fill(const Path& path, tchar* outPtr, int outSize)
		{
			const tchar* pathPtr = path.GetCharData();
			const uint32 minSize = path.GetSize() < outSize ? path.GetSize() : outSize;
			for (uint32 i = 0; i < minSize; ++i)
				outPtr[i] = pathPtr[i];
			return minSize;
		}

	private:
		friend class PathPrivate;
		Path(PathPrivate&);

	private:
		PathPrivate* _p;
	};
}
