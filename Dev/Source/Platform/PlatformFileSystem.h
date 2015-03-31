#pragma once

#include "FStream.h"

class IFileHandle : public IStream
{
	public:
}

class IPlatformFile
{
public:
	virtual IFileHandle * OpenRead(const wchar_t * fileName) = 0;
	virtual IFileHandle * OpenWrite(const wchar_t * fileName, bool append = 0, bool allowRead = 0) = 0;
}

