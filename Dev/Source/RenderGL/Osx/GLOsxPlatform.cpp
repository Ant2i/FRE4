#include "GLOsxPlatform.h"
#include "OsxPlatformObjects.h"

namespace FRE
{
    bool PlatformInit()
    {
        return false;
    }
    
	h_GLContext PlatformCreateContext(h_GLContext shared)
    {
        return 0;
    }
    
	h_GLRenderTarget PlatformCreateSurfaceTarget(h_GLContext context, const DarkParams & params)
    {
        OsxSurfaceTarget * surface = [[OsxSurfaceTarget alloc] initWithFrame:nil];
        return 0;
    }
    
	void PlatformUpdateSurfaceTarget(h_GLRenderTarget target, unsigned width, unsigned height)
    {
        
    }
    
	bool PlatformMakeCurrentContext(h_GLContext context)
    {
        return false;
    }
    
	bool PlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target)
    {
        return false;
    }
    
	bool PlatformSwapContext(h_GLContext context, h_GLRenderTarget target)
    {
        return false;
    }
    
	void PlatformDestroyEntity(int64 handle)
    {
        
    }
}