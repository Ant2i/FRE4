#include "DeviceManager.h"
#include "Library.h"
#include "DeviceInterfaces.h"
#include <map>

namespace FRE
{
	struct DeviceLoader : public IDeviceRegister
	{
		virtual void Register(IRenderDevice * device) override
		{
			_device = device;
		}

		virtual void Unregister(IRenderDevice * device) override
		{
		}

		IRenderDevice * _device;
	};

	class DeviceManager::Pimpl : public IDeviceRegister
	{
	public:
		IRenderDevice * LoadDevice(const sPath & path)
		{
			std::unique_ptr<Library> deviceLibrary(Library::Load(path));
			if (deviceLibrary)
			{
				auto LoadDevice = deviceLibrary->GetFunction<void(IDeviceRegister &)>("LoadDevice");
				DeviceLoader loader;
				LoadDevice(loader);

				if (loader._device)
				{

				}

				return loader._device;
			}

			return nullptr;
		}

		void UnloadDevice(const std::string & name)
		{

		}

	private:
		virtual void Register(IRenderDevice * device) override
		{
			
		}

		virtual void Unregister(IRenderDevice * device) override
		{
			if (device)
				_devices.erase(device->GetName());
		}

		std::map<std::string, IRenderDevice *> _devices;
		IRenderDevice * _registeredDevice;
	};

	DeviceManager::DeviceManager()
	{
		_pimpl.reset(new Pimpl());
	}

	IRenderDevice * DeviceManager::LoadDevice(const sPath & devicePath)
	{
		return _pimpl->LoadDevice(devicePath);
	}

	void DeviceManager::UnloadDevice(const std::string & name)
	{
		return _pimpl->UnloadDevice(name);
	}

	IRenderDevice * DeviceManager::GetDevice(const std::string & name) const
	{
		return nullptr;
	}
}