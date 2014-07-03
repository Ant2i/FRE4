#pragma once

#include "FreTypes.h"

namespace FRE
{
	struct GLVersion
	{
		GLVersion(unsigned major = 0, unsigned minor = 0) :
			Major(major),
			Minor(minor)
		{

		}

		unsigned Major;
		unsigned Minor;
	};

	//-----------------------------------------------------------------------

	typedef uint64 h_GLContext;
	typedef uint64 h_GLRenderTarget;

	bool GLPlatformInit(const GLVersion & ver);

	h_GLContext GLPlatformCreateContext(h_GLContext shared = 0);
	h_GLRenderTarget GLPlatformCreateSurfaceTarget(h_GLContext context, uint64 params);

	void GLPlatformUpdateSurfaceTarget(h_GLRenderTarget target, unsigned width, unsigned height);

	bool GLPlatformMakeCurrentContext(h_GLContext context);
	bool GLPlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target);
	bool GLPlatformSwapContext(h_GLContext context, h_GLRenderTarget target);

	void GLPlatformDestroyEntity(int64 handle);
}
