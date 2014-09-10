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

		virtual RenderTargetRef CreateSurfaceRenderTarget(const DarkParams & params) override;

		virtual RenderQueryRef CreateRenderQuery(RendetQuetyType type) override;
		virtual void BeginRenderQuery(RenderQueryRef query) override;
		virtual void EndRenderQuery(RenderQueryRef query) override;
		virtual bool GetRenderQueryResult(RenderQueryRef query, uint64 & result, bool wait) override;

        virtual void Clear(bool clearColor, const Math::Vector4f_t & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue) override;

		virtual void BeginFrame(RenderTargetH target) override;
		virtual void EndFrame() override;

		static bool Init();

	private:
		HGLContext _context;
		GLRenderTarget * _frameTarget;
		static const GLVersion NeededGLVersion;
	};
}