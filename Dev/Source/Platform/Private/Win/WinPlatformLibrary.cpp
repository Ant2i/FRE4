#include "NativePlatformLibrary.h"

#define NOMINMAX

#include <windows.h>
#undef LoadLibrary

namespace Platform
{
	PlatformLibrary::Handle PlatformLibrary::LoadLibrary(const Path& fileName)
	{
		HMODULE module = LoadLibraryW(fileName.GetCharData());
		return module;
	}

	void PlatformLibrary::FreeLibrary(Handle handle)
	{
		if (handle)
			::FreeLibrary(reinterpret_cast<HMODULE>(handle));
	}

	void* PlatformLibrary::ExportProc(Handle handle, const std::string& procName)
	{
		return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(handle), procName.c_str()));
	}

	void PlatformLibrary::SetFindLibraryDirectory(const Path& directory)
	{
		::SetDllDirectoryW(directory.GetCharData());
	}

	const wchar_t* PlatformLibrary::BaseDirectory()
	{
		wchar_t exeFileName[MAX_PATH];
		auto size = GetModuleFileNameW(NULL, exeFileName, MAX_PATH);
		if (size > 0)
		{
			std::wstring str;
			str.append(exeFileName, size);
			str = str.substr(0, str.find_last_of(L"\\/"));

			static wchar_t baseDir[MAX_PATH];
			auto len = str.copy(baseDir, MAX_PATH, 0);
			baseDir[len] = 0;
			return baseDir;
		}

		return nullptr;
	}

	const wchar_t* PlatformLibrary::GetLibraryPrefix()
	{
		return nullptr;
	}

	const wchar_t* PlatformLibrary::GetLibraryExtension()
	{
		return L".dll";
	}

	const wchar_t* PlatformLibrary::ExecutableName(bool bRemoveExtension)
	{
		return nullptr;
	}
}
