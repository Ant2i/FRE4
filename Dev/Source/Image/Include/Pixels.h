#pragma once

#include "Decl.h"
#include <cstring>

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

	class IMAGE_API Pixels
	{
	public:
		static size_t GetNumElemBytes(PixelFormat format);
		static size_t GetNumElemBits(PixelFormat format)
		{
			return GetNumElemBytes(format) * 8;
		}

		static size_t GetComponentCount(PixelFormat format);

		static size_t GetMemorySize(PixelFormat format, size_t width, size_t height, size_t depth);
		static size_t CalculateSize(PixelFormat format, size_t width, size_t height, size_t depth, size_t mipmaps);

		static bool HasAlpha(PixelFormat format);
		static bool IsCompressed(PixelFormat format);
		static bool IsAccessible(PixelFormat format);
		
		static void PackI(FPlatform::uint32 r, FPlatform::uint32 g, FPlatform::uint32 b, FPlatform::uint32 a, PixelFormat format, void * dest);
		static void PackF(float r, float g, float b, float a, PixelFormat format, void * dest);

		static void UnpackI(FPlatform::uint32 & r, FPlatform::uint32 & g, FPlatform::uint32 & b, FPlatform::uint32 & a, PixelFormat format, void * src);
		static void UnpackF(float & r, float & g, float & b, float & a, PixelFormat format, void * src);

	public:
		static unsigned int GetFlags(PixelFormat format);
	};
}