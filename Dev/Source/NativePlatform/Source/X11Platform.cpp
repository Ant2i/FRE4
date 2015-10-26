#include "Platform.h"
#include "FPlatform.h"

#ifdef PLATFORM_LINUX

#include <dlfcn.h>
#include "utf8.h"

std::string ToUtf8(const std::wstring & str)
{
	std::wstring wstr(str);
	std::string res;

	utf8::utf16to8(wstr.begin(), wstr.end(), std::back_inserter(res));
	return res;
}

std::string ToUtf8(const wchar_t * str)
{
	return ToUtf8(std::wstring(str));
}

//-----------------------------------------------------------------------------

std::wstring GetLibraryName(const wchar_t * fileName)
{
	return L"lib" + std::wstring(fileName) + L".so";
}

void * PlatformLibrary::LoadLibrary(const wchar_t * fileName)
{
	std::string fileNameUtf8 = ToUtf8(GetLibraryName(fileName));
	void * ret = dlopen(fileNameUtf8.c_str(), 2);

	if (!ret)
	{
		char * err = dlerror();
		int d = 0;
	}

    return ret;
}
void PlatformLibrary::FreeLibrary(void* handle)
{
	if (handle)
		dlclose(handle);
}

void* PlatformLibrary::ExportProc(void* handle, const char * procName)
{
	return dlsym(handle, procName);
}

const wchar_t * PlatformLibrary::GetLibraryExtension()
{
	return L".so";
}

const wchar_t * PlatformLibrary::BaseDirectory()
{
	return nullptr;
}

const wchar_t * PlatformLibrary::ExecutableName(bool bRemoveExtension)
{
	return nullptr;
}


#endif
