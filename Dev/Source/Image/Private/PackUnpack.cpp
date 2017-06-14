#include "FrePixels.h"

#include <algorithm>

namespace Image
{
	struct PixelIntPackInfo
	{
		unsigned char Rbits, Gbits, Bbits, Abits;
		uint64_t Rmask, Gmask, Bmask, Amask;
		unsigned int Rshift, Gshift, Bshift, Ashift;
		unsigned int Size;
	};

	//-------------------------------------------------------------------------

	inline uint32_t TrueBits(uint8_t n);
	inline uint32_t FloatToFixed(float value, uint8_t bits);
	inline float FixedToFloat(uint32_t value, uint8_t bits);
	inline uint32_t FixedToFixed(uint32_t value, uint8_t n, uint8_t p);

	//-------------------------------------------------------------------------

	PixelIntPackInfo GetPixelIntPackInfo(PixelFormat format)
	{
		PixelIntPackInfo ret;

		const PixelFormatDescription & desc = Pixels::GetDescription(format);

		ret.Rbits = desc.Rbits;
		ret.Gbits = desc.Gbits;
		ret.Bbits = desc.Bbits;
		ret.Abits = desc.Abits;

		ret.Rshift = desc.Gbits + desc.Bbits + desc.Abits;
		ret.Gshift = desc.Bbits + desc.Abits;
		ret.Bshift = desc.Abits;
		ret.Ashift = 0;

		ret.Rmask = TrueBits(desc.Rbits) << ret.Rshift;
		ret.Gmask = TrueBits(desc.Gbits) << ret.Gshift;
		ret.Bmask = TrueBits(desc.Bbits) << ret.Bshift;
		ret.Amask = TrueBits(desc.Abits) << ret.Ashift;

		if (desc.Flags & PF_RBInvert)
		{
			std::swap(ret.Rshift, ret.Bshift);
			std::swap(ret.Rmask, ret.Bmask);
		}

		ret.Size = (desc.Rbits + desc.Gbits + desc.Bbits + desc.Abits) / 8;

		return ret;
	}

	//-----------------------------------------------------

	template <typename T>
	T * GetP(void * p)
	{
		return (T *)p;
	}

	uint32_t PackInt24(uint8_t b1, uint8_t b2, uint8_t b3)
	{
		return (uint32_t)(b1 << 16) | (uint32_t)(b2 << 8) | (uint32_t)b3;
	}

	void UnpackInt24(uint8_t & b1, uint8_t & b2, uint8_t & b3, uint32_t v)
	{
		b1 = (v >> 16) & 0xFF;
		b2 = (v >> 8) & 0xFF;
		b3 = v & 0xFF;
	}

	uint32_t ReadInt32(void * p, int size)
	{
		switch (size)
		{
		case 1:
			return *GetP<uint8_t>(p);
		case 2:
			return *GetP<uint16_t>(p);
		case 3:
		{
			auto * ptr = GetP<uint8_t>(p);
			return PackInt24(ptr[0], ptr[1], ptr[2]);
		}
		case 4:
			return *GetP<uint32_t>(p);
		}
		return 0;
	}

	void WriteInt32(void * p, const int size, uint32_t value)
	{
		switch (size)
		{
		case 1:
			*GetP<uint8_t>(p) = (uint8_t)value;
			break;
		case 2:
			*GetP<uint16_t>(p) = (uint16_t)value;
			break;
		case 3:
		{
			auto * ptr = GetP<uint8_t>(p);
			UnpackInt24(ptr[0], ptr[1], ptr[2], value);
			break;
		}
		case 4:
			*GetP<uint32_t>(p) = value;
			break;
		}
	}

	//----------------------------------------------------------------

	bool PackInt(uint32_t r, uint32_t g, uint32_t b, uint32_t a, PixelFormat format, void * dest)
	{
		switch (format)
		{
		case PixelFormat::L8:
		case PixelFormat::L16:
		case PixelFormat::R16:
		case PixelFormat::R5G6B5:
		case PixelFormat::B5G6R5:
		case PixelFormat::RGB8:
		case PixelFormat::RGBA8:
		case PixelFormat::BGR8:
		case PixelFormat::BGRA8:
		{
			const PixelIntPackInfo & pinfo = GetPixelIntPackInfo(format);

			uint32_t value =
				((FixedToFixed(r, 8, pinfo.Rbits) << pinfo.Rshift) & pinfo.Rmask) |
				((FixedToFixed(g, 8, pinfo.Gbits) << pinfo.Gshift) & pinfo.Gmask) |
				((FixedToFixed(b, 8, pinfo.Bbits) << pinfo.Bshift) & pinfo.Bmask) |
				((FixedToFixed(a, 8, pinfo.Abits) << pinfo.Ashift) & pinfo.Amask);

			WriteInt32(dest, pinfo.Size, value);
			return true;
		}
		case PixelFormat::RGBA16:
			GetP<uint16_t>(dest)[3] = a;
		case PixelFormat::RGB16:
			GetP<uint16_t>(dest)[0] = r;
			GetP<uint16_t>(dest)[1] = g;
			GetP<uint16_t>(dest)[2] = b;
			return true;
		}
		return false;
	}

	bool PackFloat(float r, float g, float b, float a, PixelFormat format, void * dest)
	{
		switch (format)
		{
		case PixelFormat::R32F:
			GetP<float>(dest)[0] = r;
			return true;
		case PixelFormat::RGBA32F:
			GetP<float>(dest)[3] = a;
		case PixelFormat::RGB32F:
			GetP<float>(dest)[0] = r;
			GetP<float>(dest)[1] = g;
			GetP<float>(dest)[2] = b;
			return true;
		}
		return false;
	}

