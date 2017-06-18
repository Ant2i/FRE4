//#include "TxPixels.h"
//#include "FormatDesription.h"
//
//namespace Image
//{
//	size_t Pixels::GetNumElemBytes(PixelFormat format)
//	{
//		return GetDescription(format).GetSize();
//	}
//
//	size_t Pixels::GetMemorySize(PixelFormat format, size_t width, size_t height, size_t depth)
//	{
//		size_t size = 0;
//
//		if (IsCompressed(format))
//		{
//			switch (format)
//			{
//			case PixelFormat::DXT1:
//				size =((width + 3) / 4)*((height + 3) / 4) * 8;
//				break;
//			case PixelFormat::DXT2:
//			case PixelFormat::DXT3:
//			case PixelFormat::DXT4:
//			case PixelFormat::DXT5:
//				size = ((width + 3) / 4)*((height + 3) / 4) * 16;
//				break;
//			}
//		}
//		else
//		{
//			size = width * height * GetNumElemBytes(format);
//		}
//
//		return  size * depth;
//	}
//	
//	size_t Pixels::CalculateSize(PixelFormat format, size_t width, size_t height, size_t depth, size_t mipmaps)
//	{
//		size_t size = 0;
//		for (size_t mip = 0; mip <= mipmaps; ++mip)
//		{
//			size += GetMemorySize(format, width, height, depth);
//			if (width != 1) width /= 2;
//			if (height != 1) height /= 2;
//			if (depth != 1) depth /= 2;
//		}
//		return size;
//	}
//
//	unsigned int Pixels::GetFlags(PixelFormat format)
//	{
//		return GetDescription(format).Flags;
//	}
//
//	bool Pixels::HasAlpha(PixelFormat format)
//	{
//		return (GetFlags(format) | Flags::PF_HasAlpha) != 0;
//	}
//
//	bool Pixels::IsCompressed(PixelFormat format)
//	{
//		return format == PixelFormat::DXT1 ||
//			   format == PixelFormat::DXT2 ||
//			   format == PixelFormat::DXT3 ||
//			   format == PixelFormat::DXT4 ||
//			   format == PixelFormat::DXT5;
//	}
//
//	bool Pixels::IsAccessible(PixelFormat format)
//	{
//		if (format == PixelFormat::Unknown)
//			return false;
//		return !IsCompressed(format);
//	}
//
//	size_t Pixels::GetComponentCount(PixelFormat format)
//	{
//		return GetDescription(format).ComponentCount;
//	}
//}
