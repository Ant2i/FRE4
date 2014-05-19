#pragma once

#include "Types.h"

namespace FRE
{
	template<unsigned Size = 8> 
	class BitSet
	{
		typedef bits64 WType;

		enum
		{
			_BitsPerWord = sizeof(WType) * 8,
			_Words = Size == 0 ? 0 : (Size - 1) / _BitsPerWord
		};

	public:
		BitSet()
		{
			Reset();
		}

		void Reset()
		{
			for (WType & word : _array)
				word = 0;
		}

		void Set(unsigned pos, bool val = true)
		{
			if (val)
				_array[pos / _BitsPerWord] |= (WType)1 << pos % _BitsPerWord;
			else
				_array[pos / _BitsPerWord] &= ~((WType)1 << pos % _BitsPerWord);
		}

		bool Get(unsigned pos) const
		{
			return ((_array[pos / _BitsPerWord] & ((WType)1 << pos % _BitsPerWord)) != 0);
		}

		unsigned Count() const
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

			const unsigned char * ptr = (const unsigned char *)(const void *)_array;
			const unsigned char * const end = ptr + sizeof(_array);

			unsigned sum = 0;
			for (; ptr != end; ++ptr)
				sum += countBits[*ptr];
			return sum;
		}

		std::pair<bool, unsigned> FindZiroBit() const
		{
			const unsigned char * ptr = (const unsigned char *)(const void *)_array;
			const unsigned char * const end = ptr + sizeof(_array);
			
			for (unsigned i = 0; ptr != end; ++ptr, ++i)
			{
				if (*ptr != 0xFF)
				{
					const unsigned pos = FirstZeroBit(*ptr) + i * 8;
					if (pos < Size)
						return std::make_pair(true, pos);
				}
			}
			return std::make_pair(false, 0);
		}

	protected:
		unsigned FirstZeroBit(unsigned char val) const
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

		WType _array[_Words + 1];
	};

}