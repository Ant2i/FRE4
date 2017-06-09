#pragma once

#include "Platform.h"
#include "NativePlatformPath.h"

namespace Platform
{
	class IFile
	{
	public:
		virtual void Release() = 0;
		//Return the current write or read position.
		virtual int64 Pos() = 0;
		//Change the current write or read position.
		virtual bool Seek(int64 pos) = 0;
		//Read bytes from the file.
		virtual int64 Read(char* dest, int64 bytesToRead) = 0;
		virtual int64 Write(const char* src, int64 bytesToWrite) = 0;

	protected:
		~IFile(){}
	};

	class PlatformFile
	{
	public:
		static IFile* OpenRead(const Path& path);
		static IFile* OpenWrite(const Path& path, bool append = false, bool allowRead = false);

        static Path GetTemporaryFolderPath();
	};
}