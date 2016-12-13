#pragma once

#include "Platform.h"

#include <string>
//#include <stdint.h>

namespace Platform
{
	typedef std::wstring Path;

	class IFile
	{
	public:
		virtual void Release() = 0;
		//Return the current write or read position
		virtual int64_t Pos() = 0;
		//Change the current write or read position.
		virtual bool Seek(int64_t pos) = 0;
		//Read bytes from the file.
		virtual int64_t Read(char * dest, int64_t bytesToRead) = 0;
		virtual int64_t Write(const char * src, int64_t bytesToWrite) = 0;

	protected:
		~IFile(){}
	};

	class PlatformFile
	{
	public:
		static IFile * OpenRead(const Path & fileName);
		static IFile * OpenWrite(const Path & fileName, bool append = false, bool allowRead = false);

		static Path AppendPath(const Path & path1, const Path & path2);
		static Path GetDirectory(const Path & path);

		static Path ConvertToPath(const std::string & path);
		static Path ConvertToPath(const std::wstring & path);

        static Path GetTemporaryFolderPath();
	};

	class PlatformLibrary
	{
	public:
		typedef void * Handle;

	public:
		static Handle LoadLibrary(const Path & fileName);
		static void FreeLibrary(Handle handle);
		static void * ExportProc(Handle handle, const std::string & procName);

		static void SetFindLibraryDirectory(const Path & directory);

		static const wchar_t * BaseDirectory();
		static const wchar_t * ExecutableName(bool bRemoveExtension = true);

		static const wchar_t * GetLibraryExtension();
	};
}