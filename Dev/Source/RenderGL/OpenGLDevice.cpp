#include "OpenGLDevice.h"
#include "OpenGLRenderSurface.h"
#include "OpenGLDebug.h"

#include "FPlatform.h"
#include "FreAssert.h"

#include "OpenGLResources.h"

namespace FRE
{
	void GLDebugCB(const char * msg)
	{
		_FRE_OutputDebugString(msg);
		FRE_ASSERT(0 == "OpenGL Error.");
	}

	void InitOpenGLCapabilities()
	{
		GLPlatformContextP initContext = GLPlatformContextCreate();
		GLPlatformContextMakeCurrent(initContext);

		PlatformInitOpenGL();

		GLPlatformContextDestroy(initContext);
	}

	bool GLDevice::Init()
	{
		bool ret = false;
		const bool isPlatformInit = GLPlatformInit(4, 1, IsDebug());
		if (isPlatformInit)
		{
			InitOpenGLCapabilities();
			ret = true;
		}
		return ret;
	}

	GLDevice::GLDevice() :
		_renderContext(_sharedContext)
	{
		_sharedContext.MakeCurrent();

#ifdef _DEBUG
		//GLPlatformDebugSetCallBack(GLDebugCB);
		//GLPlatformDebugEnable();
#endif
	}

	GLDevice::~GLDevice()
	{
		
	}

	void GLDevice::Release()
	{
		delete this;
	}

	char * GLDevice::GetName() const
	{
		return "GLRenderDevice";
	}

	RDRenderOutputRef GLDevice::RDCreateSurfaceRenderOutput(const DarkParams & params) 
	{
		GLPlatformRenderSurfaceP surface = GLPlatformSurfaceCreate(params.params[0]);
		if (surface)
			return new GLRenderSurface(surface);
		return nullptr;
	}

	RDTexture2DRef GLDevice::RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags)
	{
		return GLTexture2D::Create(GetCurrentContext(), sizeX, sizeY, numMips, numSamples, (EPixelFormat)format, flags);
	}

	RDRenderQueryRef GLDevice::RDCreateRenderQuery(ERenderQueryType type)
	{
		return new RDRenderQuery(type);
	}

	RDVertexShaderRef GLDevice::RDCreateVertexShader(const uint8 * source, unsigned size)
	{
		return new RDVertexShader();
	}

	RDPixelShaderRef GLDevice::RDCreatePixelShader(const uint8 * source, unsigned size)
	{
		return new RDPixelShader();
	}

	RDHullShaderRef GLDevice::RDCreateHullShader(const uint8 * source, unsigned size)
	{
		return new RDHullShader();
	}

	RDDomainShaderRef GLDevice::RDCreateDomainShader(const uint8 * source, unsigned size)
	{
		return new RDDomainShader();
	}

	RDGeometryShaderRef GLDevice::RDCreateGeometryShader(const uint8 * source, unsigned size)
	{
		return new RDGeometryShader();
	}

	RDBoundShaderStateRef GLDevice::RDCreateBoundShaderState(RDVertexDeclarationRef declaration, 
		RDVertexShaderRef vertexShader, RDHullShaderRef hullShader, RDDomainShaderRef domainShader, RDPixelShaderRef pixelShader, RDGeometryShaderRef geometryShader)
	{
		return new RDBoundShaderState();
	}

	void GLDevice::RDBeginRenderQuery(RDRenderQueryRef query)
	{
	}

	void GLDevice::RDEndRenderQuery(RDRenderQueryRef query)
	{
	}

	bool GLDevice::RDGetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait)
	{
		return true;
	}

	void GLDevice::RDClear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue)
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

	void GLDevice::RDBeginFrame()
	{
		//GPU_PROFILE_START(gpu_FrameTimer);
	}

	void GLDevice::RDEndFrame()
	{
		//GPU_PROFILE_STOP(gpu_FrameTimer);
		GLPlatformContextMakeCurrent(0);
	}

	void GLDevice::RDBeginDrawing(RDRenderOutputP pOutput)
	{
		if (pOutput)
		{
			_drawSurface = static_cast<GLRenderSurface *>(pOutput);

			GLPlatformContextP currentContext = GetCurrentContext().GetPlatformContext();
			if (currentContext != _renderContext.GetPlatformContext())
			{
				currentContext = _renderContext.GetPlatformContext();
				_restoreContext = currentContext;
			}

			_drawSurface->MakeCurrent(currentContext);
		}
	}

	void GLDevice::RDEndDrawing(bool present)
	{
		if (_drawSurface && present)
			_drawSurface->Swap(GetCurrentContext().GetPlatformContext());
		_drawSurface = nullptr;

		if (_restoreContext)
			GLPlatformContextMakeCurrent(_restoreContext);
	}

	void GLDevice::RDDrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances)
	{

	}

	void GLDevice::RDDrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset)
	{

	}

	void GLDevice::RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances)
	{

	}

	void GLDevice::RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances)
	{

	}

	void GLDevice::RDDrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 argumentOffset)
	{
		
	}

	GLContext & GLDevice::GetCurrentContext()
	{
		GLPlatformContextP context = GLPlatformGetCurrentContext();
		if (context == _renderContext.GetPlatformContext())
		{
			return _renderContext;
		}

		FRE_ASSERT(context == _sharedContext.GetPlatformContext());
		return _sharedContext;
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
