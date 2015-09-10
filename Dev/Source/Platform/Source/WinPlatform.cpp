#include "WinPlatform.h"

#ifdef PLATFORM_WIN

WinPlatform::WinPlatform()
{
	GetModuleFileNameW(NULL, _baseDir, MAX_PATH);
}

std::wstring WinPlatform::GetLibraryName(const wchar_t * fileName)
{
	return std::wstring(fileName) + L".dll";
}

void * WinPlatform::LoadLibrary(const wchar_t * fileName)
{
	auto libraryName = GetLibraryName(fileName);



	return LoadLibraryW(fileName);
}

void WinPlatform::FreeLibrary(void * handle)
{
	if (handle)
		FreeLibrary((HINSTANCE)handle);
}

void * WinPlatform::ExportProc(void* handle, const char * procName)
{
	return GetProcAddress((HINSTANCE)handle, procName);
}

void WinPlatform::SetFindLibraryDirectory(const wchar_t * directory)
{
	::SetDllDirectoryW(directory);
}

const wchar_t * WinPlatform::GetLibraryExtension() 
{ 
	return L".dll";
}

//-----------------------------------------------------------------------------

static WinPlatform sPlatform;

SYSP_API IPlatformFile & PlatformFile()
{
	return sPlatform;
}

SYSP_API IPlatformLibrary & PlatformLibrary()
{
	return sPlatform;
}

#endif