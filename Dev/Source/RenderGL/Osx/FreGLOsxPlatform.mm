#import "FreGLOsxPlatform.h"
#
@class NSOpenGLContext, NSOpenGLPixelFormat;

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
    
	h_GLRenderTarget PlatformCreateSurfaceTarget(h_GLContext context, uint64 params)
    {
        OsxSurfaceTarget * surface = [OsxSurfaceTarget alloc];
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

@implementation OsxSurfaceTarget

//- (id)initWithFrame:(NSRect)frame pixelFormat:(NSOpenGLPixelFormat*)pixelFormat
//{
//	self = [super initWithFrame:frame];
//
//	if ( self )
//	{
//		_pixelFormat = [pixelFormat retain];
//
//		if ( _pixelFormat == nil )
//		{
//			NSLog(@"nil pixel format cannot be used to initialize a CustomOpenGLView");
//			[self release];
//			return nil;
//		}
//
//		_openGLContext = [[NSOpenGLContext alloc] initWithFormat:_pixelFormat shareContext:nil];
//
//		[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(_globalFrameDidChangeNotification:) name:NSViewGlobalFrameDidChangeNotification object:self];
//	}

//	return self;
//}

@end