	void Pixels::PackI(uint32_t r, uint32_t g, uint32_t b, uint32_t a, PixelFormat format, void * dest)
	{
		if (!PackInt(r, g, b, a, format, dest))
			PackFloat(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f, format, dest);
	}

	void Pixels::PackF(float r, float g, float b, float a, PixelFormat format, void * dest)
	{
		if (!PackFloat(r, g, b, a, format, dest))
		{
			const PixelIntPackInfo & pinfo = GetPixelIntPackInfo(format);

			uint32_t ir = FloatToFixed(r, pinfo.Rbits);
			uint32_t ig = FloatToFixed(g, pinfo.Gbits);
			uint32_t ib = FloatToFixed(b, pinfo.Bbits);
			uint32_t ia = FloatToFixed(a, pinfo.Abits);
			PackInt(ir, ig, ib, ia, format, dest);
		}
	}

	//-------------------------------------------------------------------------

	bool UnpackInt(uint32_t & r, uint32_t & g, uint32_t & b, uint32_t & a, PixelFormat format, void * src)
	{
		switch (format)
		{
		case PixelFormat::L8:
		case PixelFormat::L16:
		case PixelFormat::R16:
		case PixelFormat::R5G6B5:
		case PixelFormat::B5G6R5:
		case PixelFormat::RGB8:
		case PixelFormat::RGBA8:
		case PixelFormat::BGR8:
		case PixelFormat::BGRA8:
		{
			const PixelIntPackInfo & pinfo = GetPixelIntPackInfo(format);

			const uint32_t value = ReadInt32(src, pinfo.Size);
			r = FixedToFixed((value & pinfo.Rmask) >> pinfo.Rshift, pinfo.Rbits, 8);
			g = FixedToFixed((value & pinfo.Gmask) >> pinfo.Gshift, pinfo.Gbits, 8);
			b = FixedToFixed((value & pinfo.Bmask) >> pinfo.Bshift, pinfo.Bbits, 8);

			if (Pixels::HasAlpha(format))
				a = FixedToFixed((value & pinfo.Amask) >> pinfo.Ashift, pinfo.Abits, 8);
			else
				a = 255;
			return true;
		}
		case PixelFormat::RGBA16:
			a = GetP<uint16_t>(src)[3];
		case PixelFormat::RGB16:
			r = GetP<uint16_t>(src)[0];
			g = GetP<uint16_t>(src)[1];
			b = GetP<uint16_t>(src)[2];
			return true;
		}

		return false;
	}

	bool UnpackFloat(float & r, float & g, float & b, float & a, PixelFormat format, void * src)
	{
		switch (format)
		{
		case PixelFormat::R32F:
			r = GetP<float>(src)[0];
			return true;
		case PixelFormat::RGBA32F:
			a = GetP<float>(src)[3];
		case PixelFormat::RGB32F:
			r = GetP<float>(src)[0];
			g = GetP<float>(src)[1];
			b = GetP<float>(src)[2];
			return true;
		}
		return false;
	}

	void Pixels::UnpackI(uint32_t & r, uint32_t & g, uint32_t & b, uint32_t & a, PixelFormat format, void * src)
	{
		if (!UnpackInt(r, g, b, a, format, src))
		{
			float fr, fg, fb, fa;
			if (UnpackFloat(fr, fg, fb, fa, format, src))
			{
				const PixelIntPackInfo & pinfo = GetPixelIntPackInfo(format);
				r = FloatToFixed(fr, pinfo.Rbits);
				g = FloatToFixed(fg, pinfo.Gbits);
				b = FloatToFixed(fb, pinfo.Bbits);
				a = FloatToFixed(fa, pinfo.Abits);
			}
		}
	}

	void Pixels::UnpackF(float & r, float & g, float & b, float & a, PixelFormat format, void * src)
	{
		if (!UnpackFloat(r, g, b, a, format, src))
		{
			uint32_t ir, ig, ib, ia;
			if (UnpackInt(ir, ig, ib, ia, format, src))
			{
				const PixelIntPackInfo & pinfo = GetPixelIntPackInfo(format);
				r = FixedToFloat(ir, pinfo.Rbits);
				g = FixedToFloat(ig, pinfo.Gbits);
				b = FixedToFloat(ib, pinfo.Bbits);
				a = FixedToFloat(ia, pinfo.Abits);
			}
		}
	}

	//----------------------------------------------------------------------------

	inline uint32_t TrueBits(uint8_t n)
	{
		return ((uint64_t)1 << n) - 1;
	}

	inline uint32_t FloatToFixed(float value, uint8_t bits)
	{
		if (value <= 0.0f) return 0;
		else if (value >= 1.0f) return TrueBits(bits);
		return (uint32_t)(value * ((uint64_t)1 << bits));
	}

	inline float FixedToFloat(uint32_t value, uint8_t bits)
	{
		if (bits)
			return (float)value / (float)TrueBits(bits);
		return 0.0;
	}

	// Convert N bit colour channel value to P bits.
	inline uint32_t FixedToFixed(uint32_t value, uint8_t n, uint8_t p)
	{
		if (n > p)
		{
			value >>= (n - p);
		}
		else if (n < p)
		{
			const auto maxN = TrueBits(n);
			if (value == maxN)
				value = TrueBits(p);
			else
			{
				auto k = ((uint64_t)1 << p) / maxN;
				value = (uint32_t)(value * k);
			}
		}
		return value;
	}
}
