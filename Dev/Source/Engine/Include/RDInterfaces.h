#pragma once

#include "RDResources.h"

#define RD_FUNC_IMPL_DEFS(ReturnType, Name, DefParams, CallParams, DefReturn) virtual ReturnType Name DefParams { DefReturn; }

namespace FRE
{
	class IRenderDevice
	{
	public:
		virtual void Release() = 0;
		virtual const char * GetName() const = 0;

		virtual void SetOutputDebug() {};

		#include "RDMethodsDefs.inc"

	protected:
		virtual ~IRenderDevice() {}
	};

	class IDeviceRegister
	{
	public:
		virtual void Register(IRenderDevice * device) = 0;
	};

	class IModule
	{
	public:
		virtual void Startup() = 0;
		virtual void Shutdown() = 0;
	};
}

#undef RD_FUNC_IMPL_DEFS