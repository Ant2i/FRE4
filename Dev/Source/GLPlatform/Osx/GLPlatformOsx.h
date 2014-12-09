#pragma once

#include "GLPlatform.h"
#import <Cocoa/Cocoa.h>

class GLPlatformContext
{
public:
    NSOpenGLContext * _openGLContext;
};

@interface OsxPlatform : NSObject
{
@private
    NSOpenGLContext * _openGLContext;
	NSOpenGLPixelFormat * _pixelFormat;
}

+ (OsxPlatform *) Init:(unsigned)majorVersion :(unsigned)minorVersion DebugMode:(bool)mode;
+ (OsxPlatform *) GetInstance;

-(void)SetGlContext:(NSOpenGLContext *)context;
-(NSOpenGLContext *)GetGlContext;

-(void)SetPixelFormat:(NSOpenGLPixelFormat *)pixelFormat;
-(NSOpenGLPixelFormat *)GetPixelFormat;
@end


@interface GLView : NSView
{
        
}

-(void)drawRect:(NSRect)dirtyRect;

@end