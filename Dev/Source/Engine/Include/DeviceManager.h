#pragma once

#include "FBase.h"
#include "Types.h"
#include <memory>

namespace FRE
{
	class IRenderDevice;

	class RE_API DeviceManager
	{
	public:
		DeviceManager();

		IRenderDevice * LoadDevice(const sPath & devicePath);
		IRenderDevice * GetDevice(const std::string & deviceName) const;

		void UnloadDevice(const std::string & deviceName);

	private:
		class Pimpl;
		std::shared_ptr<Pimpl> _pimpl;
	};
}