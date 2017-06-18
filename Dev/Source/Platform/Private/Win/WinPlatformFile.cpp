#include "NativePlaformFile.h"

#define NOMINMAX

#include <windows.h>
#undef LoadLibrary

#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

namespace Platform
{
	class FileHandleWindows : public IFile
	{
		enum 
		{ 
			READWRITE_SIZE = 1024 * 1024 
		};

	public:
		FileHandleWindows(HANDLE handle = NULL) :
			_handle(handle)
		{
		}

		~FileHandleWindows()
		{
			CloseHandle(_handle);
			_handle = NULL;
		}

		virtual void Release() override
		{
			delete this;
		}

		virtual int64 Pos() override
		{
			assert(IsValid() == true);
			return FileSeek(0, FILE_CURRENT);
		}

		virtual bool Seek(int64 pos) override
		{
			assert(IsValid() == true);
			assert(pos >= 0);
			return FileSeek(pos, FILE_BEGIN) != -1;
		}

		virtual int64 Read(char * dest, int64 bytesToRead) override
		{
			int64 readBytes = 0;

			assert(IsValid() == true);
			while (bytesToRead)
			{
				assert(bytesToRead >= 0);
				int64 batchSize = std::min((int64)READWRITE_SIZE, bytesToRead);

				assert(dest);
				uint32_t result = 0;
				if (!ReadFile(_handle, dest, uint32_t(batchSize), (::DWORD *)&result, NULL) || result != uint32_t(batchSize))
				{
					readBytes += result;
					break;
				}
				dest += batchSize;
				bytesToRead -= batchSize;
				readBytes += result;
			}
			return readBytes;
		}

		virtual int64 Write(const char* src, int64 bytesToWrite) override
		{
			int64 writeBytes = 0;

			assert(IsValid() == true);
			while (bytesToWrite)
			{
				assert(bytesToWrite >= 0);
				int64 batchSize = std::min((int64)READWRITE_SIZE, bytesToWrite);
				assert(src);
				uint32_t result = 0;
				if (!WriteFile(_handle, src, uint32_t(batchSize), (::DWORD *)&result, NULL) || result != uint32_t(batchSize))
				{
					writeBytes += result;
					break;
				}

				src += batchSize;
				bytesToWrite -= batchSize;
				writeBytes += result;
			}
			return writeBytes;
		}

	private:
		HANDLE _handle;

		inline int64 FileSeek(int64 distance, uint32_t moveMethod)
		{
			LARGE_INTEGER li;
			li.QuadPart = distance;
			li.LowPart = SetFilePointer(_handle, li.LowPart, &li.HighPart, moveMethod);
			if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
			{
				li.QuadPart = -1;
			}
			return li.QuadPart;
		}

		inline bool IsValid() const
		{
			return _handle != NULL && _handle != INVALID_HANDLE_VALUE;
		}
	};

	Path NormalizeFileName(const Path & fileName)
	{
		return fileName;
	}

	IFile * PlatformFile::OpenRead(const Path & path)
	{
		uint32_t Access = GENERIC_READ;
		uint32_t WinFlags = FILE_SHARE_READ;
		uint32_t Create = OPEN_EXISTING;

		tchar pathName[MAX_PATH + 1] = {};
		Path::Fill(path, pathName, MAX_PATH + 1);

		HANDLE Handle = CreateFileW(pathName, Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL);
		if (Handle != INVALID_HANDLE_VALUE)
			return new FileHandleWindows(Handle);
		return nullptr;
	}

	IFile * PlatformFile::OpenWrite(const Path & path, bool append, bool allowRead)
	{
		uint32_t Access = GENERIC_WRITE;
		uint32_t WinFlags = allowRead ? FILE_SHARE_READ : 0;
		uint32_t Create = append ? OPEN_ALWAYS : CREATE_ALWAYS;

		tchar pathName[MAX_PATH + 1] = {};
		Path::Fill(path, pathName, MAX_PATH + 1);

		HANDLE Handle = CreateFileW(pathName, Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL);
		if (Handle != INVALID_HANDLE_VALUE)
			return new FileHandleWindows(Handle);
		return nullptr;
	}

	Path PlatformFile::GetTemporaryFolderPath()
	{
		wchar_t lpTempPathBuffer[MAX_PATH];
		DWORD res = GetTempPathW(MAX_PATH, lpTempPathBuffer);
		return Path::ConvertToPath(lpTempPathBuffer, res);
	}
}
