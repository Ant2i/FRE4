#pragma once

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
}