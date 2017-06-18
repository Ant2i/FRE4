#include "OpenGLPixelFormat.h"
#include <cstring>

#define GLPDFormat(eFormat, internalFormat, internalFormatSRGB, format, type, compress)\
	GLFormat[(int)eFormat] = { internalFormat, internalFormatSRGB, format, type, compress }

namespace FRE
{
	OpenGLPixelDataFormat GLFormat[InitializePixelFormat::NumFormats];

	void InitGLPixelData()
	{
		memset(GLFormat, 0, sizeof(GLFormat));

		GLPDFormat(EPixelFormat::Unknown,		GL_NONE,				GL_NONE,			GL_NONE,			GL_NONE, false);
		GLPDFormat(EPixelFormat::A8,			GL_R8,					GL_NONE,			GL_RED,				GL_UNSIGNED_BYTE, false);
		GLPDFormat(EPixelFormat::R8,			GL_R8,					GL_SRGB8,			GL_RED,				GL_UNSIGNED_BYTE, false);
		GLPDFormat(EPixelFormat::R16,			GL_R16,					GL_NONE,			GL_RED,				GL_UNSIGNED_SHORT, false);
		GLPDFormat(EPixelFormat::R16F,			GL_R16F,				GL_NONE,			GL_RED,				GL_HALF_FLOAT, false);
		GLPDFormat(EPixelFormat::R16UI,			GL_R16UI,				GL_NONE,			GL_RED,				GL_UNSIGNED_SHORT, false);
		GLPDFormat(EPixelFormat::R16SI,			GL_R16I,				GL_NONE,			GL_RED,				GL_SHORT, false);
		GLPDFormat(EPixelFormat::R32F,			GL_R32F,				GL_NONE,			GL_RED,				GL_FLOAT, false);
		GLPDFormat(EPixelFormat::R32UI,			GL_R32UI,				GL_NONE,			GL_RED,				GL_UNSIGNED_INT, false);
		GLPDFormat(EPixelFormat::R32SI,			GL_R32I,				GL_NONE,			GL_RED,				GL_INT, false);
		GLPDFormat(EPixelFormat::RG8,			GL_RG8,					GL_NONE,			GL_RG,				GL_UNSIGNED_BYTE, false);
		GLPDFormat(EPixelFormat::RG16,			GL_RG16,				GL_NONE,			GL_RG,				GL_UNSIGNED_SHORT, false);
		GLPDFormat(EPixelFormat::RG16F,			GL_RG16F,				GL_NONE,			GL_RG,				GL_HALF_FLOAT, false);
		GLPDFormat(EPixelFormat::RG32F,			GL_RG32F,				GL_NONE,			GL_RG,				GL_FLOAT, false);
		GLPDFormat(EPixelFormat::RGB16F,		GL_RGB16F,				GL_NONE,			GL_RGB,				GL_HALF_FLOAT, false);
		GLPDFormat(EPixelFormat::R11G11B10F,	GL_R11F_G11F_B10F,		GL_R11F_G11F_B10F,	GL_RGB,				GL_UNSIGNED_INT_10F_11F_11F_REV, false);
		GLPDFormat(EPixelFormat::BGRA8,			GL_RGBA8,				GL_SRGB8_ALPHA8,	GL_BGRA,			GL_UNSIGNED_INT_8_8_8_8_REV, false);
		GLPDFormat(EPixelFormat::RGBA8,			GL_RGBA8,				GL_SRGB8_ALPHA8,	GL_BGRA,			GL_UNSIGNED_INT_8_8_8_8_REV, false);
		GLPDFormat(EPixelFormat::RGBA16,		GL_RGBA16,				GL_RGBA16,			GL_RGBA,			GL_UNSIGNED_SHORT, false);
		GLPDFormat(EPixelFormat::RGBA16UI,		GL_RGBA16UI,			GL_NONE,			GL_RGBA,			GL_UNSIGNED_SHORT, false);
		GLPDFormat(EPixelFormat::RGBA16SI,		GL_RGBA16I,				GL_NONE,			GL_RGBA,			GL_UNSIGNED_SHORT, false);
		GLPDFormat(EPixelFormat::RGBA16F,		GL_RGBA16F,				GL_RGBA16F,			GL_RGBA,			GL_HALF_FLOAT, false);
		GLPDFormat(EPixelFormat::BGRA32F,		GL_RGBA32F,				GL_RGBA32F,			GL_BGRA,			GL_FLOAT, false);
		GLPDFormat(EPixelFormat::RGBA32F,		GL_RGBA32F,				GL_RGBA32F,			GL_RGBA,			GL_FLOAT, false);
		GLPDFormat(EPixelFormat::R10G10B10A2F,	GL_RGB10_A2,			GL_RGB10_A2,		GL_RGBA,			GL_UNSIGNED_INT_2_10_10_10_REV, false);
		GLPDFormat(EPixelFormat::DepthStencil,	GL_DEPTH24_STENCIL8,	GL_NONE,			GL_DEPTH_STENCIL,	GL_UNSIGNED_INT_24_8, false);
		GLPDFormat(EPixelFormat::Depth,			GL_DEPTH_COMPONENT16,	GL_NONE,			GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, false);

		if (FOpenGL::GetCapability().SupportDXT)
		{
			if (FOpenGL::GetCapability().SupportSRGB)
			{
				GLPDFormat(EPixelFormat::DXT1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT, GL_RGBA, GL_UNSIGNED_BYTE, true);
				GLPDFormat(EPixelFormat::DXT3, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT, GL_RGBA, GL_UNSIGNED_BYTE, true);
				GLPDFormat(EPixelFormat::DXT5, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT, GL_RGBA, GL_UNSIGNED_BYTE, true);
			}
			else
			{
				GLPDFormat(EPixelFormat::DXT1, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_RGBA, GL_UNSIGNED_BYTE, true);
				GLPDFormat(EPixelFormat::DXT3, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_RGBA, GL_UNSIGNED_BYTE, true);
				GLPDFormat(EPixelFormat::DXT5, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_RGBA, GL_UNSIGNED_BYTE, true);
			}
		}

		if (FOpenGL::GetCapability().SupportPVRTC)
		{
			GLPDFormat(EPixelFormat::PVRTC2, GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG, GL_RGBA, GL_UNSIGNED_BYTE, true);
			GLPDFormat(EPixelFormat::PVRTC4, GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG, GL_RGBA, GL_UNSIGNED_BYTE, true);
		}

		if (FOpenGL::GetCapability().SupportRGTC)
		{
			GLPDFormat(EPixelFormat::BC4, GL_COMPRESSED_RED_RGTC1, GL_COMPRESSED_RED_RGTC1, GL_RED, GL_UNSIGNED_BYTE, true);
			GLPDFormat(EPixelFormat::BC5, GL_COMPRESSED_RG_RGTC2, GL_COMPRESSED_RG_RGTC2, GL_RG, GL_UNSIGNED_BYTE, true);
		}
	}

	const OpenGLPixelDataFormat & GetGLPixelDataFormat(EPixelFormat format)
	{
        static bool init = false;
        if (!init)
        {
            InitGLPixelData();
            init = true;
        }
		return GLFormat[(int)format];
	}
}
