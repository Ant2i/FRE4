#pragma once

#include "FStream.h"

class IFileHandle : public IStream
{
	public:

};

class IPlatformFile
{
public:
	virtual IFileHandle * OpenRead(const wchar_t * fileName) = 0;
	virtual IFileHandle * OpenWrite(const wchar_t * fileName, bool append = false, bool allowRead = false) = 0;


};

class IPlatformLibrary
{
public:
	virtual void * LoadLibrary( const wchar_t * fileName ) = 0;
	virtual void FreeLibrary( void* handle ) = 0;
	virtual void* ExportProc( void* handle, const wchar_t * procName) = 0;

	virtual void PushFindLibraryDirectory(const wchar_t * directory) = 0;
	virtual void PopFindLibraryDirectory() = 0;

	virtual const wchar_t * BaseDirectory() = 0;
	virtual const wchar_t * ExecutableName(bool bRemoveExtension = true) = 0;

	static const wchar_t * GetLibraryExtension() = 0;
};

