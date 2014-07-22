#include "FreGLDevice.h"
#include "GLBase.h"
#include "FPlatform.h"
#include "FreGLRenderTarget.h"
#include "FreGPUTimer.h"
#include "FreGLDebug.h"

namespace FRE
{
	const GLVersion GLDevice::NeededGLVersion(4, 1);

	GLVersion GetCapabilityGLVersion()
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

	void GLDebugCB(const char * msg)
	{
		_FRE_OutputDebugString(msg);
		FRE_ASSERT(0 == "OpenGL Error.");
	}

	bool InitGlew()
	{
		glewExperimental = GL_TRUE;
		return glewInit() == GLEW_OK;
	}

	bool GLDevice::Init()
	{
		bool ret = false;
		const bool isPlatformInit = GLPlatformInit(NeededGLVersion, IsDebug());
		if (isPlatformInit)
		{
			h_GLContext tempContext = GLPlatformCreateContext();
			GLPlatformMakeCurrentContext(tempContext);
			ret = InitGlew();

			const GLVersion supportGlVersion = GetCapabilityGLVersion();

			GLPlatformDestroyEntity(tempContext);
		}
		return ret;
	}

	GLDevice::GLDevice() :
		_frameTarget(nullptr)
	{
		_context = GLPlatformCreateContext();
		GLPlatformMakeCurrentContext(_context);

#ifdef _DEBUG
		GLDebug::SetCallBack(GLDebugCB);
		GLDebug::Enable();
#endif
	}

	GLDevice::~GLDevice()
	{
		GLPlatformDestroyEntity(_context);
	}

	void GLDevice::Release()
	{
		delete this;
	}

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
	
		GPU_PROFILE_START(gpu_FrameTimer);

		glClearColor(1.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GLDevice::EndFrame()
	{
        //glFlush();
        
		if (_frameTarget)
			_frameTarget->Swap(_context);

		GPU_PROFILE_STOP(gpu_FrameTimer);
		
		GLPlatformMakeCurrentContext(0);
		_frameTarget = nullptr;
	}
}

//---------------------------------------------------------------------------

API_EXPORT void LoadDevice(FRE::IDeviceRegister & reg, const FRE::sPath & path)
{
	if (FRE::GLDevice::Init())
	{
		reg.Register(new FRE::GLDevice());
	}
}
