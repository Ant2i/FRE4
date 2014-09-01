#pragma once

#include "FreRDInterfaces.h"
#include "FreGLPlatform.h"

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

		virtual void BeginFrame(RenderTargetH target) override;
        virtual void Clear(bool clearColor, const Math::Vector4f_t & colorValue, bool clearDepth, float depthValue, bool clearStencil, uint32 stencilValue) override;
		virtual void EndFrame() override;

		static bool Init();

	private:
		h_GLContext _context;
		GLRenderTarget * _frameTarget;
		static const GLVersion NeededGLVersion;
	};
}