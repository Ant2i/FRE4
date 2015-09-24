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
    RD_AUTO_GEN RDRenderOutputRef RDCreateSurfaceRenderOutput(const DarkParams & iParams);
	
	RD_AUTO_GEN RDVertexBufferRef RDCreateVertexBuffer(uint32_t iSize, uint32_t iUsage, void * iData);
	RD_AUTO_GEN void* RDLockBuffer(RDVertexBufferRef iBuffer, uint32_t iOffset, uint32_t iSize, ELockMode iAccess);
	RD_AUTO_GEN void RDUnlockBuffer(RDVertexBufferRef iBuffer);

	RD_AUTO_GEN RDStructureBufferRef RDCreateStructureBuffer(uint32_t iSize, uint32_t iUsage, uint32_t iStride, void * iData);
	RD_AUTO_GEN void* RDLockBuffer(RDStructureBufferRef iBuffer, uint32_t iOffset, uint32_t iSize, ELockMode iAccess);
	RD_AUTO_GEN void RDUnlockBuffer(RDStructureBufferRef iBuffer);

	RD_AUTO_GEN RDIndexBufferRef RDCreateIndexBuffer(uint32_t iSize, uint32_t iUsage, uint32_t iStride, void * iData);
	RD_AUTO_GEN void* RDLockBuffer(RDIndexBufferRef iBuffer, uint32_t iOffset, uint32_t iSize, ELockMode iAccess);
	RD_AUTO_GEN void RDUnlockBuffer(RDIndexBufferRef iBuffer);

	RD_AUTO_GEN RDTexture2DRef RDCreateTexture2D(uint32_t iWidth, uint32_t iHeight, uint32_t iFormat, uint32_t iNumMips, uint32_t iFlags);
    RD_AUTO_GEN RDTexture2DRef RDCreateTexture2DMS(uint32_t iWidth, uint32_t iHeight, uint32_t iFormat, uint32_t iNumSamples, uint32_t iFlags);
    
    RD_AUTO_GEN RDRenderQueryRef RDCreateRenderQuery(ERenderQueryType iType);

	RD_AUTO_GEN RDVertexShaderRef RDCreateVertexShader(const uint8_t * iSource, unsigned iSize);
	RD_AUTO_GEN RDPixelShaderRef RDCreatePixelShader(const uint8_t * iSource, unsigned iSize);
	RD_AUTO_GEN RDHullShaderRef RDCreateHullShader(const uint8_t * iSource, unsigned iSize);
	RD_AUTO_GEN RDDomainShaderRef RDCreateDomainShader(const uint8_t * iSource, unsigned iSize);
	RD_AUTO_GEN RDGeometryShaderRef RDCreateGeometryShader(const uint8_t * iSource, unsigned iSize);

	RD_AUTO_GEN RDVertexDeclarationRef RDCreateVertexDeclaration(const VertexElementDeclarationDesc * iElements, unsigned iNumElems);

	RD_AUTO_GEN RDPipelineStateRef RDCreatePipelineState(const PipelineStateDesc & iPipeline);
	
	RD_AUTO_GEN void RDBeginRenderQuery(RDRenderQueryRef iQuery);
	RD_AUTO_GEN void RDEndRenderQuery(RDRenderQueryRef iQuery);
	RD_AUTO_GEN bool RDGetRenderQueryResult(RDRenderQueryRef iQuery, uint64_t & iResult, bool iWait);

	RD_AUTO_GEN void RDClear(bool iClearColor, const Color & iColorValue, bool iClearDepth, float iDepthValue, bool iClearStencil, uint32_t iStencilValue);

	RD_AUTO_GEN void RDBeginFrame();
	RD_AUTO_GEN void RDEndFrame();

	RD_AUTO_GEN void RDBeginDrawing(RDRenderOutputP iOutput);
	RD_AUTO_GEN void RDEndDrawing(bool iPresent);

	RD_AUTO_GEN void RDSetStreamSource(uint32_t iStreamIndex, RDVertexBufferRef iBuffer, uint32_t iStride, uint32_t iOffset);

	RD_AUTO_GEN void RDDrawPrimitive(uint32_t iPrimitiveType, uint32_t iBaseVertexIndex, uint32_t iNumPrimitives, uint32_t iNumInstances);
	RD_AUTO_GEN void RDDrawPrimitiveIndirect(uint32_t iPrimitiveType, RDVertexBufferRef iDrawParams, uint32_t iDrawParamsOffset);

	RD_AUTO_GEN void RDDrawIndexedIndirect(RDIndexBufferRef iIndexBuffer, uint32_t iPrimitiveType, RDStructureBufferRef iDrawParams, int32_t iDrawParamsIndex, uint32_t iNumInstances);
	
	RD_AUTO_GEN void RDDrawIndexedPrimitive(RDIndexBufferRef iIndexBuffer, uint32_t iPrimitiveType, int32_t iBaseVertexIndex, uint32_t iMinIndex, uint32_t iNumVertices, uint32_t iStartIndex, uint32_t iNumPrimitives, uint32_t iNumInstances);
	RD_AUTO_GEN void RDDrawIndexedPrimitiveIndirect(uint32_t iPrimitiveType, RDIndexBufferRef iIndexBuffer, RDVertexBufferRef iDrawParams, uint32_t iDrawParamsOffset);
    
    RD_EXPORT_F PixelFormatInfo RDGetPixelFormatInfo(EPixelFormat iFormat);
}