#include "FreEngine.h"

#include <memory>

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
	EnginePtr sEngine;

	Engine * Engine::Create(const CreateParams & params)
	{
		if (!sEngine)
		{
			EnginePtr engine(new Engine);
			IRenderDevice * device = engine->_deviceManager.LoadDevice(params.renderDeviceName);
			if (device)
			{
				engine->_activeRenderDevice = device;
				sEngine.swap(engine);
			}
		}

		return sEngine.get();
	}

	void Engine::Destroy()
	{
		sEngine = nullptr;
	}

	Engine * Engine::GetInstance()
	{
		return sEngine.get();
	}

	IRenderDevice * Engine::GetActiveRenderDevice()
	{
		if (GetInstance())
		{
			return GetInstance()->ActiveRenderDevice();
		}
		return nullptr;
	}

	//----------------------------------------------------------------------------

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{

	}

	IRenderDevice * Engine::ActiveRenderDevice() const
	{
		return _activeRenderDevice;
	}
}