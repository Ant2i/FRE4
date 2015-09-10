#pragma once

#include "FPlatform.h"
#include "RDResources.h"

#ifdef _RD_EXPORT
#define RD_EXPORT_F API_EXPORT
#else
#define RD_EXPORT_F API_IMPORT
#endif

#define RD_AUTO_GEN RD_EXPORT_F

namespace FRE
{
    RD_AUTO_GEN RDRenderOutputRef RDCreateSurfaceRenderOutput(const DarkParams & params);
	
	RD_AUTO_GEN RDVertexBufferRef RDCreateVertexBuffer(uint32_t size, uint32_t usage, void * data);
	RD_AUTO_GEN void* RDLockBuffer(RDVertexBufferRef buffer, uint32_t offset, uint32_t size, ELockMode access);
	RD_AUTO_GEN void RDUnlockBuffer(RDVertexBufferRef buffer);

	RD_AUTO_GEN RDStructureBufferRef RDCreateStructureBuffer(uint32_t size, uint32_t usage, uint32_t stride, void * data);
	RD_AUTO_GEN void* RDLockBuffer(RDStructureBufferRef buffer, uint32_t offset, uint32_t size, ELockMode access);
	RD_AUTO_GEN void RDUnlockBuffer(RDStructureBufferRef buffer);

	RD_AUTO_GEN RDIndexBufferRef RDCreateIndexBuffer(uint32_t size, uint32_t usage, uint32_t stride, void * data);
	RD_AUTO_GEN void* RDLockBuffer(RDIndexBufferRef buffer, uint32_t offset, uint32_t size, ELockMode access);
	RD_AUTO_GEN void RDUnlockBuffer(RDIndexBufferRef buffer);

	RD_AUTO_GEN RDTexture2DRef RDCreateTexture2D(uint32_t sizeX, uint32_t sizeY, uint32_t format, uint32_t numMips, uint32_t flags);
    RD_AUTO_GEN RDTexture2DRef RDCreateTexture2DMS(uint32_t sizeX, uint32_t sizeY, uint32_t format, uint32_t numSamples, uint32_t flags);
    
    RD_AUTO_GEN RDRenderQueryRef RDCreateRenderQuery(ERenderQueryType type);

	RD_AUTO_GEN RDVertexShaderRef RDCreateVertexShader(const uint8_t * source, unsigned size);
	RD_AUTO_GEN RDPixelShaderRef RDCreatePixelShader(const uint8_t * source, unsigned size);
	RD_AUTO_GEN RDHullShaderRef RDCreateHullShader(const uint8_t * source, unsigned size);
	RD_AUTO_GEN RDDomainShaderRef RDCreateDomainShader(const uint8_t * source, unsigned size);
	RD_AUTO_GEN RDGeometryShaderRef RDCreateGeometryShader(const uint8_t * source, unsigned size);

	RD_AUTO_GEN RDVertexDeclarationRef RDCreateVertexDeclaration(const VertexDeclarationElementList & elements);

	RD_AUTO_GEN RDBoundShaderStateRef RDCreateBoundShaderState(RDVertexDeclarationRef declaration, RDVertexShaderRef vertexShader, RDHullShaderRef hullShader, RDDomainShaderRef domainShader, RDPixelShaderRef pixelShader, RDGeometryShaderRef geometryShader);
	
	RD_AUTO_GEN void RDBeginRenderQuery(RDRenderQueryRef query);
	RD_AUTO_GEN void RDEndRenderQuery(RDRenderQueryRef query);
	RD_AUTO_GEN bool RDGetRenderQueryResult(RDRenderQueryRef query, uint64_t & result, bool wait);

	RD_AUTO_GEN void RDClear(bool clearColor, const Color & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32_t stencilValue);

	RD_AUTO_GEN void RDBeginFrame();
	RD_AUTO_GEN void RDEndFrame();

	RD_AUTO_GEN void RDBeginDrawing(RDRenderOutputP pOutput);
	RD_AUTO_GEN void RDEndDrawing(bool present);

	RD_AUTO_GEN void RDSetStreamSource(uint32_t streamIndex, RDVertexBufferRef vertexBuffer, uint32_t stride, uint32_t offset);

	RD_AUTO_GEN void RDDrawPrimitive(uint32_t primitiveType, uint32_t baseVertexIndex, uint32_t numPrimitives, uint32_t numInstances);
	RD_AUTO_GEN void RDDrawPrimitiveIndirect(uint32_t primitiveType, RDVertexBufferRef drawParams, uint32_t drawParamsOffset);

	RD_AUTO_GEN void RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32_t primitiveType, RDStructureBufferRef drawParams, int32_t drawParamsIndex, uint32_t numInstances);
	
	RD_AUTO_GEN void RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32_t primitiveType, int32_t baseVertexIndex, uint32_t minIndex, uint32_t numVertices, uint32_t startIndex, uint32_t numPrimitives, uint32_t numInstances);
	RD_AUTO_GEN void RDDrawIndexedPrimitiveIndirect(uint32_t primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32_t drawParamsOffset);
    
    RD_EXPORT_F PixelFormatInfo RDGetPixelFormatInfo(EPixelFormat format);
}