#pragma once

#include "FPlatform.h"

#ifdef _SYS_PLATFORM_EXPORTS
#define SYSP_API API_EXPORT_C
#else
#define SYSP_API API_IMPORT_C
#endif

class IFileStream
{
public:

};

class IPlatformFile
{
public:
	virtual IFileStream * OpenRead(const wchar_t * fileName) = 0;
	virtual IFileStream * OpenWrite(const wchar_t * fileName, bool append = false, bool allowRead = false) = 0;

};

class IPlatformLibrary
{
public:
	virtual void * LoadLibrary(const wchar_t * fileName) = 0;
	virtual void FreeLibrary(void* handle) = 0;
	virtual void* ExportProc(void* handle, const char * procName) = 0;

	virtual void SetFindLibraryDirectory(const wchar_t * directory) = 0;

	virtual const wchar_t * BaseDirectory() = 0;
	virtual const wchar_t * ExecutableName(bool bRemoveExtension = true) = 0;

	virtual const wchar_t * GetLibraryExtension() = 0;
};

SYSP_API IPlatformFile & PlatformFile();
SYSP_API IPlatformLibrary & PlatformLibrary();

