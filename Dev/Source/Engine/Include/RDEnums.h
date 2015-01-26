#pragma once

namespace FRE
{
	enum class EShaderPlatform
	{
		OGL_SM4,
		OGL_SM5,
		OGL_ES2,
		OGL_ES3,
		D3D_SM4,
		D3D_SM5
	};

	enum class ERenderQueryType
	{
		Unknown
	};

	//The maximum numbers of simultaneously used render targets.
	const unsigned char RD_MaxSimultaneousRenderTargets = 8;

	enum class ELockMode : unsigned char
	{
		Read,
		Write
	};

	enum class ETextureType : unsigned char
	{
		Unknown,
		Tex2D,
		Tex2DArray,
		Tex3D,
		TexCube
	};

	enum class EShaderType : unsigned char
	{
		Unknown,
		Vertex,
		Hull,
		Domain,
		Pixel,
		Geometry,
		Compute
	};

	enum class ETextureCreateFlags : unsigned int
	{
		None = 0,
		sRGB = 1
	};

	enum class EBufferUsageFlags : unsigned int
	{
		Static = 0x1,
		Dynamic = 0x2
	};

	enum class EVertexElementType : unsigned char
	{
		None,
		Float1,
		Float2,
		Float3,
		Float4,
		PackedNormal,	// FPackedNormal
		Short2,
		Short4,
		Short2N,		// 16 bit word normalized to (value/32767.0,value/32767.0,0,0,1)
		UByte4,
		UByte4N,
		Half2,			// 16 bit float using 1 bit sign, 5 bit exponent, 10 bit mantissa 
		Color
	};

	//----------------------------------

	template <typename T, typename FT>
	inline bool IsSetFlags(T flags, FT f)
	{
		return (flags & static_cast<decltype(flags)>(f)) != 0;
	}
}