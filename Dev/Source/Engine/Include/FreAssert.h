#pragma once

#include "FreBase.h"

inline bool IsDebug()
{
#ifdef _DEBUG
	return true;
#else
	return false;
#endif
}

RE_API_F void _FRE_Assert(const char * exp, const char * file, unsigned line);
RE_API_F void _FRE_OutputDebugString(const char *p);

#ifndef _DEBUG
#define FRE_ASSERT(x) ((void)0)
#undef FRE_ASSERTS_ENABLED
#else
#define FRE_ASSERT(_exp) (void)((!!!(_exp)) || (_FRE_Assert(#_exp, __FILE__, __LINE__), 0))
#define FRE_ASSERTS_ENABLED
#endif

#define FRE_VERIFY(_exp) do { if (!!!(_exp)) _FRE_Assert(#_exp, __FILE__, __LINE__); } while (0)