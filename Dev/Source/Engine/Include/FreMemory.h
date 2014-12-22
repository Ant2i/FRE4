#pragma once

#include "FPlatform.h"

#include <memory>
#include <list>

namespace FRE
{
	namespace Utils
	{
		template <typename _I = unsigned>
		class FPoolChunk
		{
			static_assert(!std::is_signed<_I>::value == true, "Can't use signed type.");

		public:
			FPoolChunk(size_t allocSize, _I numBlocks = 1000) : 
				NumBlocks(numBlocks), 
				AllocSize(allocSize), 
				IndicesPerAlloc(allocSize / sizeof(_I)),
				_memory(new _I[NumBlocks * IndicesPerAlloc]),
				_last(MemoryPtr() + NumBlocks * IndicesPerAlloc),
				_numFreeBlocks(numBlocks)
			{
				for (_I i = 0; i < NumBlocks; ++i)
				{
					auto * _ptr = AddressFromIndex(i);
					*_ptr = i + 1;
				}
				_nextFreeBlock = MemoryPtr();
			}

			inline _I * AddressFromIndex(_I index)
			{
				return MemoryPtr() + (index * IndicesPerAlloc);
			}

			inline _I IndexFromAddress(_I * pointer)
			{
				_I index = ((_I)(pointer - MemoryPtr())) / (int)IndicesPerAlloc;
				return index;
			}

			bool In(void * pointer) const
			{
				return pointer >= MemoryPtr() && pointer < _last; 
			}

			bool IsEmpty() const
			{ 
				return _numFreeBlocks == NumBlocks; 
			}

			bool IsFull() const
			{
				return _numFreeBlocks == 0; 
			}

			void * Allocate()
			{
				void * allocPtr = nullptr;
				if (_numFreeBlocks != 0)
				{
					allocPtr = (void *)_nextFreeBlock;
					_numFreeBlocks = _numFreeBlocks - 1;
					_nextFreeBlock = _numFreeBlocks ? AddressFromIndex(*_nextFreeBlock) : nullptr;
				}
				return allocPtr;
			}

			void Deallocate(void * pointer)
			{
//				if (In(pointer))
//				{
					_I * const prevFreeBlock = _nextFreeBlock;
					_nextFreeBlock = (_I *)pointer;
					*_nextFreeBlock = prevFreeBlock ? IndexFromAddress(prevFreeBlock) : NumBlocks;
					++_numFreeBlocks;
//				}
			}

		private:
			inline _I * MemoryPtr() const
			{
				return _memory.get();
			}

			const _I NumBlocks;
			const size_t AllocSize;
			const size_t IndicesPerAlloc;
			std::unique_ptr<_I[]> const _memory;
			_I * const _last;
			_I _numFreeBlocks;
			_I * _nextFreeBlock;
		};

		//-------------------------------------------------------------------

		template <typename _T, size_t ChunkSize = 1000>
		class FPoolMemory
		{
			typedef FPoolChunk<unsigned> ChunkType;
			enum
			{
				Size = sizeof(_T)
			};

		public:
			void * Allocate()
			{
				ChunkType * allocChunk = FindChunkForAlloc();
				if (!allocChunk)
				{
					allocChunk = new ChunkType(Size, ChunkSize);
					_chunks.push_back(std::unique_ptr<ChunkType>(allocChunk));
				}
				return allocChunk->Allocate();
			}

			void Deallocate(void * pointer)
			{
				ChunkType * chunk = FindChunkForDealloc(pointer);
				if (chunk)
					chunk->Deallocate(pointer);
			}

		private:
			ChunkType * FindChunkForAlloc() const
			{
				for(auto & chunk : _chunks)
				{
					if(!chunk->IsFull())
						return chunk.get();
				}
				return nullptr;
			}

			ChunkType * FindChunkForDealloc(void * p) const
			{
				for(auto & chunk : _chunks)
				{
					if(!chunk->In(p))
						return chunk.get();
				}
				return nullptr;
			}

		private:
			typedef std::list<std::unique_ptr<ChunkType>> ChunkList;
			ChunkList _chunks;
		};
	}
}