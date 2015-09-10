#pragma once

#include "FPlatform.h"

#define DEFINE_PIXEL_FORMAT(arr, format, sizeX, sizeY, bytes, num) arr[(int)EPixelFormat::format] = {"format", sizeX, sizeY, bytes, num};

namespace FRE
{
	enum class EPixelFormat : unsigned char
	{
		Unknown,
		A8,
		R8,
		R16,
		R16F,
		R16UI,
		R16SI,
		R32F,
		R32UI,
		R32SI,
		RG8,
		RG16,
		RG16F,
		RG32F,
		RGB16F,
		R11G11B10F,
		BGRA8,
		RGBA8,
		RGBA16,
		RGBA16UI,
		RGBA16SI,
		RGBA16F,
		BGRA32F,
		RGBA32F,
		R10G10B10A2F,
		DepthStencil,
		Depth,
		DXT1,
		DXT3,
		DXT5,
		BC4,
		BC5,
		PVRTC2,
		PVRTC4,
		X24G8
	};

	struct PixelFormatInfo
	{
		const char * Name;
		uint32_t CompressBlockSizeX;
		uint32_t CompressBlockSizeY;
		uint32_t PixelBlockBytes;
		uint32_t NumComponentByPixel;
	};

	struct InitializePixelFormat
	{
	public:
		InitializePixelFormat()
		{
			auto & p = PixelFormats;
			DEFINE_PIXEL_FORMAT(p, Unknown,			0, 0, 0, 0);
			DEFINE_PIXEL_FORMAT(p, A8,				1, 1, 1, 1);
			DEFINE_PIXEL_FORMAT(p, R8,				1, 1, 1, 1);
			DEFINE_PIXEL_FORMAT(p, R16,				1, 1, 2, 1);
			DEFINE_PIXEL_FORMAT(p, R16F,			1, 1, 2, 1);
			DEFINE_PIXEL_FORMAT(p, R16UI,			1, 1, 2, 1);
			DEFINE_PIXEL_FORMAT(p, R16SI,			1, 1, 2, 1);
			DEFINE_PIXEL_FORMAT(p, R32F,			1, 1, 4, 1);
			DEFINE_PIXEL_FORMAT(p, R32UI,			1, 1, 4, 1);
			DEFINE_PIXEL_FORMAT(p, R32SI,			1, 1, 4, 1);
			DEFINE_PIXEL_FORMAT(p, RG8,				1, 1, 2, 2);
			DEFINE_PIXEL_FORMAT(p, RG16,			1, 1, 4, 2);
			DEFINE_PIXEL_FORMAT(p, RG16F,			1, 1, 4, 2);
			DEFINE_PIXEL_FORMAT(p, RG32F,			1, 1, 8, 2);
			DEFINE_PIXEL_FORMAT(p, RGB16F,			1, 1, 6, 3);
			DEFINE_PIXEL_FORMAT(p, R11G11B10F,		1, 1, 4, 3);
			DEFINE_PIXEL_FORMAT(p, BGRA8,			1, 1, 4, 4);
			DEFINE_PIXEL_FORMAT(p, RGBA8,			1, 1, 4, 4);
			DEFINE_PIXEL_FORMAT(p, RGBA16,			1, 1, 8, 4);
			DEFINE_PIXEL_FORMAT(p, RGBA16UI,		1, 1, 8, 4);
			DEFINE_PIXEL_FORMAT(p, RGBA16SI,		1, 1, 8, 4);
			DEFINE_PIXEL_FORMAT(p, RGBA16F,			1, 1, 8, 4);
			DEFINE_PIXEL_FORMAT(p, BGRA32F,			1, 1, 16, 4);
			DEFINE_PIXEL_FORMAT(p, RGBA32F,			1, 1, 16, 4);
			DEFINE_PIXEL_FORMAT(p, R10G10B10A2F,	1, 1, 4, 4);
			DEFINE_PIXEL_FORMAT(p, DepthStencil,	1, 1, 0, 1);
			DEFINE_PIXEL_FORMAT(p, Depth,			1, 1, 4, 1);
			DEFINE_PIXEL_FORMAT(p, DXT1,			4, 4, 8, 3);
			DEFINE_PIXEL_FORMAT(p, DXT3,			4, 4, 16, 4);
			DEFINE_PIXEL_FORMAT(p, DXT5,			4, 4, 16, 4);
			DEFINE_PIXEL_FORMAT(p, BC4,				4, 4, 8, 1);
			DEFINE_PIXEL_FORMAT(p, BC5,				4, 4, 16, 2);
			DEFINE_PIXEL_FORMAT(p, PVRTC2,			8, 4, 8, 4);
			DEFINE_PIXEL_FORMAT(p, PVRTC4,			4, 4, 8, 4);
			DEFINE_PIXEL_FORMAT(p, X24G8,			1, 1, 1, 1);
		}

		enum
		{
			NumFormats = 50
		};

		PixelFormatInfo PixelFormats[NumFormats];
	};
}