#include "FormatDesription.h"

#include <algorithm>

namespace Image
{
	struct PixelIntPackInfo
	{
		unsigned char Rbits, Gbits, Bbits, Abits;
		FPlatform::uint64 Rmask, Gmask, Bmask, Amask;
		unsigned int Rshift, Gshift, Bshift, Ashift;
		unsigned int Size;
	};

	//-------------------------------------------------------------------------

	inline FPlatform::uint32 TrueBits(FPlatform::uint8 n);
	inline FPlatform::uint32 FloatToFixed(float value, FPlatform::uint8 bits);
	inline float FixedToFloat(FPlatform::uint32 value, FPlatform::uint8 bits);
	inline FPlatform::uint32 FixedToFixed(FPlatform::uint32 value, FPlatform::uint8 n, FPlatform::uint8 p);

	//-------------------------------------------------------------------------

	PixelIntPackInfo GetPixelIntPackInfo(PixelFormat format)
	{
		PixelIntPackInfo ret;

		const PixelFormatDescription & desc = GetDescription(format);

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

	FPlatform::uint32 PackInt24(FPlatform::uint8 b1, FPlatform::uint8 b2, FPlatform::uint8 b3)
	{
		return (FPlatform::uint32)(b1 << 16) | (FPlatform::uint32)(b2 << 8) | (FPlatform::uint32)b3;
	}

	void UnpackInt24(FPlatform::uint8 & b1, FPlatform::uint8 & b2, FPlatform::uint8 & b3, FPlatform::uint32 v)
	{
		b1 = (v >> 16) & 0xFF;
		b2 = (v >> 8) & 0xFF;
		b3 = v & 0xFF;
	}

	FPlatform::uint32 ReadInt32(void * p, int size)
	{
		switch (size)
		{
		case 1:
			return *GetP<FPlatform::uint8>(p);
		case 2:
			return *GetP<FPlatform::uint16>(p);
		case 3:
		{
			auto * ptr = GetP<FPlatform::uint8>(p);
			return PackInt24(ptr[0], ptr[1], ptr[2]);
		}
		case 4:
			return *GetP<FPlatform::uint32>(p);
		}
		return 0;
	}

	void WriteInt32(void * p, const int size, FPlatform::uint32 value)
	{
		switch (size)
		{
		case 1:
			*GetP<FPlatform::uint8>(p) = (FPlatform::uint8)value;
			break;
		case 2:
			*GetP<FPlatform::uint16>(p) = (FPlatform::uint16)value;
			break;
		case 3:
		{
			auto * ptr = GetP<FPlatform::uint8>(p);
			UnpackInt24(ptr[0], ptr[1], ptr[2], value);
			break;
		}
		case 4:
			*GetP<FPlatform::uint32>(p) = value;
			break;
		}
	}

	//----------------------------------------------------------------

	bool PackInt(FPlatform::uint32 r, FPlatform::uint32 g, FPlatform::uint32 b, FPlatform::uint32 a, PixelFormat format, void * dest)
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

			FPlatform::uint32 value =
				((FixedToFixed(r, 8, pinfo.Rbits) << pinfo.Rshift) & pinfo.Rmask) |
				((FixedToFixed(g, 8, pinfo.Gbits) << pinfo.Gshift) & pinfo.Gmask) |
				((FixedToFixed(b, 8, pinfo.Bbits) << pinfo.Bshift) & pinfo.Bmask) |
				((FixedToFixed(a, 8, pinfo.Abits) << pinfo.Ashift) & pinfo.Amask);

			WriteInt32(dest, pinfo.Size, value);
			return true;
		}
		case PixelFormat::RGBA16:
			GetP<FPlatform::uint16>(dest)[3] = a;
		case PixelFormat::RGB16:
			GetP<FPlatform::uint16>(dest)[0] = r;
			GetP<FPlatform::uint16>(dest)[1] = g;
			GetP<FPlatform::uint16>(dest)[2] = b;
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

	void Pixels::PackI(FPlatform::uint32 r, FPlatform::uint32 g, FPlatform::uint32 b, FPlatform::uint32 a, PixelFormat format, void * dest)
	{
		if (!PackInt(r, g, b, a, format, dest))
			PackFloat(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f, format, dest);
	}

	void Pixels::PackF(float r, float g, float b, float a, PixelFormat format, void * dest)
	{
		if (!PackFloat(r, g, b, a, format, dest))
		{
			const PixelIntPackInfo & pinfo = GetPixelIntPackInfo(format);

			FPlatform::uint32 ir = FloatToFixed(r, pinfo.Rbits);
			FPlatform::uint32 ig = FloatToFixed(g, pinfo.Gbits);
			FPlatform::uint32 ib = FloatToFixed(b, pinfo.Bbits);
			FPlatform::uint32 ia = FloatToFixed(a, pinfo.Abits);
			PackInt(ir, ig, ib, ia, format, dest);
		}
	}

	//-------------------------------------------------------------------------

	bool UnpackInt(FPlatform::uint32 & r, FPlatform::uint32 & g, FPlatform::uint32 & b, FPlatform::uint32 & a, PixelFormat format, void * src)
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

			const FPlatform::uint32 value = ReadInt32(src, pinfo.Size);
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
			a = GetP<FPlatform::uint16>(src)[3];
		case PixelFormat::RGB16:
			r = GetP<FPlatform::uint16>(src)[0];
			g = GetP<FPlatform::uint16>(src)[1];
			b = GetP<FPlatform::uint16>(src)[2];
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

	void Pixels::UnpackI(FPlatform::uint32 & r, FPlatform::uint32 & g, FPlatform::uint32 & b, FPlatform::uint32 & a, PixelFormat format, void * src)
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
			FPlatform::uint32 ir, ig, ib, ia;
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

	inline FPlatform::uint32 TrueBits(FPlatform::uint8 n)
	{
		return ((FPlatform::uint64)1 << n) - 1;
	}

	inline FPlatform::uint32 FloatToFixed(float value, FPlatform::uint8 bits)
	{
		if (value <= 0.0f) return 0;
		else if (value >= 1.0f) return TrueBits(bits);
		return (FPlatform::uint32)(value * ((FPlatform::uint64)1 << bits));
	}

	inline float FixedToFloat(FPlatform::uint32 value, FPlatform::uint8 bits)
	{
		if (bits)
			return (float)value / (float)TrueBits(bits);
		return 0.0;
	}

	// Convert N bit colour channel value to P bits.
	inline FPlatform::uint32 FixedToFixed(FPlatform::uint32 value, FPlatform::uint8 n, FPlatform::uint8 p)
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
				auto k = ((FPlatform::uint64)1 << p) / maxN;
				value = (FPlatform::uint32)(value * k);
			}
		}
		return value;
	}
}