#include "OpenGLDevice.h"
#include "OpenGLRenderSurface.h"
#include "OpenGLDebug.h"
#include "OpenGLResources.h"
#include "OpenGLResourceManager.h"

#include "FPlatform.h"
#include "FAssert.h"
#include "FreTypes.h"

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
		GLPlatformContextP initContext = GLPlatformContextCreate();
		GLPlatformContextMakeCurrent(initContext);

		PlatformInitOpenGL();

		GLPlatformContextDestroy(initContext);
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
		_renderContext(_sharedContext)
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

	RDRenderOutputRef GLDevice::RDCreateSurfaceRenderOutput(const DarkParams & params) 
	{
		GLPlatformRenderSurfaceP surface = GLPlatformSurfaceCreate(params.params[0]);
		if (surface)
			return new GLRenderSurface(surface);
		return nullptr;
	}

	RDRenderQueryRef GLDevice::RDCreateRenderQuery(ERenderQueryType type)
	{
		return new RDRenderQuery(type);
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

	void GLDevice::RDClear(bool clearColor, const Color & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue)
	{
		glClearColor(colorValue.R, colorValue.G, colorValue.B, colorValue.A);
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
	}

	void GLDevice::RDBeginDrawing(RDRenderOutputP pOutput)
	{
		if (pOutput)
		{
			_drawSurface = static_cast<GLRenderSurface *>(pOutput);

			GLPlatformContextP context = GetCurrentContext().GetPlatformContext();
			if (context != _renderContext.GetPlatformContext())
			{
				context = _renderContext.GetPlatformContext();
				_restoreContext = context;
			}

			_drawSurface->MakeCurrent(context);
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

		F_ASSERT(context == _sharedContext.GetPlatformContext());
		return _sharedContext;
	}

	RDVertexDeclarationRef GLDevice::RDCreateVertexDeclaration(const VertexDeclarationElementList & elements)
	{
		return IRenderDevice::RDCreateVertexDeclaration(elements);
	}

	void GLDevice::RDSetStreamSource(uint32 streamIndex, RDVertexBufferRef vertexBuffer, uint32 stride, uint32 offset)
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
