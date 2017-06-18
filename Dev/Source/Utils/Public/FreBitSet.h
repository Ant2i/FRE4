#pragma once

#include "FPlatform.h"

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
        
        //---------------------------------------------
        
		template<unsigned _Size = 8, typename _I = uintptr_t>
		class BitSet
		{
			static_assert(std::is_signed<_I>::value != true, "Can't use signed type.");
			static_assert(_Size > 0, "Size is zero.");

			typedef bits64 WType;

			enum
			{
				_BitsPerWord = sizeof(WType) * 8,
				_Words = _Size == 0 ? 0 : (_Size - 1) / _BitsPerWord
			};

		public:
			BitSet()
			{
				Reset();
			}

			BitSet(const BitSet & set)
			{
				memcpy(_array, set._array, sizeof(_array));
			}

			void Reset()
			{
				for (WType & word : _array)
					word = 0;
			}

			void Set(_I pos, bool val = true)
			{
				if (val)
					_array[pos / _BitsPerWord] |= (WType)1 << pos % _BitsPerWord;
				else
					_array[pos / _BitsPerWord] &= ~((WType)1 << pos % _BitsPerWord);
			}

			bool Get(_I pos) const
			{
				return ((_array[pos / _BitsPerWord] & ((WType)1 << pos % _BitsPerWord)) != 0);
			}

			_I Count() const
			{
				const unsigned char * ptr = (const unsigned char *)(const void *)_array;
				const unsigned char * const end = ptr + sizeof(_array);

				unsigned count = 0;
				for (; ptr != end; ++ptr)
					count += CountBits(*ptr);
				return count;
			}

			std::pair<bool, _I> FindZeroBit() const
			{
				unsigned i = 0;
				for (const WType & word : _array)
				{
					if (word != std::numeric_limits<WType>::max())
					{
						const _I pos = FirstZeroBit(word) + i * _BitsPerWord;
						if (pos < _Size)
							return std::make_pair(true, pos);
					}
					++i;
				}
				return std::make_pair(false, 0);
			}

		protected:
			WType _array[_Words + 1];
		};
	}
}
