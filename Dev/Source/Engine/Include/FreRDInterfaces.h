#pragma once

#include "FreRDResources.h"
#include "FreMath.h"
#include <string>

namespace FRE
{
	class IRenderDevice
	{
	public:
		virtual void Release() = 0;
		virtual char * GetName() const = 0;

		virtual RenderTargetRef CreateSurfaceRenderTarget(const DarkParams & params) { return nullptr; }
		virtual VertexBufferRef CreateVertexBuffer(uint32 size, void * data, uint32 usage) { return nullptr; }

		virtual void Clear(bool clearColor, const Math::Vector4f_t & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue){}
		
		virtual void BeginFrame(RenderTargetH target) = 0;
		virtual void EndFrame() = 0;

	protected:
		virtual ~IRenderDevice(){}
	};

	class IDeviceRegister
	{
	public:
		virtual void Register(IRenderDevice * device) = 0;
	};

	class IModule
	{
	public:
		virtual void Startup() = 0;
		virtual void Shutdown() = 0;
	};
}