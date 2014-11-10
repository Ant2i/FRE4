#include "FreEngine.h"
#include "FreNullDevice.h"
#include "FreDeviceManager.h"

#include <memory>

static FRE::NullRenderDevice NullDevice;
FRE::IRenderDevice * GlobalRD = &NullDevice;
static FRE::DeviceManager DeviceMng;

namespace FRE
{
	class REDeleter
	{
	public:
		void operator()(Engine * engine) const
		{
			delete engine;
		}
	};

	typedef std::unique_ptr<Engine, REDeleter> EnginePtr;
	static EnginePtr sEngineP;

	Engine * Engine::Create(const CreateParams & params)
	{
		if (!sEngineP)
		{
			IRenderDevice * loadDevice = DeviceMng.LoadDevice(params.renderDeviceName);
			if (loadDevice)
			{
				EnginePtr engine(new Engine);
				GlobalRD = loadDevice;
				std::swap(sEngineP, engine);
			}
		}

		return sEngineP.get();
	}

	void Engine::Destroy()
	{
		sEngineP = nullptr;
		GlobalRD = &NullDevice;
	}

	Engine * Engine::GetInstance()
	{
		return sEngineP.get();
	}

	IRenderDevice & Engine::GetActiveRenderDevice()
	{
		return *GlobalRD;
	}

	//----------------------------------------------------------------------------

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{
		DeviceMng.UploadAllDevices();
	}

	IRenderDevice & Engine::ActiveRenderDevice() const
	{
		return GetActiveRenderDevice();
	}
}