#pragma once

#include "Types.h"
#include <string>

namespace FRE
{
	class IRenderTarget
	{
	public:
		virtual void Release() = 0;
		virtual void SetSize(unsigned width, unsigned height) = 0;
	};

	struct DarkParams
	{
		uint64 params[6];
	};

	class IRenderDevice
	{
	public:
		virtual void Release() = 0;

		virtual char * GetName() const = 0;
		virtual IRenderTarget * CreateSurfaceRenderTarget(const DarkParams & params) = 0;

		//Temp
		virtual void BeginFrame(IRenderTarget * target) = 0;
		virtual void EndFrame() = 0;
	};

	class IDeviceRegister
	{
	public:
		virtual void Register(IRenderDevice * device) = 0;
	};
}