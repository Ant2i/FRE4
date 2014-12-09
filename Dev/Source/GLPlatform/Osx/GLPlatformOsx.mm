#include "GLPlatformOsx.h"

//#if F_CURRENT_PLATFORM == F_PLATFORM_OSX

bool GLPlatformInit(unsigned majorVer, unsigned minorVer, bool debugMode)
{
     OsxPlatform * platform = [OsxPlatform Init:majorVer :minorVer DebugMode:debugMode];
     if (platform)
     {
         [[platform GetGlContext] makeCurrentContext];
         bool init = glewInit() == GLEW_OK;
         [NSOpenGLContext clearCurrentContext];
     }
     return platform != nil;
}
 
GLPlatformContextP GLPlatformContextCreate(GLPlatformContextP hShared)
{
     OsxPlatform * platform = [OsxPlatform GetInstance];
     return (GLPlatformContextP)[[NSOpenGLContext alloc] initWithFormat:[platform GetPixelFormat] shareContext:(NSOpenGLContext *)hShared];
}
 
GLPlatformRenderSurfaceP GLPlatformSurfaceCreate(GLPlatformContextP hContext, uint64 params)
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
     return (GLPlatformRenderSurfaceP)view;
 }
 
void GLPlatformSurfaceUpdate(GLPlatformRenderSurfaceP pSurface, unsigned width, unsigned height)
 {
     NSOpenGLContext * context = [NSOpenGLContext currentContext];
     if (context && context.view == (NSView *)hSurface)
         [context update];
 }
 
bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext)
{
     if (pContext != 0)
     {
         NSOpenGLContext * context = (NSOpenGLContext *)pContext;
         [context makeCurrentContext];
         return [NSOpenGLContext currentContext] == context;
     }
     //else ?????
     //{
         //[NSOpenGLContext clearCurrentContext];
         //return true;
     //}
     
     return true;
}
 
bool GLPlatformContextMakeCurrent(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
     NSOpenGLContext * context = (NSOpenGLContext *)pContext;
     NSView * view = (NSView *)hTarget;
     [context setView: view];
     [context makeCurrentContext];
     return [NSOpenGLContext currentContext] == context;
}
 
bool GLPlatformContextSwap(GLPlatformContextP pContext, GLPlatformRenderSurfaceP pSurface)
{
     NSOpenGLContext * context = (NSOpenGLContext *)pContext;
     [context flushBuffer];
     return true;
}
 
void GLPlatformContextDestroy(GLPlatformContextP pContext)
 {
     NSObject * object = (NSObject *)pContext;
     if (object != nil)
         [object dealloc];
 }
 
 void GLPlatformSurfaceDestroy(GLPlatformRenderSurfaceP pSurface)
 {
     NSView * view = (NSView *)pSurface;
     if (view != nil)
     {
         [view removeFromSuperview];
         [view dealloc];
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

//#endif