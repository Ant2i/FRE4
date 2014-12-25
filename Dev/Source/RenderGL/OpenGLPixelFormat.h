#pragma once

#include "FPixelFormats.h"
#include "OpenGLBase.h"

namespace FRE
{
	struct OpenGLPixelDataFormat
	{
		GLenum InternalFormat;
		GLenum InternalFormatSRGB;
		GLenum Format;
		GLenum Type;
		bool Compressed;
	};

	static const OpenGLPixelDataFormat & GetGLPixelDataFormat(EPixelFormat format);
}