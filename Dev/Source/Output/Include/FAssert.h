#pragma once

#include "FOutput.h"

#ifndef _DEBUG
#define F_ASSERT(x) ((void)0)
#undef F_ASSERTS_ENABLED
#else
#define F_ASSERT(_exp) do { if (!!!(_exp)) Output::_Assert(#_exp, __FILE__, __LINE__); } while (0)
#define F_ASSERTS_ENABLED
#endif

#define F_VERIFY(_exp) do { if (!!!(_exp)) Output::_Assert(#_exp, __FILE__, __LINE__); } while (0)