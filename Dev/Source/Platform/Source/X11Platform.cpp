#include "Platform.h"
#include "FPlatform.h"

#ifdef PLATFORM_LINUX

#include "utf8.h"

std::string ToUtf8(const wchar_t * str)
{
	std::wstring wstr(str);
	std::string res;

	utf8::utf16to8(wstr.begin(), wstr.end(), std::back_inserter(res));
	return res;
}

//-----------------------------------------------------------------------------

void * PlatformLibrary::LoadLibrary(const wchar_t * fileName)
{
	std::string fileNameUtf8 = ToUtf8(fileName);
	return dlopen(fileNameUtf8.c_str(), 2);
}
void PlatformLibrary::FreeLibrary(void* handle)
{
	if (handle)
		dlclose(handle);
}

void* PlatformLibrary::ExportProc(void* handle, const wchar_t * procName)
{
	return dlsym(handle, ToUtf8(procName).c_str());
}

#endif