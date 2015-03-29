#pragma once

#include "FPlatform.h"

class Stream
{
public:
	enum class SeekDirection
	{
		Begin,
		Current,
		End
	};

public:
	virtual ~Stream() {}

	virtual void Seek(uint64 offset, SeekDirection origin = SeekDirection::Begin) = 0;
	virtual uint64 Read(void * data, uint64 size) = 0;
	virtual void Write(const void * data, uint64 size) = 0;

	// Get size of stream in byte.
	//virtual uint64 Size() const = 0;
	// Returns the current byte offset from beginning.
	//virtual uint64 Tell() const = 0;
	virtual bool IsEOF() const = 0;
	virtual void Close() = 0;

	virtual bool IsReadable() const { return false; }
	virtual bool IsWriteable() const { return false; }
};

template <typename T>
Stream & operator<<(Stream & s, T v)
{
	s.Write(&v, sizeof(v));
	return s;
}

template <typename T>
Stream & operator>>(Stream & s, T & v)
{
	s.Read(&v, sizeof(v));
	return s;
}

