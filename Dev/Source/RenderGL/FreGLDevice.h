#pragma once

#include "FreDeviceInterfaces.h"
#include "FreGLPlatform.h"

namespace FRE
{
	class GLRenderTarget;

	class GLDevice : public IRenderDevice
	{
	public:
		GLDevice();
		~GLDevice();
		virtual void Release() override;

		virtual char * GetName() const override;

		virtual IRenderTarget * CreateSurfaceRenderTarget(const DarkParams & params) override;

		virtual void BeginFrame(IRenderTarget * target) override;
		virtual void EndFrame() override;

	private:
		h_GLContext _context;
		GLRenderTarget * _frameTarget;
	};
}