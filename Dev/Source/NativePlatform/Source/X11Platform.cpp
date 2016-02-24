#include "NativePlatform.h"
#include "FPlatform.h"

#ifdef PLATFORM_LINUX

#include <dlfcn.h>
#include "utf8.h"
#include <cassert>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <linux/limits.h>
#include <cstring>
#include <fcntl.h>
#include <stdio.h>

#include "Utils.h"
#include <iostream>

namespace NativePlatform
{
	class FileHandleLinux : public IFile
	{
		enum {READWRITE_SIZE = 1024 * 1024};
		int32_t _handle;

		inline bool IsValid()
		{
			return _handle != -1;
		}

	public:
		FileHandleLinux(int32_t handle = -1)
			: _handle(handle)
		{
		}

		virtual void Release() override
		{
			delete this;
		}

		virtual ~FileHandleLinux()
		{
			close(_handle);
			_handle = -1;
		}

		virtual int64_t Pos() override
		{
			assert(IsValid());
			return lseek(_handle, 0, SEEK_CUR);
		}

		virtual bool Seek(int64_t pos) override
		{
			assert(IsValid());
			assert(pos >= 0);
			return lseek(_handle, pos, SEEK_SET) != -1;
		}

		virtual int64_t Read(char* dest, int64_t bytesToRead) override
		{
			int64_t readBytes = 0;

			assert(IsValid());
			while (bytesToRead)
			{
				assert(bytesToRead >= 0);
				int64_t batchSize = std::min((int64_t)READWRITE_SIZE, bytesToRead);
				assert(dest);
				ssize_t rb = read(_handle, dest, batchSize);
				if (rb != batchSize)
				{
					readBytes += rb;
					break;
				}
				dest += batchSize;
				bytesToRead -= batchSize;
				readBytes += rb;
			}
			return readBytes;
		}

		virtual int64_t Write(const char* src, int64_t bytesToWrite) override
		{
			int64_t writeBytes = 0;

			assert(IsValid());
			while (bytesToWrite)
			{
				assert(bytesToWrite >= 0);
				int64_t batchSize = std::min((int64_t)READWRITE_SIZE, bytesToWrite);
				assert(src);
				ssize_t wb = write(_handle, src, batchSize);
				if (wb != batchSize)
				{
					writeBytes += wb;
					break;
				}
				src += batchSize;
				bytesToWrite -= batchSize;
				writeBytes += wb;
			}
			return writeBytes;
		}
	};

	//-----------------------------------------------------------------------------

	std::string ToUtf8(const std::wstring & wstr)
	{
		std::string res;
		utf8::utf16to8(wstr.begin(), wstr.end(), std::back_inserter(res));
		return res;
	}

	std::string ToUtf8(const wchar_t * str)
	{
		return ToUtf8(std::wstring(str));
	}

	std::wstring FromUtf8(const std::string & str)
	{
		std::wstring res;
		utf8::utf8to16(str.begin(), str.end(), std::back_inserter(res));
		return res;
	}

	//-----------------------------------------------------------------------------

	Path GetLibraryName(const Path & path)
	{
		Path name;
		Path dir;
		Utils::GetFileName(path, name, dir);
		return Utils::AppendPath(dir, L"lib" + name + L".so");
	}

	PlatformLibrary::Handle PlatformLibrary::LoadLibrary(const Path & path)
	{
		std::string pathUtf8 = ToUtf8(GetLibraryName(path));
		void * ret = dlopen(pathUtf8.c_str(), 2);

		if (!ret)
		{
			char * err = dlerror();
			std::cerr << "Load library: " << pathUtf8 << " : " << err;
		}

		return ret;
	}
	void PlatformLibrary::FreeLibrary(Handle handle)
	{
		if (handle)
			dlclose(handle);
	}

	void* PlatformLibrary::ExportProc(Handle handle, const std::string & procName)
	{
		return dlsym(handle, procName.c_str());
	}

	const wchar_t * PlatformLibrary::GetLibraryExtension()
	{
		return L".so";
	}

	const wchar_t * PlatformLibrary::BaseDirectory()
	{
		char buffer[PATH_MAX];
		memset(buffer, 0, sizeof(buffer));
		ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
		
		//std::string ansiExePath(buffer);
		std::wstring uExePath(FromUtf8(buffer));
		//std::wstring uExePath(ansiExePath.begin(), ansiExePath.end());
		std::wstring uDirExe = uExePath.substr(0, uExePath.find_last_of(L"\\/"));

		static wchar_t baseDir[PATH_MAX];
		auto len = uDirExe.copy(baseDir, PATH_MAX, 0);
		baseDir[len] = 0;

		return baseDir;
	}

	const wchar_t * PlatformLibrary::ExecutableName(bool bRemoveExtension)
	{
		return nullptr;
	}

	//-----------------------------------------------------------------------------

	Path NormalizeFileName(const Path & fileName)
	{
		return fileName;
	}

	IFile * PlatformFile::OpenRead(const Path & fileName)
	{
		int32_t handle = open(ToUtf8(NormalizeFileName(fileName)).c_str(), O_RDONLY);
		if (handle != -1)
			return new FileHandleLinux(handle);
		return nullptr;
	}

	IFile * PlatformFile::OpenWrite(const Path & fileName, bool append, bool allowRead)
	{
		int Flags = O_CREAT;
		Flags |= append ? O_APPEND : O_TRUNC;
		Flags |= allowRead ? O_RDWR : O_WRONLY;

		int32_t handle = open(ToUtf8(NormalizeFileName(fileName)).c_str(), Flags, S_IRUSR | S_IWUSR);
		if (handle != -1)
			return new FileHandleLinux(handle);
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

    Path PlatformFile::GetTemporaryFolderPath()
    {
        Path wchPath;
        const char * envPath = std::getenv("TMPDIR");
        if (envPath)
        {
			Utils::CStringToPath(envPath, wchPath);
        }
        else if (P_tmpdir)
        {
			Utils::CStringToPath(P_tmpdir, wchPath);
        }
        else
        {
            wchPath = L"/tmp";
        }

        return wchPath;
    }
}

#endif
