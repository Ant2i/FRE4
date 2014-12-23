#pragma once

#include "FPlatform.h"
#include "FMathDefs.h"

namespace FRE
{
	namespace Utils
	{
		template <typename _T>
		inline _T Max(_T a, _T b) 
		{
			return a > b ? a : b;
		}

		template <typename _T>
		inline _T Min(_T a, _T b)
		{
			return a < b ? a : b;
		}
	}
}

#define freMax(a, b) FRE::Utils::Max(a, b);
#define freMin(a, b) FRE::Utils::Min(a, b);
