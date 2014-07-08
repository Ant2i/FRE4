#import "FreGLOsxPlatform.h"

@class NSOpenGLContext, NSOpenGLPixelFormat, NSView;

namespace FRE
{
    bool GLPlatformInit(const GLVersion & ver, bool debugMode)
    {
        OsxPlatform * surface = [OsxPlatform InitWithGLVersion:ver DebugMode:debugMode];
        return surface != nil;
    }
    
	h_GLContext GLPlatformCreateContext(h_GLContext shared)
    {
        return 0;
    }
    
	h_GLRenderTarget GLPlatformCreateSurfaceTarget(h_GLContext context, uint64 params)
    {
        
        return 0;
    }
    
	void GLPlatformUpdateSurfaceTarget(h_GLRenderTarget target, unsigned width, unsigned height)
    {
        
    }
    
	bool GLPlatformMakeCurrentContext(h_GLContext context)
    {
        return false;
    }
    
	bool GLPlatformMakeCurrentContext(h_GLContext context, h_GLRenderTarget target)
    {
        return false;
    }
    
	bool GLPlatformSwapContext(h_GLContext context, h_GLRenderTarget target)
    {
        return false;
    }
    
	void GLPlatformDestroyEntity(int64 handle)
    {
        
    }
}

@implementation OsxPlatform

static OsxPlatform * sPlatform = nil;

+ (OsxPlatform *)InitWithMajor:(FRE::GLVersion)version DebugMode:(bool)mode
{
    if (sPlatform == nil)
    {
        NSOpenGLPixelFormatAttribute attributes[] = {
            NSOpenGLPFAOpenGLProfile,
            NSOpenGLProfileVersion3_2Core,
            0
        };
        
        NSOpenGLPixelFormat * pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        
        sPlatform = [[OsxPlatform alloc] init];
        [pixelFormat retain]
    }
    
    return sPlatform;
}

+ (OsxPlatform *) GetInstance
{
    return sPlatform;
}


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
