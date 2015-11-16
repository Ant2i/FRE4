#include "NativePlatform.h"
#include "FPlatform.h"

#define NOMINMAX

#ifdef PLATFORM_WIN

#include <windows.h>
#undef LoadLibrary

#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

#include "Utils.h"

namespace NativePlatform
{
	class FileHandleWindows : public IFileHandle
	{
		enum { READWRITE_SIZE = 1024 * 1024 };

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

		virtual int64_t Pos() override
		{
			assert(IsValid() == true);
			return FileSeek(0, FILE_CURRENT);
		}

		virtual bool Seek(int64_t pos) override
		{
			assert(IsValid() == true);
			assert(pos >= 0);
			return FileSeek(pos, FILE_BEGIN) != -1;
		}

		virtual int64_t Read(char * dest, int64_t bytesToRead) override
		{
			int64_t readBytes = 0;

			assert(IsValid() == true);
			while (bytesToRead)
			{
				assert(bytesToRead >= 0);
				int64_t batchSize = std::min((int64_t)READWRITE_SIZE, bytesToRead);

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

		virtual int64_t Write(const char* src, int64_t bytesToWrite) override
		{
			int64_t writeBytes = 0;

			assert(IsValid() == true);
			while (bytesToWrite)
			{
				assert(bytesToWrite >= 0);
				int64_t batchSize = std::min((int64_t)READWRITE_SIZE, bytesToWrite);
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

		inline int64_t FileSeek(int64_t distance, uint32_t moveMethod)
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

	//-------------------------------------------------------------------------

	Path GetLibraryName(const Path & path)
	{
		return path + L".dll";
	}

	void * PlatformLibrary::LoadLibrary(const Path & fileName)
	{
		auto libraryName = GetLibraryName(fileName);
		HMODULE module = LoadLibraryW(fileName.c_str());
		return module;
	}

	void PlatformLibrary::FreeLibrary(void * handle)
	{
		if (handle)
			::FreeLibrary((HINSTANCE)handle);
	}

	void * PlatformLibrary::ExportProc(void * handle, const std::string & procName)
	{
		return GetProcAddress((HINSTANCE)handle, procName.c_str());
	}

	void PlatformLibrary::SetFindLibraryDirectory(const Path & directory)
	{
		::SetDllDirectoryW(directory.c_str());
	}

	const wchar_t * PlatformLibrary::BaseDirectory()
	{
		wchar_t exeFileName[MAX_PATH];
		memset(exeFileName, 0, sizeof(exeFileName));
		GetModuleFileNameW(NULL, exeFileName, MAX_PATH);

		std::wstring str(exeFileName);
		str = str.substr(0, str.find_last_of(L"\\/"));

		static wchar_t baseDir[MAX_PATH];
		auto len = str.copy(baseDir, MAX_PATH, 0);
		baseDir[len] = 0;
		return baseDir;
	}

	const wchar_t * PlatformLibrary::GetLibraryExtension()
	{
		return L".dll";
	}

	const wchar_t * PlatformLibrary::ExecutableName(bool bRemoveExtension)
	{
		return nullptr;
	}

	//-------------------------------------------------------------------------

	Path NormalizeFileName(const Path & fileName)
	{
		return fileName;
	}

	IFileHandle * PlatformFile::OpenRead(const Path & fileName)
	{
		uint32_t Access = GENERIC_READ;
		uint32_t WinFlags = FILE_SHARE_READ;
		uint32_t Create = OPEN_EXISTING;
		HANDLE Handle = CreateFileW(NormalizeFileName(fileName).c_str(), Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL);
		if (Handle != INVALID_HANDLE_VALUE)
			return new FileHandleWindows(Handle);
		return nullptr;
	}

	IFileHandle * PlatformFile::OpenWrite(const Path & fileName, bool append, bool allowRead)
	{
		uint32_t Access = GENERIC_WRITE;
		uint32_t WinFlags = allowRead ? FILE_SHARE_READ : 0;
		uint32_t Create = append ? OPEN_ALWAYS : CREATE_ALWAYS;
		HANDLE Handle = CreateFileW(NormalizeFileName(fileName).c_str(), Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL);
		if (Handle != INVALID_HANDLE_VALUE)
			return new FileHandleWindows(Handle);
		return nullptr;
	}

	Path PlatformFile::AppendPath(const Path & path1, const Path & path2)
	{
		return Utils::AppendPath(path1, path2);
	}

	Path PlatformFile::GetDirectory(const Path & path)
	{
		return Utils::GetDirectory(path);
	}

	Path PlatformFile::ConvertToPath(const std::string & path)
	{
		return Path(path.begin(), path.end());
	}

	Path PlatformFile::ConvertToPath(const std::wstring & path)
	{
		return path;
	}
}

#endif