#include "FreImage.h"
#include "FreImageMemoryStream.h"

#include "FreeImageCodec.h"
#include "CodecManager.h"

#include  <algorithm>

namespace Image
{
	class ImageData
	{
	public:
		ImageData();
		ImageData(const Data & d);
		ImageData(const ImageData & data);

		unsigned char * Bits()
		{
			return data.Bits.empty() ? nullptr : data.Bits.data();
		}

		static ImageData * Create(size_t width, size_t height, size_t depth, PixelFormat format);

	public:
		Data data;
	};

	ImageData::ImageData()
	{

	}

	ImageData::ImageData(const Data & d) :
		data(d)
	{

	}

	ImageData::ImageData(const ImageData & other) : 
		data(other.data)
	{

	}

	ImageData * ImageData::Create(size_t width, size_t height, size_t depth, PixelFormat format)
	{
		ImageData * imageData(new ImageData());
		imageData->data.Width = width;
		imageData->data.Height = height;
		imageData->data.Depth = 1;
		imageData->data.Format = format;
		imageData->data.Bits.resize(width *  height * Pixels::GetNumElemBytes(format));
		return imageData;
	}

	//-------------------------------------------------------------------------

	Image2D::Image2D() : 
		_p(nullptr)
	{
		
	}

	Image2D::Image2D(size_t width, size_t height, PixelFormat format) :
		_p(ImageData::Create(width, height, 1, format))
	{
		
	}

	Image2D::Image2D(const Image2D & image) :
		_p(image._p ? new ImageData(*image._p) : nullptr)
	{
		
	}

	Image2D::Image2D(Image2D && image) : 
		_p(image._p)
	{
		image._p = nullptr;
	}

	Image2D::~Image2D()
	{
		ResetP(nullptr);
	}

	void Image2D::ResetP(ImageData * p)
	{
		if (_p)
			delete _p;
		_p = p;
	}

	Codec * FindCodec(const std::string & type)
	{
		Codec * retCodec = nullptr;
		if (!type.empty())
			retCodec = CodecManager::GetCodec(type);
		return retCodec;
	}

	Codec * FindCodec(IStream & stream, const std::string & type)
	{
		Codec * retCodec = FindCodec(type);
		if (!retCodec)
		{
			const int magicSize = 32;
			char magicBuf[magicSize];
			memset(magicBuf, 0, magicSize);
			stream.Read(magicBuf, magicSize);
			retCodec = CodecManager::GetCodec(magicBuf, magicSize);

			stream.Skip(-magicSize);
		}

		return retCodec;
	}

	void Image2D::Load(IStream & stream, const char * type, int flags)
	{
		Codec * codec = FindCodec(stream, type);
		if (codec)
		{
			const Data & data = codec->Decode(stream);
			ResetP(new ImageData(data));
		}
	}

	void Image2D::Save(IStream & stream, const char * type, int flags)
	{
		Codec * codec = FindCodec(type);
		if (codec)
		{
			std::unique_ptr<IStream> outputStream = _p ? codec->Encode(_p->data) : nullptr;
			if (outputStream)
			{
				char buffer[1024];
				while (!outputStream->AtEnd())
				{
					auto readSize = outputStream->Read(buffer, sizeof(buffer));
					stream.Write(buffer, readSize);
				}
			}
		}
	}

	size_t Image2D::Width() const
	{
		return _p ? _p->data.Width : 0;
	}

	size_t Image2D::Height() const
	{
		return _p ? _p->data.Height : 0;
	}

	PixelFormat Image2D::Format() const
	{
		return _p ? _p->data.Format : PixelFormat::Unknown;
	}

	unsigned char * Image2D::Bits()
	{
		return _p ? _p->Bits() : nullptr;
	}

	const unsigned char * Image2D::Bits() const
	{
		return _p ? _p->Bits() : nullptr;
	}

	void * Image2D::GetPixelPtr(size_t x, size_t y) const
	{
		if (_p)
		{
			size_t offset = (x + _p->data.Width * y) * Pixels::GetNumElemBytes(_p->data.Format);
			return _p->Bits() + offset;
		}
		return nullptr;
	}

	void Image2D::SetPixel(size_t x, size_t y, const Color & c)
	{
		void * pixel = GetPixelPtr(x, y);
		if (pixel)
			Pixels::PackI(c.R, c.G, c.B, c.A, Format(), pixel);
	}

	void Image2D::GetPixel(size_t x, size_t y, Color & c) const
	{
		void * pixel = GetPixelPtr(x, y);
		if (pixel)
		{
			unsigned int r, g, b, a;
			Pixels::UnpackI(r, g, b, a, Format(), pixel);
			c.R = r; 
			c.G = g; 
			c.B = b; 
			c.A = a;
		}
	}

	void Image2D::SetPixel(size_t x, size_t y, const ColorF & c)
	{
		void * pixel = GetPixelPtr(x, y);
		if (pixel)
			Pixels::PackF(c.R, c.G, c.B, c.A, Format(), pixel);
	}

	void Image2D::GetPixel(size_t x, size_t y, ColorF & c) const
	{
		void * pixel = GetPixelPtr(x, y);
		if (pixel)
			Pixels::UnpackF(c.R, c.G, c.B, c.A, Format(), pixel);
	}

	//----------------------------------------------------------------------------

	void Startup()
	{
		FreeImageCodec::Startup();
	}

	void Shutdown()
	{
		FreeImageCodec::Shutdown();
	}
}
