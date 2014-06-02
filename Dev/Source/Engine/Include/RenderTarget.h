#pragma once

#include "Resource.h"

namespace FRE
{
	class RE_API RenderTarget : public Resource
	{
	public:
		static RenderTarget * CreateWindowTarget();
		static RenderTarget * CreateMemmoryTarget();

	private:
		RenderTarget()
		{

		}
	};
}