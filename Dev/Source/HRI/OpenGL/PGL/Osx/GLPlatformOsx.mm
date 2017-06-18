#include "GLPlatformOsx.h"

class GLPlatformContext
{
public:
    GLContext * _openGLContext;
};

class GLPlatformRenderSurface
{
public:
    GLView * _view;
};

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
     OsxPlatform * platform = [OsxPlatform Init:majorVer :minorVer DebugMode:debugMode];
     if (platform)
     {
         [[platform GetGlContext] makeCurrentContext];
         [NSOpenGLContext clearCurrentContext];
     }
     return platform != nil;
}
 
GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP pShared)
{
     OsxPlatform * platform = [OsxPlatform GetInstance];
    
    NSOpenGLContext * sharedContext = pShared ? pShared->_openGLContext : nullptr;
    
    GLPlatformContext * pContext = new GLPlatformContext();
    pContext->_openGLContext = [[GLContext alloc] initWithFormat:[platform GetPixelFormat] shareContext:sharedContext];
    pContext->_openGLContext->_ctx = pContext;
    return pContext;
}
 
GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(uint64 params)
{
     NSRect rect = NSMakeRect(0, 0, 1000, 1000);
     GLView * view = [[GLView alloc] initWithFrame:rect];
     if (params)
     {
         NSView * parentView = (NSView *)params;
         [parentView addSubview: view];
         [view setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
         [view setAutoresizesSubviews: YES];
     }
    
    GLPlatformRenderSurface * pSurface = new GLPlatformRenderSurface();
    pSurface->_view = view;
     return pSurface;
 }
 
void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height)
 {
     NSOpenGLContext * context = [NSOpenGLContext currentContext];
     if (context && context.view == pSurface->_view)
     {
         [context update];
     }
 }

bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext)
{
     if (pContext)
     {
         GLContext * context = pContext->_openGLContext;
         [context makeCurrentContext];
         return [NSOpenGLContext currentContext] == context;
     }
     else
     {
         //[NSOpenGLContext clearCurrentContext];
     }
    
     return true;
}
 
bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
    if (pContext)
    {
        GLContext * context = pContext->_openGLContext;
        if (pSurface)
        {
            GLView * view = pSurface->_view;
            [context setView: view];
        }
        else
        {
           //invalid drawable.
           //[context setView: nullptr];
        }
        
        [context makeCurrentContext];
        return [NSOpenGLContext currentContext] == context;
    }
    else
    {
        //[NSOpenGLContext clearCurrentContext];
    }
    
    return true;
}

bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
    if (pContext)
    {
        GLContext * context = pContext->_openGLContext;
        [context flushBuffer];
        return true;
    }
    return false;
}

void GLPlatformContextDestroy(GLPlatformContextP pContext)
 {
     if (pContext)
     {
         GLContext * context = pContext->_openGLContext;
         if (context != nil)
         {
             if ([NSOpenGLContext currentContext] == context)
             {
                 [NSOpenGLContext clearCurrentContext];
             }
             [context dealloc];
         }
         delete pContext;
     }
 }
 
 void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
 {
     if (pSurface)
     {
         GLView * view = pSurface->_view;
         if (view != nil)
        {
            [view removeFromSuperview];
            [view dealloc];
        }
         delete pSurface;
     }
 }

GLPlatformContextP GLPlatformGetCurrentContext()
{
    NSOpenGLContext * context = [NSOpenGLContext currentContext];
    if (context != nil)
    {
        GLContext * ctx = (GLContext *)(context);
        ctx = [ctx isKindOfClass:[GLContext class]] ? ctx : nil;
        if (ctx != nil)
        {
            return ctx->_ctx;
        }
    }
    return nullptr;
}

//-------------------------------------------------------

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

@implementation GLContext

@end
