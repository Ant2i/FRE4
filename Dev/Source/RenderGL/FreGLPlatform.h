#pragma once

#include "FreTypes.h"

namespace FRE
{
	typedef uint64 h_GLContext;
	typedef uint64 h_GLRenderTarget;

	bool PlatformInit();

	h_GLContext PlatformCreateContext(h_GLContext shared = 0);
	h_GLRenderTarget PlatformCreateSurfaceTarget(h_GLContext context, uint64 params);

	void PlatformUpdateSurfaceTarget(h_GLRenderTarget target, unsigned width, unsigned height);

	bool PlatformMakeCurrentContext(h_GLContext context);
	bool PlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target);
	bool PlatformSwapContext(h_GLContext context, h_GLRenderTarget target);

	void PlatformDestroyEntity(int64 handle);
}
