#pragma once

namespace FRE
{
	enum class EPixelFormat : unsigned char
	{
		Unknown = 0,
		BGRA32_F = 1,
		BGRA8 = 2,
		R8 = 3,
		R16 = 4,
		DXT1 = 5,
		DXT3 = 6,
		DXT5 = 7,
		RGB16_F = 9,
		RGBA16_F = 10,
		DepthStencil = 11,
		Depth = 12,
		R32_F = 13,
		RG16 = 14,
		RG16_F = 15,
		RG32_F = 17,
		R10G10B10A2 = 18,
		RGBA16 = 19,
		D24 = 20,
		R16F = 21,
		BC5 = 23,
		RG8_NORM = 24,
		R11G11B10_F = 26,
		A8 = 27,
		R32_U = 28,
		R32_S = 29,
		PVRTC2 = 30,
		PVRTC4 = 31,
		R16_U = 32,
		R16_S = 33,
		R16G16B16A16_U = 34,
		R16G16B16A16_S = 35,
		R8G8B8A8 = 37,
		A8R8G8B8 = 38,
		BC4 = 39,
		R8G8 = 40,
		ATC_RGB = 41,
		ATC_RGBA_E = 42,
		ATC_RGBA_I = 43,
		X24_G8 = 44,
		ETC1 = 45,
		ETC2_RGB = 46,
		ETC2_RGBA = 47
	};

	struct PixelFormatInfo
	{
		const char * Name;
		uint32 PixelBlockSizeX;
		uint32 PixelBlockSizeY;
		uint32 PixelBlockBytes;

		uint32 NumComponentByPixel;
		uint32 PlatformFormat;
	};
}