#pragma once

#include <string>

#if defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

void * _LoadLibrary(const std::string & libraryName, int iMode = 2)
{
	std::string sLibraryName = libraryName;
	void * hLibrary = nullptr;
#if defined(_WIN32)
	sLibraryName += ".dll";
	hLibrary = (void *)LoadLibrary(sLibraryName.c_str());
#else
	sLibraryName += ".so";
	hLibrary = dlopen(sLibraryName.c_str(), iMode);
#endif
	return hLibrary;
}

void * _GetLibraryFunction(void * hLibrary, const std::string & functionName)
{
#if defined(_WIN32)
	return (void *)GetProcAddress((HINSTANCE)hLibrary, functionName.c_str());
#else
	return dlsym(hLibrary, functionName.c_str());
#endif
}

bool _FreeLibrary(void * hLibrary)
{
#if defined(_WIN32)
	return FreeLibrary((HINSTANCE)hLibrary);
#else
	return dlclose(hLibrary);
#endif
}
