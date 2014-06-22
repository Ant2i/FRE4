#include "GLDevice.h"
#include "FPlatform.h"
#include "GLRenderTarget.h"

#include "GL/glew.h"

namespace FRE
{
	GLDevice::GLDevice() :
		_frameTarget(nullptr)
	{
		_context = GetCurrentPlatform().CreateContext();
	}

	//void GLDevice::Init()
	//{
		
	//}

	IRenderTarget * GLDevice::CreateSurfaceRenderTarget(const DarkParams & params) 
	{
		h_GLRenderTarget surface = GetCurrentPlatform().CreateSurfaceTarget(_context, params);
		if (surface)
			return new GLRenderTarget(surface);
		return nullptr;
	}

	char * GLDevice::GetName() const
	{
		return "GLRenderDevice";
	}

	void GLDevice::BeginFrame(IRenderTarget * target)
	{
		_frameTarget = static_cast<GLRenderTarget *>(target);
		if (_frameTarget)
			_frameTarget->MakeCurrent(_context);
		
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLDevice::EndFrame()
	{
		if (_frameTarget)
			_frameTarget->Swap(_context);
		
		GetCurrentPlatform().MakeCurrentContext(0);
		_frameTarget = nullptr;
	}
}

API_EXPORT void LoadDevice(FRE::IDeviceRegister & regDevice, const FRE::sPath & path)
{
	regDevice.Register(new FRE::GLDevice());
}
