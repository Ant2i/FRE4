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

		virtual ISurfaceTarget * CreateSurfaceRenderTarget(const TargetParams & param) override;

		virtual void BeginFrame(IRenderTarget * target) override;
		virtual void EndFrame() override;
	};
}