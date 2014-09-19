#pragma once

#include "FreRDInterfaces.h"

namespace FRE
{
	class NullRenderDevice : public IRenderDevice
	{
	public:
		virtual void Release() override
		{
			delete this;
		}

		virtual char * GetName() const override
		{
			return "NullRenderDevice";
		}
	};
}
