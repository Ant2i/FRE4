#pragma once

#include "FPlatform.h"
#include "RDResources.h"

#ifdef _RD_EXPORT
#define RD_EXP_F API_EXPORT
#else
#define RD_EXP_F API_IMPORT
#endif

namespace FRE
{
	RD_EXP_F RDRenderOutputRef RDCreateSurfaceRenderOutput(const DarkParams & params);
	
	RD_EXP_F RDVertexBufferRef RDCreateVertexBuffer(uint32 size, uint32 usage, void * data);
	RD_EXP_F void* RDLockBuffer(RDVertexBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RD_EXP_F void RDUnlockBuffer(RDVertexBufferRef buffer);

	RD_EXP_F RDStructureBufferRef RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data);
	RD_EXP_F void* RDLockBuffer(RDStructureBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RD_EXP_F void RDUnlockBuffer(RDStructureBufferRef buffer);

	RD_EXP_F RDIndexBufferRef RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data);
	RD_EXP_F void* RDLockBuffer(RDIndexBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RD_EXP_F void RDUnlockBuffer(RDIndexBufferRef buffer);

	RD_EXP_F RDTexture2DRef RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags);
	RD_EXP_F RDRenderQueryRef RDCreateRenderQuery(ERenderQueryType type);

	RD_EXP_F RDVertexShaderRef RDCreateVertexShader(const uint8 * source, unsigned size);
	RD_EXP_F RDPixelShaderRef RDCreatePixelShader(const uint8 * source, unsigned size);
	RD_EXP_F RDHullShaderRef RDCreateHullShader(const uint8 * source, unsigned size);
	RD_EXP_F RDDomainShaderRef RDCreateDomainShader(const uint8 * source, unsigned size);
	RD_EXP_F RDGeometryShaderRef RDCreateGeometryShader(const uint8 * source, unsigned size);

	RD_EXP_F RDBoundShaderStateRef RDCreateBoundShaderState(RDVertexDeclarationRef declaration, RDVertexShaderRef vertexShader, RDHullShaderRef hullShader, RDDomainShaderRef domainShader,RDPixelShaderRef pixelShader, RDGeometryShaderRef geometryShader);
	
	RD_EXP_F void RDBeginRenderQuery(RDRenderQueryRef query);
	RD_EXP_F void RDEndRenderQuery(RDRenderQueryRef query);
	RD_EXP_F bool RDGetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait);

	RD_EXP_F void RDClear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue);

	RD_EXP_F void RDBeginFrame();
	RD_EXP_F void RDEndFrame();

	RD_EXP_F void RDBeginDrawing(RDRenderOutputP pOutput);
	RD_EXP_F void RDEndDrawing(bool present);

	RD_EXP_F void RDDrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances);
	RD_EXP_F void RDDrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset);

	RD_EXP_F void RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances);
	
	RD_EXP_F void RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances);
	RD_EXP_F void RDDrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 drawParamsOffset);
}