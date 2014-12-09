#pragma once

namespace FRE
{
	enum class EPixelFormat : unsigned char
	{
		Unknown = 0,
		//ABGR32F
		A32B32G32R32F = 1,
		//BGRA8
		B8G8R8A8 = 2,
		//R8
		G8 = 3,
		//R16
		G16 = 4,
		DXT1 = 5,
		DXT3 = 6,
		DXT5 = 7,
		//RGB16F
		FloatRGB = 9,
		//RGBA16F
		FloatRGBA = 10,
		DepthStencil = 11,
		Depth = 12,
		//R32F
		R32_FLOAT = 13,
		//RG16
		G16R16 = 14,
		//RG16F
		G16R16F = 15,
		//RG32F
		G32R32F = 17,
		//R10G10B10A2
		A2B10G10R10 = 18,
		//RGBA16
		A16B16G16R16 = 19,
		//
		D24 = 20,
		//
		R16F = 21,
		BC5 = 23,
		//RG8_NORM
		V8U8 = 24,
		//R11G11B10F
		FloatR11G11B10 = 26,
		A8 = 27,
		R32UI = 28,
		R32I = 29,
		PVRTC2 = 30,
		PVRTC4 = 31,
		R16_UINT = 32,
		R16_SINT = 33,
		R16G16B16A16_UINT = 34,
		R16G16B16A16_SINT = 35,
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
}