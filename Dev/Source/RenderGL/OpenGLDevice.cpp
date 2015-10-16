#include "OpenGLDevice.h"
#include "OpenGLRenderSurface.h"
#include "OpenGLDebug.h"
#include "OpenGLResources.h"
#include "OpenGLResourceManager.h"

#include "FPlatform.h"
#include "FAssert.h"
//#include "FreTypes.h"

#ifdef _DEBUG
#define DEBUG_OPENGL_CONTEXT
#endif

inline bool IsOpenGLDebug()
{
#ifdef DEBUG_OPENGL_CONTEXT
	return true;
#endif
	return false;
}

namespace FRE
{
	void InitOpenGLCapabilities()
	{
		GLPlatformContextP initContext = GLPlatformContextCreate(GLDevice::GetDefaultPixelFormat());
		GLPlatformContextMakeCurrent(initContext);

		PlatformInitOpenGL();

		GLPlatformContextDestroy(initContext);
	}

	GLPixelFormatH GLDevice::GetDefaultPixelFormat()
	{
		static GLPixelFormatH defaultPixelFormat = 0;
		if (!defaultPixelFormat)
		{
			PixelFormatDesc pixelFormatDesc;
			pixelFormatDesc.Stereo = false;
			defaultPixelFormat = FindPixelFormat(pixelFormatDesc);
		}
		return defaultPixelFormat;
	}

	bool GLDevice::Init()
	{
		bool result = false;
		const bool isPlatformInit = GLPlatformInit(4, 1, IsOpenGLDebug());
		if (isPlatformInit)
		{
			InitOpenGLCapabilities();
			result = true;
		}
		return result;
	}

	GLDevice::GLDevice() :
		_sharedContext(GetDefaultPixelFormat()),
		_renderContext(GetDefaultPixelFormat(), _sharedContext)
	{
		GLResourceManager::GetInstance().Register(this);
		_sharedContext.MakeCurrent();
		
		if (IsOpenGLDebug())
			InitOpenGLContextForDebug();
	}

	GLDevice::~GLDevice()
	{
		GLResourceManager::GetInstance().Unregister(this);
	}

	void GLDevice::Release()
	{
		delete this;
	}

	const char * GLDevice::GetName() const
	{
		return "GLRenderDevice";
	}

	RDRenderOutputRef GLDevice::RDCreateSurfaceRenderOutput(const DarkParams & iParams) 
	{
		SurfaceDesc surfaceDesc;
		surfaceDesc.PlatformData = iParams.params[0];
		surfaceDesc.External = true;
		GLPlatformRenderSurfaceP surface = GLPlatformSurfaceCreate(GetDefaultPixelFormat(), surfaceDesc);
		if (surface)
			return new GLRenderSurface(surface);
		return nullptr;
	}

	RDViewportRef GLDevice::RDCreateViewport(RDRenderOutputP iOutput, int x, int y, unsigned width, unsigned height)
	{
		return nullptr;
	}

	RDRenderQueryRef GLDevice::RDCreateRenderQuery(ERenderQueryType iType)
	{
		return new RDRenderQuery(iType);
	}

	RDPipelineStateRef GLDevice::RDCreatePipelineState(const PipelineStateDesc & iPipeline)
	{
		return new RDPipelineState();
	}

	void GLDevice::RDBeginRenderQuery(RDRenderQueryP iQuery)
	{
	}

	void GLDevice::RDEndRenderQuery(RDRenderQueryP iQuery)
	{
	}

	bool GLDevice::RDGetRenderQueryResult(RDRenderQueryP iQuery, uint64_t & oResult, bool iWait)
	{
		return true;
	}

	void GLDevice::RDClear(bool iClearColor, const Color & iColorValue, bool iClearDepth, float iDepthValue, bool iClearStencil, uint32_t iStencilValue)
	{
		glClearColor(iColorValue.R, iColorValue.G, iColorValue.B, iColorValue.A);
		GLenum clearFlags = GL_COLOR_BUFFER_BIT;

		if (iClearDepth)
		{
			glClearDepth(iDepthValue);
			clearFlags |= GL_DEPTH_BUFFER_BIT;
		}

		if (iClearStencil)
		{
			glClearStencil(iStencilValue);
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
	}

	void GLDevice::RDBeginDrawing(RDViewportP iViewport)
	{
		if (iViewport)
		{
			//_drawSurface = static_cast<GLRenderSurface *>(iOutput);

			//GLPlatformContextH context = GetCurrentContext().GetPlatformContext();
			//if (context != _renderContext.GetPlatformContext())
			//{
			//	context = _renderContext.GetPlatformContext();
			//	_restoreContext = context;
			//}

			//_drawSurface->MakeCurrent(context);
		}
	}

	void GLDevice::RDEndDrawing(bool iPresent)
	{
		if (_drawSurface && iPresent)
			_drawSurface->Swap(GetCurrentContext().GetPlatformContext());
        
		_drawSurface = nullptr;

		if (_restoreContext)
			GLPlatformContextMakeCurrent(_restoreContext);
	}

	void GLDevice::RDDrawPrimitive(uint32_t iPrimitiveType, uint32_t iBaseVertexIndex, uint32_t iNumPrimitives, uint32_t iNumInstances)
	{

	}

	void GLDevice::RDDrawPrimitiveIndirect(uint32_t iPrimitiveType, RDVertexBufferP iDrawParams, uint32_t iDrawParamsOffset)
	{

	}

	void GLDevice::RDDrawIndexedIndirect(uint32_t iPrimitiveType, RDIndexBufferP iIndexBuffer, RDStructureBufferP iDrawParams, int32_t drawParamsIndex, uint32_t numInstances)
	{

	}

	void GLDevice::RDDrawIndexedPrimitive(uint32_t iPrimitiveType, RDIndexBufferP iIndexBuffer, int32_t baseVertexIndex, uint32_t minIndex, uint32_t numVertices, uint32_t startIndex, uint32_t numPrimitives, uint32_t numInstances)
	{

	}

	void GLDevice::RDDrawIndexedPrimitiveIndirect(uint32_t iPrimitiveType, RDIndexBufferP iIndexBuffer, RDVertexBufferP drawParams, uint32_t argumentOffset)
	{
		
	}

	GLContext & GLDevice::GetCurrentContext()
	{
		GLPlatformContextP context = GLPlatformGetCurrentContext();
		if (context == _renderContext.GetPlatformContext())
		{
			return _renderContext;
		}

		F_ASSERT(context == _sharedContext.GetPlatformContext());
		return _sharedContext;
	}

	RDVertexDeclarationRef GLDevice::RDCreateVertexDeclaration(const VertexElementDeclarationDesc * iElements, unsigned iNumElems)
	{
		return IRenderDevice::RDCreateVertexDeclaration(iElements, iNumElems);
	}

	void GLDevice::RDSetStreamSource(uint32_t streamIndex, RDVertexBufferP vertexBuffer, uint32_t stride, uint32_t offset)
	{

	}
}

//---------------------------------------------------------------------------

API_EXPORT_C void LoadDevice(FRE::IDeviceRegister & reg, const std::wstring & path)
{
	if (FRE::GLDevice::Init())
	{
		reg.Register(new FRE::GLDevice());
	}
}
