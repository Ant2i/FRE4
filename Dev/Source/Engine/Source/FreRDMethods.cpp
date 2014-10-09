#include "FreRDMethods.h"
#include "FreRDInterfaces.h"

extern FRE::IRenderDevice * GlobalRD;

namespace FRE
{
	RDRenderTargetRef RDCreateSurfaceRenderTarget(const DarkParams & params)
	{
		return GlobalRD->CreateSurfaceRenderTarget(params);
	}

	RDVertexBufferRef RDCreateVertexBuffer(uint32 size, uint32 usage, void * data)
	{
		return GlobalRD->CreateVertexBuffer(size, usage, data);
	}

	RDIndexBufferRef RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data)
	{
		return GlobalRD->CreateIndexBuffer(size, usage, stride, data);
	}

	RDStructureBufferRef RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data)
	{
		return GlobalRD->CreateStructureBuffer(size, usage, stride, data);
	}

	RDTexture2DRef RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags)
	{
		return GlobalRD->CreateTexture2D(sizeX, sizeY, format, numMips, numSamples, flags);
	}

	RDRenderQueryRef RDCreateRenderQuery(RendetQuetyType type)
	{
		return GlobalRD->CreateRenderQuery(type);
	}

	void RDBeginRenderQuery(RDRenderQueryRef query)
	{
		return GlobalRD->BeginRenderQuery(query);
	}

	void RDEndRenderQuery(RDRenderQueryRef query)
	{
		return GlobalRD->EndRenderQuery(query);
	}

	bool RDGetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait)
	{
		return GlobalRD->GetRenderQueryResult(query, result, wait);
	}

	void RDClear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue)
	{
		GlobalRD->Clear(clearColor, colorValue, clearDepth, depthValue, clearStencil, stencilValue);
	}

	void RDBeginFrame()
	{
		GlobalRD->BeginFrame();
	}

	void RDEndFrame()
	{
		GlobalRD->EndFrame();
	}

	void RDBeginDrawing(RDRenderTargetP pTarget)
	{
		GlobalRD->BeginDrawing(pTarget);
	}

	void RDEndDrawing(bool present)
	{
		GlobalRD->EndDrawing(present);
	}

	void RDDrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances)
	{
		GlobalRD->DrawPrimitive(primitiveType, baseVertexIndex, numPrimitives, numInstances);
	}

	void RDDrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset)
	{
		GlobalRD->DrawPrimitiveIndirect(primitiveType, drawParams, drawParamsOffset);
	}

	void RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances)
	{
		GlobalRD->DrawIndexedIndirect(indexBuffer, primitiveType, drawParams, drawParamsIndex, numInstances);
	}

	void RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances)
	{
		GlobalRD->DrawIndexedPrimitive(indexBuffer, primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, numPrimitives, numInstances);
	}

	void RDDrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 drawParamsOffset)
	{
		GlobalRD->DrawIndexedPrimitiveIndirect(primitiveType, indexBuffer, drawParams, drawParamsOffset);
	}
}