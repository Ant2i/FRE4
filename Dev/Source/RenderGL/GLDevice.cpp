#include "GLDevice.h"
#include "FPlatform.h"

namespace FRE
{
	IRenderTarget * GLDevice::CreateSurfaceRenderTarget(const DarkParams & params) 
	{
		return nullptr;
	}

	void GLDevice::BeginFrame(IRenderTarget * target)
	{
		
	}

	void GLDevice::EndFrame()
	{

	}
}

API_EXPORT void LoadDevice(FRE::IDeviceRegister & regDevice, const FRE::sPath & path)
{
	regDevice.Register(new FRE::GLDevice());
}
