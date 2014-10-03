#include "FOpenGLDevice.h"
#include "FOpenGLRenderTarget.h"
#include "FOpenGLDebug.h"

#include "FPlatform.h"
#include "FreAssert.h"
#include "FreGPUTimer.h"

#define DEF_RENDER_API(Type, Name, ParameterTypesAndNames, ParameterNames, ReturnStatement, NullImplementation) Type Name ParameterTypesAndNames { NullImplementation; }

namespace FRE
{
	DEF_RENDER_INTEFACE(DEF_RENDER_API);

	const GLVersion NeededGLVersion(4, 1);

	void GLDebugCB(const char * msg)
	{
		_FRE_OutputDebugString(msg);
		FRE_ASSERT(0 == "OpenGL Error.");
	}

	void InitOpenGLCapabilities()
	{
		HGLContext initContext = GLContextCreate();
		GLContextMakeCurrent(initContext);

		TOpenGLAPI::Init(TOpenGLAPI::GetExtensionString());
		auto capailityOpenGL = TOpenGLAPI::GetCapability();

		GLContextDestroy(initContext);
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

	RDRenderTargetRef GLDevice::CreateSurfaceRenderTarget(const DarkParams & params) 
	{
		HGLRenderSurface surface = GLSurfaceCreate(_context, params.params[0]);
		if (surface)
			return new GLRenderTarget(surface);
		return nullptr;
	}

	RDRenderQueryRef GLDevice::CreateRenderQuery(RendetQuetyType type)
	{
		return new RDRenderQuery(type);
	}

	void GLDevice::BeginRenderQuery(RDRenderQueryRef query)
	{
	}

	void GLDevice::EndRenderQuery(RDRenderQueryRef query)
	{
	}

	bool GLDevice::GetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait)
	{
		return true;
	}

	void GLDevice::Clear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue)
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

	void GLDevice::BeginFrame()
	{
		//GPU_PROFILE_START(gpu_FrameTimer);
	}

	void GLDevice::EndFrame()
	{
		//GPU_PROFILE_STOP(gpu_FrameTimer);
		GLContextMakeCurrent(0);
	}

	void GLDevice::BeginDrawing(RDRenderTargetH hTarget)
	{
		_frameTarget = static_cast<GLRenderTarget *>(hTarget);
		if (_frameTarget)
			_frameTarget->MakeCurrent(_context);
	}

	void GLDevice::EndDrawing(bool present)
	{
		if (_frameTarget && present)
			_frameTarget->Swap(_context);
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
