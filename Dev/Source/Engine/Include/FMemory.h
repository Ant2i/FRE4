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
			static_assert(_Size > 0, "Size is zero.");

			enum : _I
			{
				AllocDataSize = sizeof(_T) * _Size
			};

		public:
			FixedMemory() :
				_data((_T *)malloc(AllocDataSize)),
				_allocIndexes(new BitSet<_Size, _I>()),
				_count(0)
			{
				 
			}

			FixedMemory(const FixedMemory & memory) :
				_data((_T *)malloc(AllocDataSize)),
				_allocIndexes(new BitSet<_Size, _I>(*memory._allocIndexes)),
				_count(memory._count)
			{
				memcpy(_data.get(), memory._data.get(), AllocDataSize);
			}

			ValueResult<_I> Allocate(const _T & val)
			{
				auto result = _allocIndexes->FindZeroBit();
				if (result.first)
					_Allocate(result.second, val);

				ValueResult<_I> res = { result.first, result.second };
				return res;
			}

			bool Allocate(_I index, const _T & val)
			{
				if (index < _Size)
				{
					_Allocate(index, val);
					return true;
				}
				return false;
			}

			void Free(_I index)
			{
				if (index < _Size)
					_Free(index);
			}

			_T & operator[](_I index)
			{
				return _data[index];
			}

			const _T & operator[](_I index) const
			{
				return _data[index];
			}

			_T & Element(_I index)
			{
				return index < _Size ? _data[index] : _data[0];
			}

			const _T & Element(_I index) const
			{
				return index < _Size ? _data[index] : _data[0];
			}

			bool IndexValidate(_I index) const
			{
				return _allocIndexes->Get(index);
			}

			_I Count() const
			{
				return _count;
			}

			void Swap(FixedMemory & memory)
			{
				std::swap(_data, memory._data);
				std::swap(_allocIndexes, memory._allocIndexes);
				std::swap(_count, memory._count);
			}

		private:
			void _Allocate(_I index, const _T & val)
			{
				if (!_allocIndexes->Get(index));
					++_count;

				new(_data.get() + index) _T(val);
				_allocIndexes->Set(index);
			}

			void _Free(_I index)
			{
				if (_allocIndexes->Get(index));
				--_count;

				_allocIndexes->Set(index, 0);
			}

			std::unique_ptr<_T, FreeDelete> _data;
			std::unique_ptr<BitSet<_Size, _I>> _allocIndexes;
			_I _count;
		};
		
		template <typename _T, unsigned _ChunkSize = 1024, typename _I = uintptr_t>
		class ChunkMemory
		{
			typedef FixedMemory<_T, _ChunkSize, _I> Chunk;

		public:
			ChunkMemory()
			{
				
			}
			
			ValueResult<_I> Allocate(const _T & val)
			{
				const _I chunkIndex = _FindLooseChunkIndex();
				Chunk & chunk = _AllocateChunk(chunkIndex);
				auto res = chunk.Allocate(val);
				if (res.valid)
					res.value += chunkIndex * _ChunkSize;
				return res;
			}

			bool Allocate(_I index, const _T & val)
			{
				const _I chunkIndex = index / _ChunkSize;
				Chunk & chunk = _AllocateChunk(chunkIndex);

				return chunk.Allocate(index - chunkIndex * _ChunkSize, val);
			}

			void Free(_I index)
			{
				Chunk * chunk = _GetChunk(index / _ChunkSize);
				if (chunk)
					chunk->Free(index);
			}

			_I Count() const
			{
				_I res(0);
				for (auto & chunk : _memory)
				{
					if (chunk)
						res += chunk->Count();
				}
				return res;
			}

		private:
			Chunk * _GetChunk(_I chunkIndex) const
			{
				if (chunkIndex < _memory.size())
					return _memory[chunkIndex];
				return nullptr;
			}

			Chunk & _AllocateChunk(_I chunkIndex)
			{
				if (chunkIndex >= _memory.size())
					_memory.resize(chunkIndex + 1);

				auto & chunk = _memory[chunkIndex];
				if (!chunk)
					chunk.reset(new Chunk());

				return *chunk;
			}

			_I _FindLooseChunkIndex() const
			{
				_I chunkIndex = 0;
				for (auto & chunk : _memory)
				{
					if (!chunk || chunk->Count() < _ChunkSize)
						break;
					++chunkIndex;
				}
				return chunkIndex;
			}

			std::vector<std::unique_ptr<Chunk>> _memory;
		};
	}
}