#pragma once

#include "Codec.h"

struct FIBITMAP;
struct FIMEMORY;

namespace Image
{
	class FreeImageCodec : public Codec
	{
	public:
		FreeImageCodec(const std::string & type, unsigned int fiType);
		virtual ~FreeImageCodec();

		virtual Data Decode(IStream & input) const override;
		virtual std::unique_ptr<IStream> Encode(const Data & data) const override;

		virtual std::string GetType() const override;

		virtual std::string MagicNumberToFileExt(const char * magicNumberPtr, size_t maxbytes) const override;

		static void Startup();
		static void Shutdown();

	private:
		FIBITMAP * LoadBitmap(FIMEMORY *) const;

	private:
		std::string _type;
		unsigned int _freeImageFormat;
	};

}
