#include "FreDeviceManager.h"
#include "FreDeviceInterfaces.h"
#include "FreLibrary.h"
#include "FreReleaser.h"

#include <map>

namespace FRE
{
	class DeviceHolder : public IDeviceRegister
	{
    public:
        DeviceHolder() :
            _device(nullptr)
        {
            
        }

		virtual void Register(IRenderDevice * device) override
		{
			_device.reset(device, Releaser<FRE::IRenderDevice>());
		}
        
        IRenderDevice * GetDevice() const
        {
            return _device.get();
        }
        
    private:
		std::shared_ptr<IRenderDevice> _device;
	};

    typedef std::pair<std::unique_ptr<Library>, DeviceHolder> LibraryDevicePair;
    
	class DeviceManager::Pimpl
	{
	public:
		IRenderDevice * LoadDevice(const sPath & path)
		{
			std::unique_ptr<Library> library(Library::Load(path));
			if (library)
			{
                DeviceHolder holder;
				library->GetFunction<void(IDeviceRegister &, const sPath &)>("LoadDevice")(holder, path);
                
                IRenderDevice * device = holder.GetDevice();
                if (device)
                {
                    _devices[device->GetName()] = std::make_pair(std::move(library), holder);
                    return device;
                }
            }
			return nullptr;
		}

		void UnloadDevice(const std::string & name)
		{
            _devices.erase(name);
		}

        IRenderDevice * GetDeviceByName(const std::string & name) const
        {
            auto findIt = _devices.find(name);
            if (findIt != _devices.end())
            {
                const LibraryDevicePair & pair = findIt->second;
                return pair.second.GetDevice();
            }
            return nullptr;
        }
        
	private:
		typedef std::map<std::string, LibraryDevicePair> LibraryMap;
		LibraryMap _devices;
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
		return _pimpl->GetDeviceByName(name);
	}
}