#include "FreGLPlatform.h"

#import <Cocoa/Cocoa.h>

@interface OsxPlatform : NSObject
{
@private
    NSOpenGLContext * _openGLContext;
	NSOpenGLPixelFormat * _pixelFormat;
}

+ (OsxPlatform *) InitWithGLVersion:(FRE::GLVersion)version DebugMode:(bool)mode;
+ (OsxPlatform *) GetInstance;

@end
