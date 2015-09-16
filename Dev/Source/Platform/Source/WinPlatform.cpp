#include "Platform.h"
#include "FPlatform.h"

#ifdef PLATFORM_WIN

#include <windows.h>
#undef LoadLibrary

#include <vector>
#include <string>

std::wstring GetLibraryName(const wchar_t * fileName)
{
	return std::wstring(fileName) + L".dll";
}

void * PlatformLibrary::LoadLibrary(const wchar_t * fileName)
{
	auto libraryName = GetLibraryName(fileName);
	return LoadLibraryW(fileName);
}

void PlatformLibrary::FreeLibrary(void * handle)
{
	if (handle)
		::FreeLibrary((HINSTANCE)handle);
}

void * PlatformLibrary::ExportProc(void * handle, const char * procName)
{
	return GetProcAddress((HINSTANCE)handle, procName);
}

void PlatformLibrary::SetFindLibraryDirectory(const wchar_t * directory)
{
	::SetDllDirectoryW(directory);
}

const wchar_t * PlatformLibrary::BaseDirectory() 
{ 
	static wchar_t baseDir[MAX_PATH];
	GetModuleFileNameW(NULL, baseDir, MAX_PATH);
	return baseDir; 
}

const wchar_t * PlatformLibrary::GetLibraryExtension()
{ 
	return L".dll";
}

const wchar_t * PlatformLibrary::ExecutableName(bool bRemoveExtension)
{ 
	return nullptr; 
}

#endif