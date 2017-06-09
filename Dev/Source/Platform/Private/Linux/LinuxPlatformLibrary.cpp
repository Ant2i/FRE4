#include "NativePlatform.h"

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

namespace Platform
{
	//Path GetLibraryName(const Path & path)
	//{
	//	Path name;
	//	Path dir;
	//	Utils::GetFileName(path, name, dir);
	//	return Utils::AppendPath(dir, L"lib" + name + L".so");
	//}

	PlatformLibrary::Handle PlatformLibrary::LoadLibrary(const Path & path)
	{
		//std::string pathUtf8 = ToUtf8(GetLibraryName(path));
		std::string pathUtf8 = ToUtf8(path);
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

}