#pragma once

#include "config.h"
#include FRE_MATH_H
#include "FreTypes.h"

namespace FRE
{
	namespace Utils
	{
		inline unsigned char CountBits(unsigned char v)
		{
			const char * const countBits =
				"\0\1\1\2\1\2\2\3\1\2\2\3\2\3\3\4"
				"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
				"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
				"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
				"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
				"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
				"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
				"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
				"\1\2\2\3\2\3\3\4\2\3\3\4\3\4\4\5"
				"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
				"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
				"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
				"\2\3\3\4\3\4\4\5\3\4\4\5\4\5\5\6"
				"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
				"\3\4\4\5\4\5\5\6\4\5\5\6\5\6\6\7"
				"\4\5\5\6\5\6\6\7\5\6\6\7\6\7\7\x8";

			return countBits[v];
		}

		inline unsigned FirstZeroBit(bits8 val)
		{
			const char * const _firstZeroBitPos =
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\5"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\6"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\5"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\7"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\5"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\6"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\5"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\4"
				"\0\1\0\2\0\1\0\3\0\1\0\2\0\1\0\x8";
			return _firstZeroBitPos[val];
		}

		inline unsigned FirstZeroBit(bits16 val) 
		{
			if (~val & 0x00FF)
				return FirstZeroBit((bits8)val);
			return FirstZeroBit((bits8)(val >> 8)) + 8;
		}

		inline unsigned FirstZeroBit(bits32 val)
		{
			if (~val & 0x0000FFFF)
				return FirstZeroBit((bits16)val);
			return FirstZeroBit((bits16)(val >> 16)) + 16;
		}

		inline unsigned FirstZeroBit(bits64 val)
		{
			if (~val & 0x00000000FFFFFFFF)
				return FirstZeroBit((bits32)val);
			return FirstZeroBit((bits32)(val >> 32)) + 32;
		}

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
