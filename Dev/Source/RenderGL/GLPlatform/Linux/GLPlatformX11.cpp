#include "GLPlatformX11.h"


//-----------------------------------------------------------------------------

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
	static bool init = false;
	if (!init)
	{

	}
	return init;
}


GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP pShared)
{
	return nullptr;
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
{

}

GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(uint64 params)
{
	return nullptr;
}

void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
{

}

void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height)
{

}

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	return false;
}

bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
	return false;
}

GLPlatformContextP GLPlatformGetCurrentContext()
{

	return nullptr;
}

