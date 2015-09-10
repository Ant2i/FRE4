//#pragma once
//
//#include "FStream.h"
//#include <memory.h>
//
//class MemoryStream : public IStreamData
//{
//public:
//	virtual uint64 Read(void * data, uint64 size) override
//	{
//		if (IsReadable())
//		{
//            uint64 readSize = _offset + size <= Size() ? size : Size() - _offset;
//            if (readSize > 0)
//			{
//				memcpy(data, Begin() + _offset, readSize);
//				_offset += readSize;
//                return readSize;
//			}
//			
//		}
//		return 0;
//	}
//
//	virtual void Write(const void * data, uint64 size) override
//	{
//		if (IsWriteable())
//		{
//			if (_offset + size > Size())
//				ReAllocate(size);
//
//			if (_offset + size <= Size())
//			{
//				memcpy(Begin() + _offset, data, size);
//				_offset += size;
//			}
//		}
//	}
//
//	virtual void Seek(uint64 offset, SeekDirection origin) override
//	{
//		switch (origin)
//		{
//		case SeekDirection::Begin:
//			_offset = offset;
//			break;
//		case SeekDirection::Current:
//			_offset += offset;
//			break;
//		case SeekDirection::End:
//			_offset = Size() - offset;
//			break;
//		}
//	}
//
//	virtual bool IsEOF(void) const override
//	{
//		return _offset >= Size();
//	}
//
//    virtual uint64 Size() const = 0;
//    
//protected:
//	virtual uint8 * Begin() = 0;
//    virtual void ReAllocate(uint64 size) = 0;
//
//private:
//	uint64 _offset = 0;
//};
//
//class MemoryStreamReader : public MemoryStream
//{
//public:
//	MemoryStreamReader(void * memory, uint64 size) :
//		_memory(memory),
//		_size(size)
//	{
//	}
//
//	virtual bool IsReadable() const override { return true; }
//
//	virtual uint64 Size() const override
//	{
//		return _size;
//	}
//
//	virtual void Close() override
//	{
//		_size = 0;
//		_memory = nullptr;
//	}
//
//private:
//	virtual uint8 * Begin() override
//	{
//		return (uint8 *)_memory;
//	}
//	virtual void ReAllocate(uint64 size) override
//	{
//
//	}
//
//	void * _memory = nullptr;
//	uint64 _size;
//};
//
//class MemoryStreamWriter : public MemoryStream
//{
//public:
//	virtual bool IsWriteable() const override { return true; }
//
//	virtual uint64 Size() const override
//	{
//		return _memory.size();
//	}
//
//    uint8 * Ptr()
//    {
//        return Begin();
//    }
//    
//	virtual void Close() override
//	{
//		_memory.clear();
//	}
//
//private:
//	virtual uint8 * Begin() override
//	{
//		return _memory.data();
//	}
//	virtual void ReAllocate(uint64 size) override
//	{
//		_memory.resize(_memory.size() + size);
//	}
//
//private:
//	std::vector<uint8> _memory;
//};
//