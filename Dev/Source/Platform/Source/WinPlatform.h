#pragma once

#include "Platform.h"

#ifdef PLATFORM_WIN

#include <windows.h>
#undef LoadLibrary

#include <vector>
#include <string>

class WinPlatform : public IPlatformLibrary, public IPlatformFile
{
public:
	WinPlatform();

	virtual IFileStream * OpenRead(const wchar_t * fileName) override { return nullptr; }
	virtual IFileStream * OpenWrite(const wchar_t * fileName, bool append = false, bool allowRead = false) override { return nullptr; }

	virtual void * LoadLibrary(const wchar_t * fileName) override;
	virtual void FreeLibrary(void * handle) override;
	virtual void * ExportProc(void * handle, const char * procName) override;

	virtual void SetFindLibraryDirectory(const wchar_t * directory) override;

	// Get startup directory.
	virtual const wchar_t * BaseDirectory() override { return _baseDir; }
	virtual const wchar_t * ExecutableName(bool bRemoveExtension = true) override { return nullptr; }

	virtual const wchar_t * GetLibraryExtension() override;

private:
	std::wstring GetLibraryName(const wchar_t * fileName);

private:
	wchar_t _baseDir[MAX_PATH];
};

#endif