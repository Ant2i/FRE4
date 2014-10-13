#include "FOpenGLDevice.h"
#include "FOpenGLRenderTarget.h"
#include "FOpenGLDebug.h"

#include "FPlatform.h"
#include "FreAssert.h"

namespace FRE
{
	const GLVersion NeededGLVersion(4, 1);

	void GLDebugCB(const char * msg)
	{
		_FRE_OutputDebugString(msg);
		FRE_ASSERT(0 == "OpenGL Error.");
	}

	void InitOpenGLCapabilities()
	{
		GLPlatformContextP initContext = GLPlatformContextCreate();
		GLPlatformContextMakeCurrent(initContext);

		TOpenGLAPI::Init(TOpenGLAPI::GetExtensionString());
		auto capailityOpenGL = TOpenGLAPI::GetCapability();

		GLPlatformContextDestroy(initContext);
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
		_currentFrameTarget(nullptr)
	{
		_context = GLPlatformContextCreate();
		GLPlatformContextMakeCurrent(_context);

#ifdef _DEBUG
		//GLPlatformDebugSetCallBack(GLDebugCB);
		//GLPlatformDebugEnable();
#endif
	}

	GLDevice::~GLDevice()
	{
		GLPlatformContextDestroy(_context);
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
		GLPlatformRenderSurfaceP surface = GLPlatformSurfaceCreate(_context, params.params[0]);
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
		GLPlatformContextMakeCurrent(0);
	}

	void GLDevice::BeginDrawing(RDRenderTargetP pTarget)
	{
		_currentFrameTarget = static_cast<GLRenderTarget *>(pTarget);
		if (_currentFrameTarget)
			_currentFrameTarget->MakeCurrent(_context);
	}

	void GLDevice::EndDrawing(bool present)
	{
		if (_currentFrameTarget && present)
			_currentFrameTarget->Swap(_context);
		_currentFrameTarget = nullptr;
	}

	void GLDevice::DrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances)
	{

	}

	void GLDevice::DrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset)
	{

	}

	void GLDevice::DrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances)
	{

	}

	void GLDevice::DrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances)
	{

	}

	void GLDevice::DrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 argumentOffset)
	{
		
	}
}

//---------------------------------------------------------------------------

API_EXPORT_C void LoadDevice(FRE::IDeviceRegister & reg, const FRE::sPath & path)
{
	if (FRE::GLDevice::Init())
	{
		reg.Register(new FRE::GLDevice());
	}
}
