#pragma once

#include "Types.h"
#include <string>

namespace FRE
{
	class IRenderTarget
	{
	public:
		virtual void Release() = 0;
	};

	class IRenderDevice
	{
	public:
		virtual std::string GetName() = 0;
		virtual IRenderTarget * CreateRenderDevice() = 0;
	};

	class IDeviceRegister
	{
	public:
		virtual void Register(IRenderDevice * device) = 0;
	};
}