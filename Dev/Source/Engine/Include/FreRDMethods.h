#pragma once

#include "FreBase.h"
#include "FreRDResources.h"

namespace FRE
{
	RE_API_F RDRenderOutputRef RDCreateSurfaceRenderOutput(const DarkParams & params);
	
	RE_API_F RDVertexBufferRef RDCreateVertexBuffer(uint32 size, uint32 usage, void * data);
	RE_API_F void* RHILockBuffer(RDVertexBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RE_API_F void RHIUnlockBuffer(RDVertexBufferRef buffer);

	RE_API_F RDStructureBufferRef RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data);
	RE_API_F void* RHILockBuffer(RDStructureBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RE_API_F void RHIUnlockBuffer(RDStructureBufferRef buffer);

	RE_API_F RDIndexBufferRef RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data);
	RE_API_F void* RHILockBuffer(RDIndexBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RE_API_F void RHIUnlockBuffer(RDIndexBufferRef buffer);

	RE_API_F RDTexture2DRef RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags);
	RE_API_F RDRenderQueryRef RDCreateRenderQuery(ERenderQueryType type);

	RE_API_F RDVertexShaderRef RDCreateVertexShader(const uint8 * source, unsigned size);
	RE_API_F RDPixelShaderRef RDCreatePixelShader(const uint8 * source, unsigned size);
	RE_API_F RDHullShaderRef RDCreateHullShader(const uint8 * source, unsigned size);
	RE_API_F RDDomainShaderRef RDCreateDomainShader(const uint8 * source, unsigned size);
	RE_API_F RDGeometryShaderRef RDCreateGeometryShader(const uint8 * source, unsigned size);

	RE_API_F RDBoundShaderStateRef RDCreateBoundShaderState(RDVertexDeclarationRef declaration, RDVertexShaderRef vertexShader, RDHullShaderRef hullShader, RDDomainShaderRef domainShader,RDPixelShaderRef pixelShader, RDGeometryShaderRef geometryShader);
	
	RE_API_F void RDBeginRenderQuery(RDRenderQueryRef query);
	RE_API_F void RDEndRenderQuery(RDRenderQueryRef query);
	RE_API_F bool RDGetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait);

	RE_API_F void RDClear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue);

	RE_API_F void RDBeginFrame();
	RE_API_F void RDEndFrame();

	RE_API_F void RDBeginDrawing(RDRenderOutputP pOutput);
	RE_API_F void RDEndDrawing(bool present);

	RE_API_F void RDDrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances);
	RE_API_F void RDDrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset);

	RE_API_F void RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances);
	
	RE_API_F void RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances);
	RE_API_F void RDDrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 drawParamsOffset);
}