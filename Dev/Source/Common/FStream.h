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

	virtual bool IsEOF() const = 0;
	virtual void Close() = 0;

	virtual bool IsReadable() const { return false; }
	virtual bool IsWriteable() const { return false; }
};

template <typename T>
Stream & operator<<(Stream & s, const T & v)
{
	s.Write(&v, sizeof(v));
	return s;
}

template <>
Stream & operator<<(Stream & s, const std::string & v)
{
	uint64 size = v.size();
	s.Write(&size, sizeof(size));
	s.Write(v.data(), sizeof(std::string::value_type) * size);
	return s;
}

template <typename T>
Stream & operator>>(Stream & s, T & v)
{
	s.Read(&v, sizeof(v));
	return s;
}

template <>
Stream & operator>>(Stream & s, std::string & v)
{
	uint64 size = 0;
	s.Read(&size, sizeof(size));
	if (size)
	{
		v.resize(size);
		s.Read((void *)v.data(), sizeof(std::string::value_type) * size);
	}
	return s;
}