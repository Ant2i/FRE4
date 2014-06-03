#pragma once

#include "Resource.h"

namespace FRE
{
	class RE_API RenderTarget : public Resource
	{
	private:
		RenderTarget()
		{
		}
	};

	class RE_API WindowRenderTarget : public RenderTarget
	{
	public:
		//static Create
	};
}