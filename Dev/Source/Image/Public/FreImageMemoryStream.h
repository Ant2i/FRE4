#pragma once

#include "FreImage.h"

#include <memory>
#include <assert.h>

namespace Image
{
	class MemoryStream : public IStream
	{
	public:
		MemoryStream(size_t size = 0) : 
			_size(0),
			_capacity(0),
			_rwOffset(0),
			_memory(nullptr)
		{
			if (size)
			{
				_memory = malloc(size);
				if (_memory)
					_capacity = _size = size;
			}
		}

		MemoryStream(MemoryStream && stream)
		{
			_memory = stream._memory;
			_size = stream._size;
			_rwOffset = stream._rwOffset;
			_capacity = stream._capacity;

			stream._memory = nullptr;
		}

		virtual ~MemoryStream()
		{
			if (_memory)
				free(_memory);
		}

		virtual size_t Read(void * buffer, size_t size) override
		{
			const auto unused = _size - _rwOffset;
			auto read = (unused < size) ? unused : size;
			if (read > 0)
			{
				memcpy(buffer, MemoryOffset(_rwOffset), (size_t)read);
				_rwOffset += read;
			}
			return read;
		}

		virtual void Write(const void * buffer, size_t size) override
		{
			Reserve(size);

			const auto access = _capacity - _rwOffset;
			if (access >= size)
			{
				memcpy(MemoryOffset(_rwOffset), buffer, size);
				_rwOffset += size;

				if (_size < _rwOffset)
					_size = _rwOffset;
			}
		}

		virtual void Skip(int size) override
		{
			if (size >= 0)
			{
				const auto unused = _size - _rwOffset;
				_rwOffset += (unused < size) ? unused : size;
			}
			else 
			{
				if (_rwOffset < std::abs(size))
					_rwOffset = 0;
				else
					_rwOffset += size;
			}
		}

		virtual bool AtEnd() const override
		{
			return _rwOffset >= _size;
		}

		void Reset()
		{
			_rwOffset = 0;
		}

		size_t GetSize() const
		{
			return _size;
		}

		void * GetPtr() const
		{
			return _memory;
		}

	private:
		inline size_t GrowTo(size_t size) const
		{
			return size + size / 2;
		}

		inline void Resize(size_t size)
		{
			void * ptr = realloc(_memory, size);
			if (ptr)
			{
				_memory = ptr;
				_capacity = size;
			}
		}

		inline void Reserve(size_t size)
		{
			const auto unused = _size - _rwOffset;
			if (unused < size)
				Resize(GrowTo(_size + size));
		}

		inline void * MemoryOffset(size_t offset) const
		{
			return reinterpret_cast<char *>(_memory)+offset;
		}

	private:
		void * _memory;
		size_t _size; 
		size_t _capacity;
		size_t _rwOffset;
	};
}
