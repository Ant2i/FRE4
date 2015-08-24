#include "FormatDesription.h"
#include <cstring>

namespace Image
{
	PixelFormatDescription sPixelFormatDesc[100];

#define PIXEL_FORMA_DECL(format, componentCount, rb, gb, bb, ab, flags){\
	auto & formatDesc = sPixelFormatDesc[(int)format];\
	formatDesc.ComponentCount = componentCount;\
	formatDesc.Flags = flags;\
	formatDesc.Rbits = rb;  formatDesc.Gbits = gb;  formatDesc.Bbits = bb;  formatDesc.Abits = ab;\
		}

#define PIXEL_FORMA_DECL2(format, componentCount, flags) PIXEL_FORMA_DECL(format, componentCount, 0, 0, 0, 0, flags)

	void InitDesc()
	{
		memset(sPixelFormatDesc, 0, sizeof(sPixelFormatDesc));

		PIXEL_FORMA_DECL(PixelFormat::L8, 1,
			8, 0, 0, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::L16, 1,
			8, 0, 0, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::R16, 1,
			8, 0, 0, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::R5G6B5, 3,
			5, 6, 5, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::B5G6R5, 3,
			5, 6, 5, 0,
			PF_RBInvert);
		PIXEL_FORMA_DECL(PixelFormat::RGB8, 3,
			8, 8, 8, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::BGR8, 3,
			8, 8, 8, 0,
			PF_RBInvert);
		PIXEL_FORMA_DECL(PixelFormat::RGBA8, 4,
			8, 8, 8, 8,
			PF_HasAlpha);
		PIXEL_FORMA_DECL(PixelFormat::BGRA8, 4,
			8, 8, 8, 8,
			PF_HasAlpha | PF_RBInvert);
		PIXEL_FORMA_DECL(PixelFormat::RGB16, 3,
			16, 16, 16, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::RGBA16, 4,
			16, 16, 16, 16,
			PF_HasAlpha);
		PIXEL_FORMA_DECL(PixelFormat::R32F, 1,
			32, 0, 0, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::RGB32F, 3,
			32, 32, 32, 0,
			0);
		PIXEL_FORMA_DECL(PixelFormat::RGBA32F, 4,
			32, 32, 32, 32,
			PF_HasAlpha);

		PIXEL_FORMA_DECL2(PixelFormat::DXT1, 3, 0);
		PIXEL_FORMA_DECL2(PixelFormat::DXT2, 4, PF_HasAlpha);
		PIXEL_FORMA_DECL2(PixelFormat::DXT3, 4, PF_HasAlpha);
		PIXEL_FORMA_DECL2(PixelFormat::DXT4, 4, PF_HasAlpha);
		PIXEL_FORMA_DECL2(PixelFormat::DXT5, 4, PF_HasAlpha);
	}

	PixelFormatDescription & GetDescription(PixelFormat format)
	{
		static bool init = false;
		if (!init)
		{
			InitDesc();
			init = true;
		}

		return sPixelFormatDesc[(int)format];
	}
}