//#pragma once
//
//#include "FPlatform.h"
////#include <string>
//
//class IStreamData
//{
//public:
//	enum class SeekDirection
//	{
//		Begin,
//		Current,
//		End
//	};
//
//public:
//	virtual ~IStreamData() {}
//
//	virtual uint64 Read(void * data, uint64 size) = 0;
//	virtual void Write(const void * data, uint64 size) = 0;
//	virtual void Seek(uint64 offset, SeekDirection origin = SeekDirection::Begin) = 0;
//
//	virtual bool IsEOF() const = 0;
//	virtual void Close() = 0;
//
//	virtual bool IsReadable() const { return false; }
//	virtual bool IsWriteable() const { return false; }
//};
//
//template <typename T>
//inline IStreamData & operator<<(IStreamData & s, const T & v)
//{
//	s.Write(&v, sizeof(v));
//	return s;
//}
//
//template <>
//inline IStreamData & operator<<(IStreamData & s, const std::string & v)
//{
//	uint64 size = v.size();
//	s.Write(&size, sizeof(size));
//	s.Write(v.data(), sizeof(std::string::value_type) * size);
//	return s;
//}
//
//template <typename T>
//inline IStreamData & operator>>(IStreamData & s, T & v)
//{
//	s.Read(&v, sizeof(v));
//	return s;
//}
//
//template <>
//inline IStreamData & operator>>(IStreamData & s, std::string & v)
//{
//	uint64 size = 0;
//	s.Read(&size, sizeof(size));
//	if (size)
//	{
//		v.resize(size);
//		s.Read((void *)v.data(), sizeof(std::string::value_type) * size);
//	}
//	return s;
//}
//
