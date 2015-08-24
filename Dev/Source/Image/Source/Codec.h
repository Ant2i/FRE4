#pragma once

#include "Image.h"

#include <map>
#include <string>
#include <memory>
#include <vector>

namespace Image
{
	struct Data
	{
		Data() : 
			Format(PixelFormat::Unknown),
			Height(0),
			Width(0),
			Depth(0),
			MipMaps(0),
			DpmX(0),
			DpmY(0),
			Flags(0)
		{

		}

		PixelFormat Format;

		size_t Height;
		size_t Width;
		size_t Depth;
		size_t MipMaps;
		int Flags;
		int DpmX;
		int DpmY;

		std::vector<unsigned char> Bits;
	};

	class Codec
	{
	public:
		virtual Data Decode(IStream & input) const = 0;
		virtual std::unique_ptr<IStream> Encode(const Data & data) const = 0;

		virtual std::string GetType() const = 0;

		virtual bool MagicNumberMatch(const char * magicNumberPtr, size_t maxbytes) const
		{
			return !MagicNumberToFileExt(magicNumberPtr, maxbytes).empty();
		}

		virtual std::string MagicNumberToFileExt(const char * magicNumberPtr, size_t maxbytes) const = 0;
	};

}