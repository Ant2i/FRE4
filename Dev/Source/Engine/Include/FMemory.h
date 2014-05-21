#pragma once

#include "Types.h"
#include "FBitSet.h"

namespace FRE
{
    struct FreeDelete
    {
        void operator()(void * x) { if (x) free(x); }
    };
    
    template <typename T, unsigned Size = 1024>
    class ChunkMemory
    {
	public:
		struct AllocRes
		{
			bool allocated;
			unsigned index;
		};

    public:
        ChunkMemory()
        {
            _data.reset((T *)malloc(sizeof(T) * Size));
        }
        
		AllocRes Allocate(const T & val)
        {
			auto result = _allocIndexes.FindZeroBit();
            if (result.first)
			{
				const auto allocIndex = result.second;
				new (_data.get() + allocIndex) T(val);
				_allocIndexes.Set(allocIndex);
			}

            AllocRes res = { result.first, result.second };
            return res;
        }
        
        void Free(unsigned index)
        {
			_allocIndexes.Set(index, 0);
        }
        
        bool IsEmpty() const
        {
            return _allocIndexes.Count() == 0;
        }
        
    private:
        std::unique_ptr<T, FreeDelete> _data;
		BitSet<Size> _allocIndexes;
    };
    
    
	template <typename T>
	class Memory
	{
        
    private:
        ChunkMemory<T> * _memory;
	};
}