#pragma once

#include "RenderTarget.h"
#include <windows.h>

namespace FRE
{
	class RE_API WinWindowRenderTarget : public WindowRenderTarget
	{
	public:
		DECLARE_RESOURCE_TYPE(WinWindowRenderTarget, WindowRenderTarget);

		WinWindowRenderTarget(HWND hwnd);

		virtual unsigned Width() const { return 0; }
		virtual unsigned Height() const { return 0; }

		virtual void * SurfaceData() const = 0;

		WinWindowRenderTarget();
	};
}

