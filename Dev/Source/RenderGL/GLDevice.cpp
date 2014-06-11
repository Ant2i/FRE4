#include "GLDevice.h"
#include "FPlatform.h"

namespace FRE
{
	ISurfaceTarget * GLDevice::CreateSurfaceRenderTarget(const TargetParams & param)
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
