#pragma once

#include "FreRDInterfaces.h"
#include "FOpenGLPlatform.h"

namespace FRE
{
	class GLRenderTarget;

	class GLDevice : public IRenderDevice
	{
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

		virtual void BeginDrawViewport(RDRenderTargetH hTarget) override;
		virtual void EndDrawViewport() override;

		static bool Init();

	private:
		HGLContext _context;
		GLRenderTarget * _frameTarget;
	};
}