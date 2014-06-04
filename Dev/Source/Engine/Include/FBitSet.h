#pragma once

#include "FMath.h"

namespace FRE
{
	namespace Utils
	{
		template<unsigned _Size = 8, typename _I = uintptr_t>
		class BitSet
		{
			static_assert(!std::is_signed<_I>::value == true, "Can't use signed type.");
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
					count += Utils::CountBits(*ptr);
				return count;
			}

			std::pair<bool, _I> FindZeroBit() const
			{
				unsigned i = 0;
				for (const WType & word : _array)
				{
					if (word != std::numeric_limits<WType>::max())
					{
						const _I pos = Utils::FirstZeroBit(word) + i * _BitsPerWord;
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