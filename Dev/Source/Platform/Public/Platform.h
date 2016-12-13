#pragma once

#ifndef PLATFORM_WIN
#define PLATFORM_WIN 0
#endif
#ifndef PLATFORM_IOS
#define PLATFORM_IOS 0
#endif
#ifndef PLATFORM_OSX
#define PLATFORM_OSX 0
#endif
#ifndef PLATFORM_LINUX
#define PLATFORM_LINUX 0
#endif
#ifndef PLATFORM_ANDROID
#define PLATFORM_ANDROID 0
#endif

//-----------------------------------------------------------------------------

#if PLATFORM_WIN
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

//-----------------------------------------------------------------------------

namespace ft
{
	typedef unsigned char 		uint8;	
	typedef unsigned short int	uint16;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;
												
	typedef	signed char			int8;	
	typedef signed short int	int16;	
	typedef signed int	 		int32;	
	typedef signed long long	int64;	

	typedef uint64 bits64;
	typedef uint32 bits32;
	typedef uint16 bits16;
	typedef uint8  bits8;
}
