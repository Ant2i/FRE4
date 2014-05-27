#include "FPlatform.h"
#include "DeviceInterfaces.h"

namespace FRE
{
	class GLDevice : public IRenderDevice
	{
	public:
		virtual std::string GetName() override
		{
			return "GLRenderDevice";
		}
	};
}

API_EXPORT void LoadDevice(FRE::IDeviceRegister & regDevice, const FRE::sPath & path)
{
	regDevice.Register(new FRE::GLDevice());
}
