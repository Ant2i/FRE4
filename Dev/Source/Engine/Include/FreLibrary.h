#pragma once
#include "FreTypes.h"
#include "FLibrary.h"

#include <memory>
#include <functional>

namespace FRE
{
	struct LibraryUploader
	{
		void operator()(void * libHandle) const { if (libHandle) _FreeLibrary(libHandle); }
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
			void * handle = _LoadLibrary((const strPath &)libraryPath);
			if (handle)
				return new Library(handle, upload);
			return nullptr;
		}

		template<typename Fn>
		std::function<Fn> GetFunction(const std::string & name)
		{
			return std::function<Fn>(reinterpret_cast<Fn *>(_GetLibraryFunction(_libHandle.get(), name)));
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