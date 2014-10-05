#pragma once

#include "FreBase.h"
#include "FreTypes.h"
#include "FreDeviceManager.h"

namespace FRE
{
	class IRenderDevice;

	class RE_API Engine
	{
	public:
		struct CreateParams
		{
			sPath renderDeviceName;
		};

	public:
		static Engine * Create(const CreateParams & params);
		static void Destroy();
		static Engine * GetInstance();
		static IRenderDevice & GetActiveRenderDevice();

		IRenderDevice * ActiveRenderDevice() const;

	private:
		Engine();
		~Engine();

		DeviceManager _deviceManager;
		IRenderDevice * _activeRenderDevice;

		friend class REDeleter;
	};
}