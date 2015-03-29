#pragma once

#include "FStream.h"

class MemoryStream : public Stream
{
public:
	virtual uint64 Read(void * data, uint64 size) override
	{
		if (IsReadable())
		{
            uint64 readSize = _offset + size <= Size() ? size : Size() - _offset;
            if (readSize > 0)
			{
				memcpy(data, Begin() + _offset, readSize);
				_offset += readSize;
                return readSize;
			}
			
		}
		return 0;
	}

	virtual void Write(const void * data, uint64 size) override
	{
		if (IsWriteable())
		{
			if (_offset + size > Size())
				ReAllocate(size);

			if (_offset + size <= Size())
			{
				memcpy(Begin() + _offset, data, size);
				_offset += size;
			}
		}
	}

	virtual void Seek(uint64 offset, SeekDirection origin) override
	{
		switch (origin)
		{
		case SeekDirection::Begin:
			_offset = offset;
			break;
		case SeekDirection::Current:
			_offset += offset;
			break;
		case SeekDirection::End:
			_offset = Size() - offset;
			break;
		}
	}

	virtual bool IsEOF(void) const override
	{
		return _offset >= Size();
	}

    virtual uint64 Size() const = 0;
    
protected:
	virtual uint8 * Begin() = 0;
    virtual void ReAllocate(uint64 size) = 0;

private:
	uint64 _offset = 0;
};

class MemoryStreamReader : public MemoryStream
{
public:
	MemoryStreamReader(void * memory, uint64 size) :
		_memory(memory),
		_size(size)
	{
	}

	virtual bool IsReadable() const override { return true; }

	virtual uint64 Size() const override
	{
		return _size;
	}

	virtual void Close() override
	{
		_size = 0;
		_memory = nullptr;
	}

private:
	virtual uint8 * Begin() override
	{
		return (uint8 *)_memory;
	}

	virtual void ReAllocate(uint64 size) override
	{

	}

	void * _memory = nullptr;
	uint64 _size;
};

class MemoryStreamWriter : public MemoryStream
{
public:
	virtual bool IsWriteable() const override { return true; }

	virtual uint64 Size() const override
	{
		return _memory.size();
	}

    uint8 * Ptr()
    {
        return Begin();
    }
    
	virtual void Close() override
	{
		_memory.clear();
	}

private:
	virtual uint8 * Begin() override
	{
		return _memory.data();
	}

	virtual void ReAllocate(uint64 size) override
	{
		_memory.resize(_memory.size() + size);
	}

private:
	std::vector<uint8> _memory;
};

//class MemoryStream : public Stream
//{
//public:
//	typedef std::function<void(void *)> Destroy;
//
//public:
//	MemoryStream(void * memory, uint64 size, uint8 accessMode) :
//		_freeOnClose(false)
//	{
//		_data = static_cast<uint8 *>(memory);
//		_end = _data + size;
//		_pos = _data;
//	}
//
//	MemoryStream(void * memory, uint64 size, Destroy d, uint8 accessMode) :
//		_free(d),
//		_freeOnClose(false)
//	{
//		_data = static_cast<uint8 *>(memory);
//		_end = _data + size;
//		_pos = _data;
//	}
//
//	MemoryStream(Stream & sourceStream, uint8 accessMode) :
//		_freeOnClose(true)
//	{
//		const uint64 size = sourceStream.Size();
//		_data = new uint8[size];
//		_pos = _data;
//		_end = _data + sourceStream.Read(_data, size);
//
//		_free = [](void * data)
//		{
//			delete[](uint8 *)data;
//		};
//	}
//
//	MemoryStream(uint64 size, uint8 accessMode) :
//		_freeOnClose(true)
//	{
//		_data = new uint8[size];
//		_pos = _data;
//		_end = _data + size;
//
//		_free = [](void * data)
//		{
//			delete[](uint8 *)data;
//		};
//	}
//
//	MemoryStream::~MemoryStream()
//	{
//		Close();
//	}
//
//	virtual void Seek(uint64 offset, SeekDirection origin) override
//	{
//		switch (origin)
//		{
//		case SeekDirection::Begin:
//			_pos = _data + offset;
//			break;
//		case SeekDirection::Current:
//			_pos += offset;
//			break;
//		case SeekDirection::End:
//			_pos = _end - offset;
//			break;
//		}
//
//		if (_pos < _data)
//			_pos = _data;
//
//		if (_pos > _end)
//			_pos = _end;
//	}
//
//	virtual uint64 Read(void * buffer, uint64 size) override
//	{
//		if (IsReadable())
//		{
//			auto s = (_pos + size > _end) ? _end - _pos : size;
//			if (s > 0)
//			{
//				memcpy(buffer, _pos, (uint64)s);
//				_pos += s;
//			}
//			return s;
//		}
//		return 0;
//	}
//
//	virtual void Write(const void * buffer, size_t size) override
//	{
//		if (IsWriteable())
//		{
//			auto s = (_pos + size > _end) ? _end - _pos : size;
//			if (s > 0)
//			{
//				memcpy(_pos, buffer, (size_t)s);
//				_pos += s;
//			}
//		}
//	}
//
//	virtual uint64 Size() const override
//	{
//		return _end - _data;
//	}
//
//	virtual uint64 Tell(void) const override
//	{
//		return _pos - _data;
//	}
//
//	virtual bool IsEOF(void) const override
//	{
//		return _pos >= _end;
//	}
//
//	virtual void Close() override
//	{
//		if (_data && _free && _freeOnClose)
//		{
//			_free(_data);
//		}
//
//		_data = nullptr;
//		_pos = nullptr;
//		_end = nullptr;
//	}
//
//	uint8 * GetPtr() const { return _data; }
//
//	void SetFreeOnClose(bool free) { _freeOnClose = free; }
//
//private:
//	uint8 * _data;
//	uint8 * _end;
//	uint8 * _pos;
//	Destroy _free;
//	bool _freeOnClose;
//};

