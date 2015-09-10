#pragma once

#include "Platform.h"

#ifdef PLATFORM_LINUX

class X11Platform : public IPlatformLibrary, public IPlatformFile
{
public:
	virtual IFileStream * OpenRead(const wchar_t * fileName) override { return nullptr; }
	virtual IFileStream * OpenWrite(const wchar_t * fileName, bool append = false, bool allowRead = false) override { return nullptr; }


	virtual void * LoadLibrary(const wchar_t * fileName) override;
	virtual void FreeLibrary(void * handle ) override;
	virtual void * ExportProc(void * handle, const wchar_t * procName) override;

	virtual void PushFindLibraryDirectory(const wchar_t * directory) override { }
	virtual void PopFindLibraryDirectory() override { }

	virtual const wchar_t * BaseDirectory() override { return nullptr; }
	virtual const wchar_t * ExecutableName(bool bRemoveExtension = true) override { return nullptr; }

	virtual const wchar_t * GetLibraryExtension() override { return nullptr; }
};

#endif