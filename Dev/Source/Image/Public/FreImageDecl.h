#pragma once

#if _WIN32

#define API_EXPORT __declspec(dllexport)
#define API_IMPORT __declspec(dllimport)

#define API_EXPORT_CLASS __declspec(dllexport)
#define API_IMPORT_CLASS __declspec(dllimport)

#else

#define API_EXPORT extern 
#define API_IMPORT extern

#define API_EXPORT_CLASS __attribute__ ((visibility("default")))
#define API_IMPORT_CLASS __attribute__ ((visibility("default")))

#endif

#ifndef IMAGE_STATIC

#ifdef IMAGE_EXPORTS
	#define IMAGE_API API_EXPORT_CLASS
	#define IMAGE_API_F API_EXPORT
#else
	#define IMAGE_API API_IMPORT_CLASS
	#define IMAGE_API_F API_IMPORT
#endif

#else

#define IMAGE_API 
#define IMAGE_API_F

#endif
