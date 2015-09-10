#include "X11Platform.h"

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

void * X11Platform::LoadLibrary(const wchar_t * fileName)
{
	std::string fileNameUtf8 = ToUtf8(fileName);
	return dlopen(fileNameUtf8.c_str(), 2);
}
void X11Platform::FreeLibrary(void* handle)
{
	if (handle)
		dlclose(handle);
}

void* X11Platform::ExportProc(void* handle, const wchar_t * procName)
{
	return dlsym(handle, ToUtf8(procName).c_str());
}

//-----------------------------------------------------------------------------

static X11Platform sPlatform;

SYSP_API IPlatformFile & PlatformFile()
{
	return sPlatform;
}

SYSP_API IPlatformLibrary & PlatformLibrary()
{
	return sPlatform;
}

#endif