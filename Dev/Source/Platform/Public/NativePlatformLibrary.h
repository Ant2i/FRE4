#pragma once

#include "Platform.h"
#include "NativePlatformPath.h"

#include <string>

namespace Platform
{
	class PlatformLibrary
	{
	public:
		typedef void* Handle;

	public:
		static Handle LoadLibrary(const Path& fileName);
		static void FreeLibrary(Handle handle);
		static void* ExportProc(Handle handle, const std::string& procName);

		static void SetFindLibraryDirectory(const Path& directory);

		static const wchar_t* BaseDirectory();
		static const wchar_t* ExecutableName(bool bRemoveExtension = true);

		static const wchar_t* GetLibraryPrefix();
		static const wchar_t* GetLibraryExtension();
	};
}