#pragma once

#include "FreRDResources.h"

namespace FRE
{
	class IRenderDevice
	{
	public:
		virtual void Release() = 0;
		virtual char * GetName() const = 0;

		virtual void SetRenderTargets(uint32 numRenderTargets, const RDRenderTarget * renderTargets, RDTextureRef depthStencilTarget) {}

		// Create methods.
		virtual RDRenderOutputRef CreateSurfaceRenderOutput(const DarkParams & params) { return new RDRenderOutput(); }
		virtual RDVertexBufferRef CreateVertexBuffer(uint32 size, uint32 usage, void * data) { return new RDVertexBuffer(size, usage); }
		virtual RDIndexBufferRef CreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data) { return new RDIndexBuffer(size, usage, stride); }
		virtual RDStructureBufferRef CreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data) { return new RDStructureBuffer(size, usage, stride); }

		virtual RDTexture2DRef CreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags)
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
		
		// Drawing methods.
		virtual void BeginFrame() {}
		virtual void EndFrame() {}

		virtual void BeginDrawing(RDRenderOutputP hRenderOutput) {}
		virtual void EndDrawing(bool present) {}

		virtual void DrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances) {}
		virtual void DrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset) {}

		virtual void DrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances) {}

		virtual void DrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances) {}
		virtual void DrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 argumentOffset) {}

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