//Описание
RD_FUNC_DEFS(RDRenderOutputRef RDCreateSurfaceRenderOutput(const DarkParams & params));
RD_FUNC_DEFS(RDVertexBufferRef RDCreateVertexBuffer(uint32 size, uint32 usage, void * data));
RD_FUNC_DEFS(RDIndexBufferRef RDCreateIndexBuffer(uint32 size, uint32 usage, uint32 stride, void * data));
RD_FUNC_DEFS(RDStructureBufferRef RDCreateStructureBuffer(uint32 size, uint32 usage, uint32 stride, void * data));

RD_FUNC_DEFS(RDTexture2DRef RDCreateTexture2D(uint32 sizeX, uint32 sizeY, uint32 format, uint32 numMips, uint32 numSamples, uint32 flags));
RD_FUNC_DEFS(RDRenderQueryRef RDCreateRenderQuery(ERenderQueryType type));

RD_FUNC_DEFS(void RDBeginRenderQuery(RDRenderQueryRef query));
RD_FUNC_DEFS(void RDEndRenderQuery(RDRenderQueryRef query));
RD_FUNC_DEFS(bool RDGetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait));

RD_FUNC_DEFS(void RDClear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue));

RD_FUNC_DEFS(void RDBeginFrame( ));
RD_FUNC_DEFS(void RDEndFrame( ));

RD_FUNC_DEFS(void RDBeginDrawing(RDRenderOutputP pOutput));
RD_FUNC_DEFS(void RDEndDrawing(bool present));

RD_FUNC_DEFS(void RDDrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances));
RD_FUNC_DEFS(void RDDrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset));

RD_FUNC_DEFS(void RDDrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances));

RD_FUNC_DEFS(void RDDrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances));
RD_FUNC_DEFS(void RDDrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 drawParamsOffset));
