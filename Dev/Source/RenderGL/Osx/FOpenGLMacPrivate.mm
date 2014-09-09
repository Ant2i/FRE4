#include "FOpenGLPlatform.h"
#include "FOpenGLMacPrivate.h"

namespace FRE
{
    bool GLPlatformInit(const GLVersion & ver, bool debugMode)
    {
        OsxPlatform * platform = [OsxPlatform Init:ver.Major :ver.Minor DebugMode:debugMode];
        if (platform)
        {
            [[platform GetGlContext] makeCurrentContext];
            bool init = glewInit() == GLEW_OK;
            [NSOpenGLContext clearCurrentContext];
        }
        return platform != nil;
    }
    
	h_GLContext GLContextCreate(h_GLContext hShared)
    {
        OsxPlatform * platform = [OsxPlatform GetInstance];
        return (h_GLContext)[[NSOpenGLContext alloc] initWithFormat:[platform GetPixelFormat] shareContext:(NSOpenGLContext *)hShared];
    }
    
	h_GLRenderTarget GLTargetCreate(h_GLContext hContext, uint64 params)
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
    
	void GLTargetUpdate(h_GLRenderTarget hTarget, unsigned width, unsigned height)
    {
        NSOpenGLContext * context = [NSOpenGLContext currentContext];
        if (context && context.view == (NSView *)hTarget)
            [context update];
    }
    
	bool GLContextMakeCurrent(h_GLContext hContext)
    {
        if (hContext != 0)
        {
            NSOpenGLContext * context = (NSOpenGLContext *)hContext;
            [context makeCurrentContext];
            return [NSOpenGLContext currentContext] == context;
        }
        //else
        //{
            //[NSOpenGLContext clearCurrentContext];
            //return true;
        //}
        
        return true;
    }
    
	bool GLContextMakeCurrent(h_GLContext hContext, h_GLRenderTarget hTarget)
    {
        NSOpenGLContext * context = (NSOpenGLContext *)hContext;
        NSView * view = (NSView *)hTarget;
        [context setView: view];
        [context makeCurrentContext];
        return [NSOpenGLContext currentContext] == context;
    }
    
	bool GLContextSwap(h_GLContext hContext, h_GLRenderTarget hTarget)
    {
        NSOpenGLContext * context = (NSOpenGLContext *)hContext;
        [context flushBuffer];
        return true;
    }
    
	void GLContextDestroy(h_GLContext hContext)
    {
        NSObject * object = (NSObject *)hContext;
        if (object != nil)
            [object dealloc];
    }
    
    void GLTargetDestroy(h_GLRenderTarget hTarget)
    {
        NSView * view = (NSView *)hTarget;
        if (view != nil)
        {
            [view removeFromSuperview];
            [view dealloc];
        }
    }
}

@implementation OsxPlatform

static OsxPlatform * sPlatform = nil;

+ (OsxPlatform *)Init:(unsigned)majorVersion :(unsigned)minorVersion DebugMode:(bool)mode
{
    if (!sPlatform)
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
        
        NSOpenGLPixelFormat * glPixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
        NSOpenGLContext * glContext = [[NSOpenGLContext alloc] initWithFormat:glPixelFormat shareContext:nil];
        
        sPlatform = [[OsxPlatform alloc] init];
        [sPlatform SetGlContext:glContext];
        [sPlatform SetPixelFormat:glPixelFormat];
        
        [glPixelFormat retain];
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
