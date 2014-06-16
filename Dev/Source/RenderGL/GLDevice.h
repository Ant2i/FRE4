#pragma once

#include "DeviceInterfaces.h"

namespace FRE
{
	class GLDevice : public IRenderDevice
	{
	public:
		virtual std::string GetName() override
		{
			return "GLRenderDevice";
		}

		virtual IRenderTarget * CreateSurfaceRenderTarget(const DarkParams & params) override;

		virtual void BeginFrame(IRenderTarget * target) override;
		virtual void EndFrame() override;
	};
}