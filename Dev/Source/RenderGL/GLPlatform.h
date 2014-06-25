#pragma once

#include "DeviceInterfaces.h"

namespace FRE
{
	typedef uint64 h_GLContext;
	typedef uint64 h_GLRenderTarget;

	bool PlatformInit();

	h_GLContext PlatformCreateContext(h_GLContext shared = 0);
	h_GLRenderTarget PlatformCreateSurfaceTarget(h_GLContext context, const DarkParams & params);

	bool PlatformMakeCurrentContext(h_GLContext context);
	bool PlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target);
	bool PlatformSwapContext(h_GLContext context, h_GLRenderTarget target);

	void PlatformDestroyEntity(int64 handle);
}
