#pragma once

#include "Types.h"
#include "FBitSet.h"
#include <memory>
#include <vector>

namespace FRE
{
	namespace Utils
	{
		struct FreeDelete
		{
			void operator()(void * x) { if (x) free(x); }
		};

		template <typename _T>
		struct ValueResult
		{
			bool valid;
			_T value;
		};

		template <typename _T, unsigned _Size = 1024, typename _I = uintptr_t>
		class FixedMemory
		{
			static_assert(!std::is_signed<_I>::value == true, "Can't use signed type.");

			enum : _I
			{
				AllocDataSize = sizeof(_T) * _Size
			};

		public:
            typedef ValueResult<_I> IndexResult;
            
			FixedMemory()
			{
				_data.reset((_T *)malloc(AllocDataSize));
			}

			FixedMemory(const FixedMemory & memory)
			{
				_data.reset((_T *)malloc(AllocDataSize));
				memcpy(_data.get(), memory._data.get(), AllocDataSize);
				_allocIndexes = memory._allocIndexes;
			}

			IndexResult Allocate(const _T & val)
			{
				auto result = _allocIndexes.FindZeroBit();
				if (result.first)
				{
					const auto allocIndex = result.second;
					new(_data.get() + allocIndex) _T(val);
					_allocIndexes.Set(allocIndex);
				}

				IndexResult res = { result.first, result.second };
				return res;
			}

			_T & Element(_I index)
			{
				return _data[index];
			}

			const _T & Element(_I index) const
			{
				return _data[index];
			}

			bool IndexValidate(_I index) const
			{
				if (index < _Size)
					return _allocIndexes.Get(index);
				return false;
			}

			void Free(_I index)
			{
				_allocIndexes.Set(index, 0);
			}

			bool IsEmpty() const
			{
				return _allocIndexes.Count() == 0;
			}

		private:
			std::unique_ptr<_T, FreeDelete> _data;
			BitSet<_Size, _I> _allocIndexes;
		};


		template <typename _T, unsigned _SizeChunk = 1024, typename _I = uintptr_t>
		class ChunkMemory
		{
		public:

		private:
			typedef std::unique_ptr<FixedMemory<_T, _SizeChunk, _I>> ChunkPtr;
			std::vector<ChunkPtr> _memory;
		};
	}
}