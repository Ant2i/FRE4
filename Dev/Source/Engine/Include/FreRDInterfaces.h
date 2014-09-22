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

		virtual RDRenderTargetRef CreateSurfaceRenderTarget(const DarkParams & params) { return new RDRenderTarget(); }
		virtual RDVertexBufferRef CreateVertexBuffer(uint32 size, void * data, uint32 usage) { return new RDVertexBuffer(); }
		virtual RDTexture2DRef CreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags/*, FResourceBulkDataInterface* BulkData,*/)
		{
			return new RDTexture2D(sizeX, sizeY, numMips, numSamples, (EPixelFormat)format, flags);
		}
		
		// Render time query.
		virtual RDRenderQueryRef CreateRenderQuery(RendetQuetyType type) { return new RDRenderQuery(type); }
		virtual void BeginRenderQuery(RDRenderQueryRef query) {}
		virtual void EndRenderQuery(RDRenderQueryRef query) {}
		virtual bool GetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait) { return true; }
        
		// Raster operations.
		virtual void Clear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue) {}
		
		// Current drawing method.
		virtual void BeginFrame() {}
		virtual void EndFrame() {}

		virtual void BeginDrawing(RDRenderTargetH hTarget) {}
		virtual void EndDrawing(bool present) {}

	protected:
		virtual ~IRenderDevice() {}
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