#pragma once

#include "Resource.h"

namespace FRE
{
	class RE_API RenderTarget : public Resource
	{
	public:
		DECLARE_RESOURCE_TYPE(RenderTarget, Resource);

	protected:
		RenderTarget();
	};

	//----------------------------------------------------------------------------

	class RE_API WindowRenderTarget : public RenderTarget
	{
	public:
		DECLARE_RESOURCE_TYPE(WindowRenderTarget, RenderTarget);

		WindowRenderTarget();
	};
}