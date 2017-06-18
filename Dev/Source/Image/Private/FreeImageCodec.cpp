#include "FreeImageCodec.h"
#include "FreImageMemoryStream.h"

#include "FreeImage.h"
#include "CodecManager.h"

#include <vector>

namespace Image
{
	std::vector<std::string> Split(const std::string & input, const std::string & del);
	MemoryStream CopyStream(IStream & stream);

	//-------------------------------------------------------------------------

	void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char * message)
	{
		const char * typeName = FreeImage_GetFormatFromFIF(fif);
	}

	FreeImageCodec::FreeImageCodec(const std::string & type, unsigned int fiFormat) : 
		_type(type),
		_freeImageFormat(fiFormat)
	{

	}

	FreeImageCodec::~FreeImageCodec()
	{

	}
	
	FIBITMAP * FreeImageCodec::LoadBitmap(FIMEMORY * memory) const
	{
		FIBITMAP * bitmap = FreeImage_LoadFromMemory((FREE_IMAGE_FORMAT)_freeImageFormat, memory);

		const FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(bitmap);
		if (FIT_BITMAP == imageType)
		{
			const unsigned bpp = FreeImage_GetBPP(bitmap);
			const FREE_IMAGE_COLOR_TYPE colourType = FreeImage_GetColorType(bitmap);

			if (colourType == FIC_MINISWHITE || colourType == FIC_MINISBLACK)
			{
				FIBITMAP * newBitmap = FreeImage_ConvertToGreyscale(bitmap);
				FreeImage_Unload(bitmap);
				bitmap = newBitmap;
			}
			else if (bpp < 24 || colourType == FIC_PALETTE || colourType == FIC_CMYK)
			{
				FIBITMAP * newBitmap = FreeImage_ConvertTo24Bits(bitmap);
				FreeImage_Unload(bitmap);
				bitmap = newBitmap;
			}
		}
		return bitmap;
	}
	
	PixelFormat ConvertToPixelFormat(FREE_IMAGE_TYPE fiType, int bpp)
	{
		switch (fiType)
		{
		case FIT_BITMAP:
			switch (bpp)
			{
			case 8:
				return PixelFormat::L8;
			case 16:
				return PixelFormat::L16;
			case 24:
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				return PixelFormat::RGB8;
#else
				return PixelFormat::BGR8;
#endif
			case 32:
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				return PixelFormat::RGBA8;
#else
				return PixelFormat::BGRA8;
#endif
			};
			break;
		case FIT_UINT16:
		case FIT_INT16:	
			return PixelFormat::R16;
		case FIT_FLOAT: 
			return PixelFormat::R32F;
		case FIT_RGB16: 
			return PixelFormat::RGB16;
		case FIT_RGBA16: 
			return PixelFormat::RGBA16;
		case FIT_RGBF: 
			return PixelFormat::RGB32F;
		case FIT_RGBAF:	
			return PixelFormat::RGBA32F;
		};

		return PixelFormat::Unknown;
	}

	FREE_IMAGE_TYPE ConvertToFiType(PixelFormat pf, int bpp)
	{
		switch (pf)
		{
		case PixelFormat::L8:
		case PixelFormat::L16:
		case PixelFormat::RGB8:
		case PixelFormat::BGR8:
		case PixelFormat::RGBA8:
		case PixelFormat::BGRA8:
			return FIT_BITMAP;
		case PixelFormat::R16:
			return FIT_INT16;
		case PixelFormat::RGB16:
			return FIT_RGB16;
		case PixelFormat::RGBA16:
			return FIT_RGBA16;
		case PixelFormat::R32F:	
			return FIT_FLOAT;
		case PixelFormat::RGB32F: 
			return FIT_RGBF;
		case PixelFormat::RGBA32F:
			return FIT_RGBAF;
		}

		return FIT_UNKNOWN;
	}

	Data FreeImageCodec::Decode(IStream & input) const
	{
		Data output;

		auto stream = CopyStream(input);
		FIMEMORY * memory = FreeImage_OpenMemory(reinterpret_cast<BYTE *>(stream.GetPtr()), static_cast<DWORD>(stream.GetSize()));
		FIBITMAP * bitmap = LoadBitmap(memory);

		if (!bitmap)
			return output;

		output.Depth = 1;
		output.Width = FreeImage_GetWidth(bitmap);
		output.Height = FreeImage_GetHeight(bitmap);
		output.MipMaps = 0;
		output.Flags = 0;

		output.DpmX = FreeImage_GetDotsPerMeterX(bitmap);
		output.DpmY = FreeImage_GetDotsPerMeterY(bitmap);

		output.Format = ConvertToPixelFormat(FreeImage_GetImageType(bitmap), FreeImage_GetBPP(bitmap));

		unsigned srcPitch = FreeImage_GetPitch(bitmap);
		BYTE * srcBits = FreeImage_GetBits(bitmap);
		
		size_t dstPitch = output.Width * Pixels::GetNumElemBytes(output.Format);
		output.Bits.resize((size_t)dstPitch * output.Height);
		
		const size_t copyPitch = dstPitch < srcPitch ? dstPitch : srcPitch;

		BYTE * pSrc = nullptr;
		auto * pDst = output.Bits.data();
		for (size_t h = 0; h < output.Height; ++h)
		{
			pSrc = srcBits + (output.Height - h - 1) * srcPitch;
			memcpy(pDst, pSrc, copyPitch);
			pDst += dstPitch;
		}

		FreeImage_Unload(bitmap);
		FreeImage_CloseMemory(memory);

		return output;
	}

	FIBITMAP * GetEncodeBitmap(const Data & iData, FREE_IMAGE_FORMAT fiFormat)
	{
		FIBITMAP * bitmap = nullptr;

		PixelFormat pixelFormat = iData.Format;
		int bpp = (int)Pixels::GetNumElemBits(pixelFormat);
		FREE_IMAGE_TYPE imageType = ConvertToFiType(pixelFormat, bpp);

		if (FreeImage_FIFSupportsExportType(fiFormat, imageType) &
			FreeImage_FIFSupportsExportBPP(fiFormat, bpp))
		{
			unsigned redMask = 0x0;
			unsigned greenMask = 0x0;
			unsigned blueMask = 0x0;

#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
			if (pixelFormat == PixelFormat::BGR8 || pixelFormat == PixelFormat::BGRA8)
			{
				redMask = 0x0000FF;
				greenMask = 0x00FF00;
				blueMask = 0xFF0000;
			}
#endif

			bitmap = FreeImage_AllocateT(imageType, static_cast<int>(iData.Width), static_cast<int>(iData.Height), bpp, redMask, greenMask, blueMask);

			if (!bitmap)
			{
				//	"FreeImage_AllocateT failed - possibly out of memory. "
			}

			size_t dstPitch = FreeImage_GetPitch(bitmap);
			size_t srcPitch = iData.Width * Pixels::GetNumElemBytes(pixelFormat);

			const auto * srcData = iData.Bits.data();
			unsigned char * pDst = FreeImage_GetBits(bitmap);
			for (size_t h = 0; h < iData.Height; ++h)
			{
				const auto * pSrc = srcData + (iData.Height - h - 1) * srcPitch;
				memcpy(pDst, pSrc, srcPitch);
				pDst += dstPitch;
			}
		}

		return bitmap;
	}

	std::unique_ptr<IStream> FreeImageCodec::Encode(const Data & iData) const
	{
		FIBITMAP * bitmap = GetEncodeBitmap(iData, (FREE_IMAGE_FORMAT)_freeImageFormat);

		FIMEMORY* memory = FreeImage_OpenMemory();
		FreeImage_SaveToMemory((FREE_IMAGE_FORMAT)_freeImageFormat, bitmap, memory);
		
		BYTE * data = nullptr;
		DWORD size = 0;
		FreeImage_AcquireMemory(memory, &data, &size);

		MemoryStream * stream = new MemoryStream(size);
		memcpy(stream->GetPtr(), data, size);
		
		FreeImage_CloseMemory(memory);
		FreeImage_Unload(bitmap);

		return std::unique_ptr<IStream>(stream);
	}

	std::string FreeImageCodec::GetType() const
	{
		return _type;
	}

	std::string FreeImageCodec::MagicNumberToFileExt(const char * magicNumberPtr, size_t maxbytes) const
	{
		FIMEMORY * fiMemory = FreeImage_OpenMemory((BYTE*)magicNumberPtr, static_cast<DWORD>(maxbytes));
		FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromMemory(fiMemory, (int)maxbytes);
		FreeImage_CloseMemory(fiMemory);

		if (fif != FIF_UNKNOWN)
			return FreeImage_GetFormatFromFIF(fif);

		return "";
	}

	void FreeImageCodec::Startup()
	{
		FreeImage_Initialise(false);

		for (int i = 0; i < FreeImage_GetFIFCount(); ++i)
		{
			if ((FREE_IMAGE_FORMAT)i == FIF_DDS)
				continue;

			const char * extList = FreeImage_GetFIFExtensionList((FREE_IMAGE_FORMAT)i);
			for (std::string & type : Split(std::string(extList), ","))
			{
				if (!CodecManager::IsCodecRegistered(type))
					CodecManager::RegisterCodec(CodecP(new FreeImageCodec(type, i)));
			}
		}

		FreeImage_SetOutputMessage(FreeImageErrorHandler);
	}
			
	void FreeImageCodec::Shutdown()
	{
		FreeImage_DeInitialise();
	}

	//----------------------------------------------------------------------------

	std::vector<std::string> Split(const std::string & input, const std::string & del)
	{
		std::vector<std::string> res;

		size_t begin = 0;
		size_t end = 0;
		std::string token;
		while ((end = input.find(del, begin)) != std::string::npos)
		{
			token = input.substr(begin, end - begin);
			res.push_back(token);
			std::swap(begin, end);
			++begin;
		}

		if (begin < input.size())
			res.push_back(input.substr(begin, input.size() - begin));

		return std::move(res);
	}

	MemoryStream CopyStream( IStream & stream)
	{
		MemoryStream memoryStream(0);

		static const size_t BufferSize = 1024;
		char rawBuffer[BufferSize];

		while (!stream.AtEnd())
		{
			const size_t bytesRead = stream.Read(rawBuffer, sizeof(rawBuffer));
			if (bytesRead)
				memoryStream.Write(rawBuffer, bytesRead);
		}

		return std::move(memoryStream);
	}

}
