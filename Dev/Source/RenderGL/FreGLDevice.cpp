#include "FreGLDevice.h"
#include "FPlatform.h"
#include "FreGLRenderTarget.h"
#include "FreGPUTimer.h"

#include "GL/glew.h"

namespace FRE
{
	GLVersion GetSupportGLVersion()
	{
		if (GLEW_VERSION_4_4) return GLVersion(4, 4);
		if (GLEW_VERSION_4_3) return GLVersion(4, 3);
		if (GLEW_VERSION_4_2) return GLVersion(4, 2);
		if (GLEW_VERSION_4_1) return GLVersion(4, 1);
		if (GLEW_VERSION_4_0) return GLVersion(4, 0);
		if (GLEW_VERSION_3_3) return GLVersion(3, 3);
		if (GLEW_VERSION_3_2) return GLVersion(3, 2);
		if (GLEW_VERSION_3_1) return GLVersion(3, 1);
		if (GLEW_VERSION_3_0) return GLVersion(3, 0);
		if (GLEW_VERSION_2_1) return GLVersion(2, 1);
		if (GLEW_VERSION_2_0) return GLVersion(2, 0);
		if (GLEW_VERSION_1_5) return GLVersion(1, 5);
		if (GLEW_VERSION_1_4) return GLVersion(1, 4);
		if (GLEW_VERSION_1_3) return GLVersion(1, 3);
		return GLVersion(0, 0);
	}

	GLDevice::GLDevice() :
		_frameTarget(nullptr)
	{
		_context = GLPlatformCreateContext();
		GLPlatformMakeCurrentContext(_context);


		GetSupportGLVersion();
	}

	bool GLDevice::Init()
	{
		bool res = false;

		if (GLPlatformInit(GLVersion(4, 3)))
		{
			h_GLContext temp = GLPlatformCreateContext();
			GLPlatformMakeCurrentContext(temp);
			res = glewInit() == GLEW_OK;
			GLPlatformDestroyEntity(temp);
		}
		return res;
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
		h_GLRenderTarget surface = GLPlatformCreateSurfaceTarget(_context, params.params[0]);
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
	
		//GPU_PROFILE_START(gpu_FrameTimer);

		glClearColor(1.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLDevice::EndFrame()
	{
		if (_frameTarget)
			_frameTarget->Swap(_context);

		//GPU_PROFILE_STOP(gpu_FrameTimer);
		//auto stat = FRE::Utils::FProfiler::GetTime(0, "gpu_FrameTimer");

		GLPlatformMakeCurrentContext(0);
		_frameTarget = nullptr;
	}
}

API_EXPORT void LoadDevice(FRE::IDeviceRegister & regDevice, const FRE::sPath & path)
{
	if (FRE::GLDevice::Init())
	{
		regDevice.Register(new FRE::GLDevice());
	}
}
