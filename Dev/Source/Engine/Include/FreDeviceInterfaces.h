#pragma once

#include "FreDeviceTypes.h"
#include "FreMath.h"
#include <string>

namespace FRE
{
	class IRenderDevice
	{
	public:
		virtual void Destroy() = 0;
		virtual char * GetName() const = 0;

		virtual RenderTargetH CreateSurfaceRenderTarget(const DarkParams & params) { return nullptr; }
		virtual VertexBufferH CreateVertexBuffer(uint32 size, void * data, uint32 usage) { return nullptr; }

		virtual void Clear(bool clearColor, const Math::Vector4f_t & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue){}
		
		virtual void BeginFrame(RenderTargetH target) = 0;
		virtual void EndFrame() = 0;
	};

	class IDeviceRegister
	{
	public:
		virtual void Register(IRenderDevice * device) = 0;
	};
}