#pragma once

#include "FreRDInterfaces.h"

#include "OpenGLBase.h"
#include "OpenGLContext.h"

namespace FRE
{
	class GLRenderTarget;

	class GLDevice : public IRenderDevice
	{
	public:
		static bool Init();

	public:
		GLDevice();
		virtual ~GLDevice();
		virtual void Release() override;

		virtual char * GetName() const override;

		virtual RDRenderTargetRef CreateSurfaceRenderTarget(const DarkParams & params) override;

		virtual RDRenderQueryRef CreateRenderQuery(RendetQuetyType type) override;
		virtual void BeginRenderQuery(RDRenderQueryRef query) override;
		virtual void EndRenderQuery(RDRenderQueryRef query) override;
		virtual bool GetRenderQueryResult(RDRenderQueryRef query, uint64 & result, bool wait) override;

        virtual void Clear(bool clearColor, const Math::Vector4f & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue) override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;

		virtual void BeginDrawing(RDRenderTargetP pTarget) override;
		virtual void EndDrawing(bool present) override;

		virtual void DrawPrimitive(uint32 primitiveType, uint32 baseVertexIndex, uint32 numPrimitives, uint32 numInstances) override;
		virtual void DrawPrimitiveIndirect(uint32 primitiveType, RDVertexBufferRef drawParams, uint32 drawParamsOffset) override;

		virtual void DrawIndexedIndirect(RDIndexBufferRef indexBuffer, uint32 primitiveType, RDStructureBufferRef drawParams, int32 drawParamsIndex, uint32 numInstances) override;

		virtual void DrawIndexedPrimitive(RDIndexBufferRef indexBuffer, uint32 primitiveType, int32 baseVertexIndex, uint32 minIndex, uint32 numVertices, uint32 startIndex, uint32 numPrimitives, uint32 numInstances) override;
		virtual void DrawIndexedPrimitiveIndirect(uint32 primitiveType, RDIndexBufferRef indexBuffer, RDVertexBufferRef drawParams, uint32 argumentOffset) override;

	private:
		GLPlatformContextP _context;
		GLRenderTarget * _currentFrameTarget;

		GLContext _sharedContext;
		GLContext _renderingContext;
	};
}