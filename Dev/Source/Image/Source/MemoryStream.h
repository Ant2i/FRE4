#pragma once

#include "Image.h"
#include <memory>

namespace Image
{
	class MemoryStream : public IStream
	{
	public:
		MemoryStream(MemoryStream && stream)
		{
			_memory = stream._memory;
			_size = stream._size;
			_destroy = stream._destroy;
			_offset = stream._offset;

			stream._memory = nullptr;
		}

		MemoryStream(size_t size) : 
			_destroy(true),
			_size(size)
		{
			_memory = new char[size];
			Reset();
		}

		MemoryStream(char * memory, size_t size, bool destroy = false) : 
			_memory(memory),
			_size(size),
			_destroy(destroy)
		{
			Reset();
		}

		~MemoryStream()
		{
			if (_destroy && _memory)
				delete _memory;
		}

		virtual size_t Read(void * buffer, size_t size) override
		{
			auto readSize = (_offset + size > _size) ? _size - _offset : size;
			if (readSize > 0)
			{
				memcpy(buffer, _memory + _offset, (size_t)readSize);
				_offset += readSize;
			}
			return readSize;
		}

		virtual void Write(const void * buffer, size_t size) override
		{
			auto writeSize = (_offset + size > _size) ? _size - _offset : size;
			if (writeSize > 0)
			{
				memcpy(_memory + _offset, buffer, (size_t)writeSize);
				_offset += writeSize;
			}
		}

		virtual void Skip(size_t size) override
		{
			_offset += size;
		}

		virtual bool AtEnd() const override
		{
			return _offset >= _size;
		}

		void Reset()
		{
			_offset = 0;
		}

		size_t GetSize() const
		{
			return _size;
		}

		char * GetPtr() const
		{
			return _memory;
		}

	private:
		char * _memory;
		size_t _size; 
		bool _destroy;
		size_t _offset;
	};
}