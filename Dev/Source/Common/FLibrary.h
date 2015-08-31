#pragma once

#include <string>

#if defined(_WIN32)
#include <windows.h>
#ifdef UNICODE
typedef std::wstring strPath;
#else
typedef std::string strPath;
#endif
#else
#include <dlfcn.h>
#include <libgen.h>
typedef std::string strPath;
#endif

strPath _GetLibraryName(const strPath & name)
{
	strPath sLibraryName = name;
#if defined(_WIN32)
	sLibraryName += ".dll";
#elif defined(__APPLE__)
    sLibraryName = "lib" + name + ".dylib";
 #else
     sLibraryName = "lib" + name + ".so";
#endif
    return sLibraryName;
}

void * _LoadLibrary(const strPath & libraryName, int iMode = 2)
{
	void * hLibrary = nullptr;
#if defined(_WIN32)
	hLibrary = (void *)LoadLibrary(libraryName.c_str());
#else
    hLibrary = dlopen(libraryName.c_str(), iMode);
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
	return FreeLibrary((HINSTANCE)hLibrary) == TRUE;
#else
	return dlclose(hLibrary);
#endif
}
