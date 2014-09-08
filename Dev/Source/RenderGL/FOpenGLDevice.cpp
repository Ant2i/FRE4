#include "FOpenGLDevice.h"
#include "FOpenGLRenderTarget.h"
#include "FOpenGLDebug.h"

//#include "GLBase.h"
#include "FPlatform.h"
#include "FreAssert.h"
#include "FreGPUTimer.h"

namespace FRE
{
	const GLVersion GLDevice::NeededGLVersion(4, 1);

	//GLVersion GetCapabilityGLVersion()
	//{
	//	if (GLEW_VERSION_4_4) return GLVersion(4, 4);
	//	if (GLEW_VERSION_4_3) return GLVersion(4, 3);
	//	if (GLEW_VERSION_4_2) return GLVersion(4, 2);
	//	if (GLEW_VERSION_4_1) return GLVersion(4, 1);
	//	if (GLEW_VERSION_4_0) return GLVersion(4, 0);
	//	if (GLEW_VERSION_3_3) return GLVersion(3, 3);
	//	if (GLEW_VERSION_3_2) return GLVersion(3, 2);
	//	if (GLEW_VERSION_3_1) return GLVersion(3, 1);
	//	if (GLEW_VERSION_3_0) return GLVersion(3, 0);
	//	if (GLEW_VERSION_2_1) return GLVersion(2, 1);
	//	if (GLEW_VERSION_2_0) return GLVersion(2, 0);
	//	if (GLEW_VERSION_1_5) return GLVersion(1, 5);
	//	if (GLEW_VERSION_1_4) return GLVersion(1, 4);
	//	if (GLEW_VERSION_1_3) return GLVersion(1, 3);
	//	return GLVersion(0, 0);
	//}

	void GLDebugCB(const char * msg)
	{
		_FRE_OutputDebugString(msg);
		FRE_ASSERT(0 == "OpenGL Error.");
	}

	//bool InitGlew()
	//{
	//	glewExperimental = GL_TRUE;
	//	return glewInit() == GLEW_OK;
	//}

	bool GLDevice::Init()
	{
		//const char * ext = nullptr;
		//OpenGLAPI::ProcessExtensions(ext);

		bool ret = false;
		const bool isPlatformInit = GLPlatformInit(NeededGLVersion, IsDebug());
		if (isPlatformInit)
		{
			ret = true;
			//h_GLContext tempContext = OpenGLAPI::ContextCreate();
			//GLPlatformContextMakeCurrent(tempContext);
			//ret = InitGlew();

			//const GLVersion supportGlVersion = GetCapabilityGLVersion();

			//GLPlatformDestroyEntity(tempContext);
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
