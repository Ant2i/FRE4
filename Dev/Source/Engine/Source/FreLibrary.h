#pragma once

//#include "FLibrary.h"
#include "FreTypes.h"
#include "Platform.h"

#include <memory>
#include <functional>

namespace FRE
{
	struct LibraryUploader
	{
		void operator()(void * libHandle) const { if (libHandle) PlatformLibrary::FreeLibrary(libHandle); }
	};

	class Library
	{
	public:
		~Library()
		{
			if (!_upload)
				_libHandle.release();
		}

		static Library * Load(const sPath & libraryPath, bool upload = true)
		{
			void * handle = PlatformLibrary::LoadLibrary(libraryPath.c_str());
			if (handle)
				return new Library(handle, upload);
			return nullptr;
		}

		template<typename Fn>
		std::function<Fn> GetFunction(const std::string & name)
		{
			return std::function<Fn>(reinterpret_cast<Fn *>(PlatformLibrary::ExportProc(_libHandle.get(), name.c_str())));
		}

	private:
		Library(void * libraryHandle, bool upload) :
			_libHandle(libraryHandle),
			_upload(upload)
		{
			
		}

		std::unique_ptr<void, LibraryUploader> _libHandle;
		bool _upload;
	};
}
