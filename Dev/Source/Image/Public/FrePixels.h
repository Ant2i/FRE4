#pragma once

#include <FreImageDecl.h>
#include <stdint.h>

namespace Image
{
	enum class PixelFormat
	{
		Unknown,
		L8,
		L16,
		R16,
		R5G6B5,
		B5G6R5,
		RGB8,
		BGR8,
		RGBA8,
		BGRA8,
		RGB16,
		RGBA16,
		R32F,
		RGB32F,
		RGBA32F,
		DXT1,
		DXT2,
		DXT3,
		DXT4,
		DXT5
	};

	enum Flags
	{
		PF_HasAlpha = 1,
		PF_RBInvert = 2
	};

	struct PixelFormatDescription
	{
		const char* Name;
		unsigned char ComponentCount;
		unsigned int Flags;
		//
		unsigned char Rbits;
		unsigned char Gbits;
		unsigned char Bbits;
		unsigned char Abits;

		unsigned char GetSize() const
		{
			return (Rbits + Gbits + Bbits + Abits) / 8;
		}
	};

#define PIXEL_STRING(s) #s
#define PIXEL_FORMAT_DECL(format, componentCount, rb, gb, bb, ab, flags) do {\
		PixelFormatDescription& pd = _pixelsDesc[(int)PixelFormat::format];\
		pd.Name = PIXEL_STRING(format); pd.ComponentCount = componentCount; pd.Flags = flags;\
		pd.Rbits = rb, pd.Gbits = gb, pd.Bbits = bb, pd.Abits = ab;\
		} while(false)
#define PIXEL_FORMAT_DECL2(format, componentCount, flags) PIXEL_FORMAT_DECL(format, componentCount, 0, 0, 0, 0, flags)

	class PixelsDescCont
	{
	public:
		PixelsDescCont()
		{
			PIXEL_FORMAT_DECL(Unknown, 0,
				0, 0, 0, 0,
				0);
			PIXEL_FORMAT_DECL(L8, 1,
				8, 0, 0, 0,
				0);
			PIXEL_FORMAT_DECL(L16, 1,
				8, 0, 0, 0,
				0);
			PIXEL_FORMAT_DECL(R16, 1,
				8, 0, 0, 0,
				0);
			PIXEL_FORMAT_DECL(R5G6B5, 3,
				5, 6, 5, 0,
				0);
			PIXEL_FORMAT_DECL(B5G6R5, 3,
				5, 6, 5, 0,
				PF_RBInvert);
			PIXEL_FORMAT_DECL(RGB8, 3,
				8, 8, 8, 0,
				0);
			PIXEL_FORMAT_DECL(BGR8, 3,
				8, 8, 8, 0,
				PF_RBInvert);
			PIXEL_FORMAT_DECL(RGBA8, 4,
				8, 8, 8, 8,
				PF_HasAlpha);
			PIXEL_FORMAT_DECL(BGRA8, 4,
				8, 8, 8, 8,
				PF_HasAlpha | PF_RBInvert);
			PIXEL_FORMAT_DECL(RGB16, 3,
				16, 16, 16, 0,
				0);
			PIXEL_FORMAT_DECL(RGBA16, 4,
				16, 16, 16, 16,
				PF_HasAlpha);
			PIXEL_FORMAT_DECL(R32F, 1,
				32, 0, 0, 0,
				0);
			PIXEL_FORMAT_DECL(RGB32F, 3,
				32, 32, 32, 0,
				0);
			PIXEL_FORMAT_DECL(RGBA32F, 4,
				32, 32, 32, 32,
				PF_HasAlpha);

			PIXEL_FORMAT_DECL2(DXT1, 3, 0);
			PIXEL_FORMAT_DECL2(DXT2, 4, PF_HasAlpha);
			PIXEL_FORMAT_DECL2(DXT3, 4, PF_HasAlpha);
			PIXEL_FORMAT_DECL2(DXT4, 4, PF_HasAlpha);
			PIXEL_FORMAT_DECL2(DXT5, 4, PF_HasAlpha);
		}

		const PixelFormatDescription & GetDescription(PixelFormat format) const
		{
			return _pixelsDesc[(int)format];
		}

	private:
		PixelFormatDescription _pixelsDesc[100];
	};

	//
	class Pixels
	{
	public:
		static const PixelFormatDescription& GetDescription(PixelFormat format)
		{
			static PixelsDescCont sPixelsCont;
			return sPixelsCont.GetDescription(format);
		}

		static size_t GetNumElemBytes(PixelFormat format)
		{
			return GetDescription(format).GetSize();
		}

		static size_t GetNumElemBits(PixelFormat format)
		{
			return GetNumElemBytes(format) * 8;
		}

		static size_t GetComponentCount(PixelFormat format)
		{
			return GetDescription(format).ComponentCount;
		}

		static size_t GetMemorySize(PixelFormat format, size_t width, size_t height, size_t depth)
		{
			size_t size = 0;

			if (IsCompressed(format))
			{
				switch (format)
				{
				case PixelFormat::DXT1:
					size = ((width + 3) / 4)*((height + 3) / 4) * 8;
					break;
				case PixelFormat::DXT2:
				case PixelFormat::DXT3:
				case PixelFormat::DXT4:
				case PixelFormat::DXT5:
					size = ((width + 3) / 4)*((height + 3) / 4) * 16;
					break;
				}
			}
			else
			{
				size = width * height * GetNumElemBytes(format);
			}

			return  size * depth;
		}

		static size_t CalculateSize(PixelFormat format, size_t width, size_t height, size_t depth, size_t mipmaps)
		{
			size_t size = 0;
			for (size_t mip = 0; mip <= mipmaps; ++mip)
			{
				size += GetMemorySize(format, width, height, depth);
				if (width != 1) width /= 2;
				if (height != 1) height /= 2;
				if (depth != 1) depth /= 2;
			}
			return size;
		}

		static bool HasAlpha(PixelFormat format)
		{
			return (GetFlags(format) | Flags::PF_HasAlpha) != 0;
		}

		static bool IsCompressed(PixelFormat format)
		{
			return format == PixelFormat::DXT1 ||
				format == PixelFormat::DXT2 ||
				format == PixelFormat::DXT3 ||
				format == PixelFormat::DXT4 ||
				format == PixelFormat::DXT5;
		}

		static bool IsAccessible(PixelFormat format)
		{
			if (format == PixelFormat::Unknown)
				return false;
			return !IsCompressed(format);
		}
		
		IMAGE_API static void PackI(uint32_t r, uint32_t g, uint32_t b, uint32_t a, PixelFormat format, void * dest);
		IMAGE_API static void PackF(float r, float g, float b, float a, PixelFormat format, void * dest);

		IMAGE_API static void UnpackI(uint32_t & r, uint32_t & g, uint32_t & b, uint32_t & a, PixelFormat format, void * src);
		IMAGE_API static void UnpackF(float & r, float & g, float & b, float & a, PixelFormat format, void * src);

	public:
		static unsigned int GetFlags(PixelFormat format)
		{
			return GetDescription(format).Flags;
		}
	};
}
