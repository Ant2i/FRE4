#import "FOpenGLOsx.h"

namespace FRE
{
    bool GLPlatformInit(const GLVersion & ver, bool debugMode)
    {
        OsxPlatform * surface = [OsxPlatform Init:ver DebugMode:debugMode];
        return surface != nil;
    }
    
	h_GLContext GLPlatformContextCreate(h_GLContext hShared)
    {
        OsxPlatform * platform = [OsxPlatform GetInstance];
        return (h_GLContext)[[NSOpenGLContext alloc] initWithFormat:[platform GetPixelFormat] shareContext:(NSOpenGLContext *)hShared];
    }
    
	h_GLRenderTarget GLPlatformSurfaceTargetCreate(h_GLContext hContext, uint64 params)
    {
        NSRect rect = NSMakeRect(0, 0, 1000, 1000);
        NSView * view = [[GLView alloc] initWithFrame:rect];
        if (params)
        {
            NSView * parentView = (NSView *)params;
            [parentView addSubview: view];
            [view setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
            [view setAutoresizesSubviews: YES];
        }
        return (h_GLRenderTarget)view;
    }
    
	void GLPlatformSurfaceTargetUpdate(h_GLRenderTarget hTarget, unsigned width, unsigned height)
    {
        [[NSOpenGLContext currentContext] update];
    }
    
	bool GLPlatformContextMakeCurrent(h_GLContext hContext)
    {
        NSOpenGLContext * ctx = (NSOpenGLContext *)hContext;
        [ctx makeCurrentContext];
        return [NSOpenGLContext currentContext] == ctx;
    }
    
	bool GLPlatformContextMakeCurrent(h_GLContext hContext, h_GLRenderTarget hTarget)
    {
        NSOpenGLContext * ctx = (NSOpenGLContext *)hContext;
        NSView * view = (NSView *)hTarget;
        [ctx setView: view];
        [ctx makeCurrentContext];
        return [NSOpenGLContext currentContext] == ctx;
    }
    
	bool GLPlatformContextSwap(h_GLContext hContext, h_GLRenderTarget hTarget)
    {
        NSOpenGLContext * ctx = (NSOpenGLContext *)hContext;
        [ctx flushBuffer];
        return true;
    }
    
	void GLPlatformDestroyEntity(int64 handle)
    {
        NSObject * object = (NSObject *)handle;
        if (object != nil)
            [object dealloc];
    }
}

@implementation OsxPlatform

static OsxPlatform * sPlatform = nil;

+ (OsxPlatform *)Init:(FRE::GLVersion)version DebugMode:(bool)mode
{
    if (!sPlatform && version.Major >= 3)
    {
        unsigned int attributeIndex = 0;
        NSOpenGLPixelFormatAttribute attributes[40];
        
#define ADD_ATTR(x) { attributes[attributeIndex++] = x; }
#define ADD_ATTR2(x, y) { ADD_ATTR(x); ADD_ATTR(y); }
        
        ADD_ATTR2(NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core);
        ADD_ATTR2(NSOpenGLPFADepthSize, 32);
        ADD_ATTR(NSOpenGLPFADoubleBuffer);
        ADD_ATTR(0);
        
#undef ADD_ATTR
#undef ADD_ATTR2
        
        NSOpenGLPixelFormat * pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        NSOpenGLContext * tempContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
        
        sPlatform = [[OsxPlatform alloc] init];
        [sPlatform SetGlContext:tempContext];
        [sPlatform SetPixelFormat:pixelFormat];
        
        [pixelFormat retain];
    }
    
    return sPlatform;
}

+ (OsxPlatform *) GetInstance
{
    return sPlatform;
}

-(void)SetGlContext:(NSOpenGLContext *)context
{
    _openGLContext = context;
}

-(NSOpenGLContext *)GetGlContext
{
    return _openGLContext;
}

-(void)SetPixelFormat:(NSOpenGLPixelFormat *)pixelFormat
{
    _pixelFormat = pixelFormat;
}

-(NSOpenGLPixelFormat *)GetPixelFormat
{
    return _pixelFormat;
}

@end

@implementation GLView

-(void)drawRect:(NSRect)dirtyRect
{
    [[NSColor greenColor] setFill];
    NSRectFill(dirtyRect);
    [super drawRect:dirtyRect];
}

@end
