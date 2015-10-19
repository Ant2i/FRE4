#pragma once

class IFileStream
{
public:

};

class PlatformFile
{
public:
	static IFileStream * OpenRead(const wchar_t * fileName);
	static IFileStream * OpenWrite(const wchar_t * fileName, bool append = false, bool allowRead = false);
};

class PlatformLibrary
{
public:
	static void * LoadLibrary(const wchar_t * fileName);
	static void FreeLibrary(void * handle);
	static void * ExportProc(void * handle, const char * procName);

	static void SetFindLibraryDirectory(const wchar_t * directory);

	static const wchar_t * BaseDirectory();
	static const wchar_t * ExecutableName(bool bRemoveExtension = true);

	static const wchar_t * GetLibraryExtension();
};
