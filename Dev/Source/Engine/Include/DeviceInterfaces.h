#pragma once
#include <string>

namespace FRE
{
	class IRenderDevice
	{
	public:
		virtual std::string GetName() = 0;
	};

	class IDeviceRegister
	{
	public:
		virtual void Register(IRenderDevice * device) = 0;
		virtual void Unregister(IRenderDevice * device) = 0;
	};


}