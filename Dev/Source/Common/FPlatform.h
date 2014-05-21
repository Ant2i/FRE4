#pragma once

#if defined(_WIN32)

#define API_EXPORT extern "C" __declspec(dllexport)
#define API_IMPORT extern "C" __declspec(dllimport)

#define API_EXPORT_CLASS __declspec(dllexport)
#define API_IMPORT_CLASS __declspec(dllimport)

#else

#define API_EXPORT extern "C"
#define API_IMPORT extern "C"

#define API_EXPORT_CLASS
#define API_IMPORT_CLASS

#endif