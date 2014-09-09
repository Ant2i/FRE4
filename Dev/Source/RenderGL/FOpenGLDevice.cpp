#include "FOpenGLDevice.h"
#include "FOpenGLRenderTarget.h"
#include "FOpenGLDebug.h"

#include "FPlatform.h"
#include "FreAssert.h"
#include "FreGPUTimer.h"

namespace FRE
{
	const GLVersion GLDevice::NeededGLVersion(4, 1);

	void GLDebugCB(const char * msg)
	{
		_FRE_OutputDebugString(msg);
		FRE_ASSERT(0 == "OpenGL Error.");
	}

	void InitOpenGLCapabilities()
	{
		h_GLContext tempContext = GLContextCreate();
		GLContextMakeCurrent(tempContext);

		TOpenGLAPI::Init(TOpenGLAPI::GetExtensionString());

		auto capailityOpenGL = TOpenGLAPI::GetCapability();

		GLContextDestroy(tempContext);
	}

	bool GLDevice::Init()
	{
		bool ret = false;
		const bool isPlatformInit = GLPlatformInit(NeededGLVersion, IsDebug());
		if (isPlatformInit)
		{
			InitOpenGLCapabilities();
			ret = true;
		}
		return ret;
	}

	GLDevice::GLDevice() :
		_frameTarget(nullptr)
	{
		_context = GLContextCreate();
		GLContextMakeCurrent(_context);

#ifdef _DEBUG
		//GLPlatformDebugSetCallBack(GLDebugCB);
		//GLPlatformDebugEnable();
#endif
	}

	GLDevice::~GLDevice()
	{
		GLContextDestroy(_context);
	}

	void GLDevice::Release()
	{
		delete this;
	}

	char * GLDevice::GetName() const
	{
		return "GLRenderDevice";
	}

	RenderTargetRef GLDevice::CreateSurfaceRenderTarget(const DarkParams & params) 
	{
		h_GLRenderTarget surface = GLTargetCreate(_context, params.params[0]);
		if (surface)
			return new GLRenderTarget(surface);
		return nullptr;
	}

	RenderQueryRef GLDevice::CreateRenderQuery(RendetQuetyType type)
	{
		return new RD_RenderQuery(type);
	}

	void GLDevice::BeginRenderQuery(RenderQueryRef query)
	{
	}

	void GLDevice::EndRenderQuery(RenderQueryRef query)
	{
	}

	bool GLDevice::GetRenderQueryResult(RenderQueryRef query, uint64 & result, bool wait)
	{
		return true;
	}

	void GLDevice::Clear(bool clearColor, const Math::Vector4f_t & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue)
	{
		glClearColor(colorValue.x, colorValue.y, colorValue.z, colorValue.w);
		GLenum clearFlags = GL_COLOR_BUFFER_BIT;

		if (clearDepth)
		{
			glClearDepth(depthValue);
			clearFlags |= GL_DEPTH_BUFFER_BIT;
		}

		if (clearStencil)
		{
			glClearStencil(stencilValue);
			clearFlags |= GL_STENCIL_BUFFER_BIT;
		}

		glClear(clearFlags);
	}

	void GLDevice::BeginFrame(RenderTargetH target)
	{
		_frameTarget = static_cast<GLRenderTarget *>(target);
		if (_frameTarget)
			_frameTarget->MakeCurrent(_context);
	
		GPU_PROFILE_START(gpu_FrameTimer);
	}

	void GLDevice::EndFrame()
	{
		if (_frameTarget)
			_frameTarget->Swap(_context);

		GPU_PROFILE_STOP(gpu_FrameTimer);
		
		GLContextMakeCurrent(0);
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
