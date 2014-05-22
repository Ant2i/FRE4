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
		struct ResultValue
		{
			bool valid;
			_T value;
		};

		template <typename _T, typename _I, unsigned _Size = 1024>
		class ChunkData
		{
			static_assert(!std::is_signed<_I>::value == true, "Can't use signed type.");

			enum
			{
				AllocDataSize = sizeof(_T) * _Size
			};

		public:
			ChunkData()
			{
				_data.reset((_T *)malloc(AllocDataSize));
			}

			ChunkData(const ChunkData & data)
			{
				_data.reset((_T *)malloc(AllocDataSize));
				memcpy(_data.get(), data._data.get(), AllocDataSize);
				_allocIndexes = data._allocIndexes;
			}

			ResultValue<_T> Allocate(const _T & val)
			{
				auto result = _allocIndexes.FindZeroBit();
				if (result.first)
				{
					const auto allocIndex = result.second;
					new(_data.get() + allocIndex) _T(val);
					_allocIndexes.Set(allocIndex);
				}

				ResultValue<_T> res = { result.first, result.second };
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

			bool ValidIndex(_I index) const
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
			BitSet<_I, _Size> _allocIndexes;
		};


		template <typename _T, typename _I>
		class ChunkMemory
		{
		public:

		private:
			typedef std::unique_ptr<ChunkData<_T, _I>> ChunkDataPtr;
			std::vector<ChunkDataPtr> _memory;
		};
	}
}