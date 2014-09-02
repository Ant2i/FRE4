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
	typedef uint64 h_GLQuery;

	//-----------------------------------------------------------------------

	bool GLPlatformInit(const GLVersion & ver, bool debugMode);

	h_GLContext GLPlatformContextCreate(h_GLContext shared = 0);
	h_GLRenderTarget GLPlatformSurfaceTargetCreate(h_GLContext context, uint64 params);

	void GLPlatformSurfaceTargetUpdate(h_GLRenderTarget target, unsigned width, unsigned height);

	bool GLPlatformContextMakeCurrent(h_GLContext context);
	bool GLPlatformContextMakeCurrent(h_GLContext context, h_GLRenderTarget target);
	bool GLPlatformContextSwap(h_GLContext context, h_GLRenderTarget target);

	typedef void (*DebugCBFunc)(const char *);
	void GLPlatformDebugSetCallBack(DebugCBFunc cb);
	bool GLPlatformDebugEnable();
	void GLPlatformDebugDisable();

	//-----------------------------------------------------------------------

	h_GLQuery GLPlatformQueryCreate();

	void GLPlatformDestroyEntity(int64 handle);
}
