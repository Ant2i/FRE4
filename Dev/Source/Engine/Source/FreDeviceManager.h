#pragma once

#include "FreBase.h"
#include "FreTypes.h"
#include <memory>

namespace FRE
{
	class IRenderDevice;

	class DeviceManager
	{
	public:
		DeviceManager();

		IRenderDevice * LoadDevice(const sPath & devicePath);
		IRenderDevice * GetDevice(const std::string & deviceName) const;

		void UnloadDevice(const std::string & deviceName);
		void UploadAllDevices();

	private:
		class Pimpl;
		std::shared_ptr<Pimpl> _pimpl;
	};
}