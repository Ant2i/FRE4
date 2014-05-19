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
			AllocRes res = { false, 0 };
			auto result = _allocIndexes.FindZiroBit();
			if (result.first)
			{
				const auto allocIndex = result.second;
				new (_data.get() + allocIndex) T(val);
				_allocIndexes.Set(allocIndex);

				res.index = allocIndex;
				res.allocated = true;
			}

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
        T * _memory;
	};
}