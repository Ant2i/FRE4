#include "RenderTarget.h"

namespace FRE
{
	IMPLEMENT_RESOURCE_TYPE(RenderTarget);

	RenderTarget::RenderTarget()
	{
		CONSTRUCTOR_RESOURCE_TYPE();
	}


	//----------------------------------------------------------------------------

	IMPLEMENT_RESOURCE_TYPE(WindowRenderTarget);

	WindowRenderTarget::WindowRenderTarget()
	{
		CONSTRUCTOR_RESOURCE_TYPE();
	}

	//RenderTarget * RenderTarget::CreateWindowTarget()
	//{
	//	return nullptr;
	//}

	//RenderTarget * RenderTarget::CreateMemmoryTarget()
	//{
	//	return nullptr;
	//}
}