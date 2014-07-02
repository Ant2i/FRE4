#include "FreGLDevice.h"
#include "FPlatform.h"
#include "FreGLRenderTarget.h"

#include "GL/glew.h"

namespace FRE
{
	GLDevice::GLDevice() :
		_frameTarget(nullptr)
	{
		_context = PlatformCreateContext();
		PlatformMakeCurrentContext(_context);

		GLenum glewErr = glewInit();
		bool b = glewErr == GLEW_OK;
	}

	GLDevice::~GLDevice()
	{

	}

	void GLDevice::Release()
	{
		delete this;
	}

	//void GLDevice::Init()
	//{
		
	//}

	IRenderTarget * GLDevice::CreateSurfaceRenderTarget(const DarkParams & params) 
	{
		h_GLRenderTarget surface = PlatformCreateSurfaceTarget(_context, params.params[0]);
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
		
		glClearColor(1.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLDevice::EndFrame()
	{
		if (_frameTarget)
			_frameTarget->Swap(_context);
		
		PlatformMakeCurrentContext(0);
		_frameTarget = nullptr;
	}
}

API_EXPORT void LoadDevice(FRE::IDeviceRegister & regDevice, const FRE::sPath & path)
{
	if (FRE::PlatformInit())
	{
		regDevice.Register(new FRE::GLDevice());
	}
}
