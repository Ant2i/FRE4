#include "FreRDMethods.h"
#include "FreRDInterfaces.h"

extern FRE::IRenderDevice * GlobalRD;

#define RD_FUNC_IMPL_DEFS(ReturnType, Name, DefParams, CallParams)\
ReturnType RD##Name##DefParams\
{\
	return GlobalRD->##Name##CallParams;\
}

namespace FRE
{

	#include "FreRDMethodsImpl_autogen.inc"

	//IMPL_RD_METHOD(RDRenderOutputRef, CreateSurfaceRenderOutput, (const DarkParams & params), (params));

	//IMPL_RD_METHOD(RDVertexBufferRef, CreateVertexBuffer, (uint32 size, uint32 usage, void * data), (size, usage, data));

	//IMPL_RD_METHOD(RDIndexBufferRef, CreateIndexBuffer, (uint32 size, uint32 usage, uint32 stride, void * data), (size, usage, stride, data));

	//IMPL_RD_METHOD(RDStructureBufferRef, CreateStructureBuffer, (uint32 size, uint32 usage, uint32 stride, void * data), (size, usage, stride, data));

	//IMPL_RD_METHOD(RDTexture2DRef, CreateTexture2D, (uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags), (sizeX, sizeY, format, numMips, numSamples, flags));

	//IMPL_RD_METHOD(RDRenderQueryRef, CreateRenderQuery, (ERenderQueryType type), (type));

	//IMPL_RD_METHOD(void, BeginRenderQuery, (RDRenderQueryRef query), (query));

	//IMPL_RD_METHOD(void, EndRenderQuery, (RDRenderQueryRef query), (query));

	//IMPL_RD_METHOD(bool, GetRenderQueryResult, (RDRenderQueryRef query, uint64 & result, bool wait), (query, result, wait));

	//IMPL_RD_METHOD(void, Clear, (bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue), (clearColor, colorValue, clearDepth, depthValue, clearStencil, stencilValue));

	//IMPL_RD_METHOD(void, BeginFrame, (), ());

	//IMPL_RD_METHOD(void, EndFrame, (), ());
	//
	//IMPL_RD_METHOD(void, BeginDrawing, (RDRenderOutputP pOutput), (pOutput));

	//IMPL_RD_METHOD(void, EndDrawing, (bool present), (present));

	//IMPL_RD_METHOD(void, DrawPrimitive, (uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances), (primitiveType, baseVertexIndex, numPrimitives, numInstances));

	//IMPL_RD_METHOD(void, DrawPrimitiveIndirect, (uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset), (primitiveType, drawParams, drawParamsOffset));

	//IMPL_RD_METHOD(void, DrawIndexedIndirect, (RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances), (indexBuffer, primitiveType, drawParams, drawParamsIndex, numInstances));

	//IMPL_RD_METHOD(void, DrawIndexedPrimitive, (RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances), (indexBuffer, primitiveType, baseVertexIndex, minIndex, numVertices, startIndex, numPrimitives, numInstances));

	//IMPL_RD_METHOD(void, DrawIndexedPrimitiveIndirect, (uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 drawParamsOffset), (primitiveType, indexBuffer, drawParams, drawParamsOffset));
}

#undef RD_FUNC_IMPL_DEFS