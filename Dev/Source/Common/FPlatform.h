#pragma once

#define F_PLATFORM_UNDEFINE 0
#define F_PLATFORM_WIN 1
#define F_PLATFORM_LINUX 2
#define F_PLATFORM_OSX 3
#define F_PLATFORM_IOS 4
#define F_PLATFORM_ANDROID 5

#if defined(__WIN32__) || defined(_WIN32)
#define F_CURRENT_PLATFORM F_PLATFORM_WIN
#elif defined(__APPLE__)
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE
	#define F_CURRENT_PLATFORM F_PLATFORM_IOS
	#else
	#define F_CURRENT_PLATFORM F_PLATFORM_OSX
	#endif
#elif defined(__linux)
#define F_CURRENT_PLATFORM F_PLATFORM_LINUX	
#elif defined(__ANDROID__)
#define F_CURRENT_PLATFORM F_PLATFORM_ANDROID
#else 
#define F_CURRENT_PLATFORM F_PLATFORM_UNDEFINE
#endif

//-----------------------------------------------------------------------------

#if F_CURRENT_PLATFORM == F_PLATFORM_WIN

#define API_EXPORT extern "C" __declspec(dllexport)
#define API_IMPORT extern "C" __declspec(dllimport)

#define API_EXPORT_CLASS __declspec(dllexport)
#define API_IMPORT_CLASS __declspec(dllimport)

#define FORCEINLINE __forceinline

#else

#define API_EXPORT extern "C"
#define API_IMPORT extern "C"

#define API_EXPORT_CLASS
#define API_IMPORT_CLASS

#define FORCEINLINE inline __attribute__ ((always_inline))

#endif


//-----------------------------------------------------------------------------

typedef long long unsigned int bits64;
typedef unsigned int bits32;
typedef unsigned short bits16;
typedef unsigned char bits8;

typedef long long unsigned int uint64;
typedef long long int int64;

typedef unsigned int uint32;
typedef int int32;