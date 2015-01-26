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
	
	RD_AUTO_GEN RDVertexBufferRef RDCreateVertexBuffer(uint32 size, uint32 usage, void * data);
	RD_AUTO_GEN void* RDLockBuffer(RDVertexBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RD_AUTO_GEN void RDUnlockBuffer(RDVertexBufferRef buffer);

	RD_AUTO_GEN RDStructureBufferRef RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data);
	RD_AUTO_GEN void* RDLockBuffer(RDStructureBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RD_AUTO_GEN void RDUnlockBuffer(RDStructureBufferRef buffer);

	RD_AUTO_GEN RDIndexBufferRef RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data);
	RD_AUTO_GEN void* RDLockBuffer(RDIndexBufferRef buffer, uint32 offset, uint32 size, ELockMode access);
	RD_AUTO_GEN void RDUnlockBuffer(RDIndexBufferRef buffer);

	RD_AUTO_GEN RDTexture2DRef RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 flags);
    RD_AUTO_GEN RDTexture2DRef RDCreateTexture2DMS(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numSamples, uint32 flags);
    
    RD_AUTO_GEN RDRenderQueryRef RDCreateRenderQuery(ERenderQueryType type);

	RD_AUTO_GEN RDVertexShaderRef RDCreateVertexShader(const uint8 * source, unsigned size);
	RD_AUTO_GEN RDPixelShaderRef RDCreatePixelShader(const uint8 * source, unsigned size);
	RD_AUTO_GEN RDHullShaderRef RDCreateHullShader(const uint8 * source, unsigned size);
	RD_AUTO_GEN RDDomainShaderRef RDCreateDomainShader(const uint8 * source, unsigned size);
	RD_AUTO_GEN RDGeometryShaderRef RDCreateGeometryShader(const uint8 * source, unsigned size);

	RD_AUTO_GEN RDVertexDeclarationRef RDCreateVertexDeclaration(const VertexDeclarationElementList & elements);

	RD_AUTO_GEN RDBoundShaderStateRef RDCreateBoundShaderState(RDVertexDeclarationRef declaration, RDVertexShaderRef vertexShader, RDHullShaderRef hullShader, RDDomainShaderRef domainShader,RDPixelShaderRef pixelShader, RDGeometryShaderRef geometryShader);
	
	RD_AUTO_GEN void RDBeginRenderQuery(RDRenderQueryRef query);
	RD_AUTO_GEN void RDEndRenderQuery(RDRenderQueryRef query);
	RD_AUTO_GEN bool RDGetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait);

	RD_AUTO_GEN void RDClear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue);

	RD_AUTO_GEN void RDBeginFrame();
	RD_AUTO_GEN void RDEndFrame();

	RD_AUTO_GEN void RDBeginDrawing(RDRenderOutputP pOutput);
	RD_AUTO_GEN void RDEndDrawing(bool present);

	RD_AUTO_GEN void RDSetStreamSource(uint32 streamIndex, RDVertexBufferRef vertexBuffer, uint32 stride, uint32 offset);

	RD_AUTO_GEN void RDDrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances);
	RD_AUTO_GEN void RDDrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset);

	RD_AUTO_GEN void RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances);
	
	RD_AUTO_GEN void RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances);
	RD_AUTO_GEN void RDDrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 drawParamsOffset);
    
    RD_EXPORT_F PixelFormatInfo RDGetPixelFormatInfo(EPixelFormat format);
}