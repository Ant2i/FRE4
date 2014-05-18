#pragma once

#include "Types.h"

namespace FRE
{
    struct FreeDelete
    {
        void operator()(void * x) { if (x) free(x); }
    };
    
    unsigned FirstZeroBit8(bits8 v)
    {
        bits8 sum = 1;
        for (int i = 0; i < 8; i++)
        {
            sum = sum << 1;
            if (v & sum)
                return 8 - i;
        }
        return 0;
    }
    
    unsigned FirstZeroBit16(bits16 v)
    {
        if (v < 0xFFFF)
        {
            if (v > 0x00FF)
                return FirstZeroBit8(v >> 8);
            else
                return FirstZeroBit8((bits8)v) + 8;
        }
        return 0;
    }
    
    unsigned FirstZeroBit32(bits32 v)
    {
        if (v < 0xFFFFFFFF)
        {
            if (v > 0x0000FFFF)
                return FirstZeroBit16(v >> 16);
            else
                return FirstZeroBit8((bits16)v) + 16;
        }
        return 0;
    }
    
    unsigned FirstZeroBit64(bits64 v)
    {
        if (v < 0xFFFFFFFFFFFFFFFF)
        {
            if (v > 0x00000000FFFFFFFF)
                return FirstZeroBit32(v >> 32);
            else
                return FirstZeroBit32((bits32)v);
        }
        return 0;
    }
    
    template <typename T, unsigned size = 1024>
    class ChunkMemory
    {
    public:
        ChunkMemory() :
            _allocCount(0),
            _allocIndexSize(size / 64 + 1)
        {
            const bool CheckTypeSize = sizeof(bits64) == 8 && sizeof(bits32) == 4 && sizeof(bits16) == 2;
            static_assert(CheckTypeSize, "Can't use base type.");
            
            _data.reset((T *)malloc(sizeof(T) * size));
            _freeIndex.reset((bits64 *)calloc(_allocIndexSize, sizeof(bits64)));
        }
        
        unsigned Allocate()
        {
            if (false)
                ++_allocCount;
            return 0;
        }
        
        void Free(unsigned index)
        {
            if (false)
                --_allocCount;
        }
        
        bool IsEmpty() const
        {
            return _allocCount == 0;
        }
        
    private:
        unsigned FindFreeIndex() const
        {
            for (unsigned i = 0; i < _allocIndexSize; ++i)
            {
                bits64 indexes = _allocIndexes[i];
                FirstZeroBit64(indexes);
            }
        }
        
        std::unique_ptr<T, FreeDelete> _data;
        std::unique_ptr<bits64, FreeDelete> _allocIndexes;
        unsigned _allocCount;
        const unsigned _allocIndexSize;
    };
    
    
	template <typename T>
	class Memory
	{
        
    private:
        T * _memory;
	};
}