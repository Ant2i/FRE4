#pragma once

#include "Pixels.h"

namespace Image
{
	struct PixelFormatDescription
	{
		const char * Name;
		unsigned char ComponentCount;
		unsigned int Flags;
		//
		unsigned char Rbits, Gbits, Bbits, Abits;
		
		unsigned char GetSize() const
		{
			return (Rbits + Gbits + Bbits + Abits) / 8;
		}
	};

	PixelFormatDescription & GetDescription(PixelFormat format);
}