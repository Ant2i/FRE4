#pragma once

namespace FRE
{
	enum class ETextureType : unsigned char
	{
		Unknown = 0,
		Tex2D,
		Tex2DArray,
		Tex3D,
		TexCube
	};

	enum class EPixelFormat : unsigned char
	{
		Unknown = 0,
		A32B32G32R32F = 1,
		B8G8R8A8 = 2,
		G8 = 3,
		G16 = 4,
		DXT1 = 5,
		DXT3 = 6,
		DXT5 = 7,
		UYVY = 8,
		FloatRGB = 9,
		FloatRGBA = 10,
		DepthStencil = 11,
		ShadowDepth = 12,
		R32_FLOAT = 13,
		G16R16 = 14,
		G16R16F = 15,
		G16R16F_FILTER = 16,
		G32R32F = 17,
		A2B10G10R10 = 18,
		A16B16G16R16 = 19,
		D24 = 20,
		R16F = 21,
		R16F_FILTER = 22,
		BC5 = 23,
		V8U8 = 24,
		A1 = 25,
		FloatR11G11B10 = 26,
		A8 = 27,
		R32_UINT = 28,
		R32_SINT = 29,
		PVRTC2 = 30,
		PVRTC4 = 31,
		R16_UINT = 32,
		R16_SINT = 33,
		R16G16B16A16_UINT = 34,
		R16G16B16A16_SINT = 35,
		R5G6B5_UNORM = 36,
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
		ETC2_RGBA = 47,
		MAX = 48,
	};
}