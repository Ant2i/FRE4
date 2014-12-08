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

	const unsigned char MaxSimultaneousRenderTargets = 8;

	enum class ELockMode : unsigned char
	{
		Read,
		Write,
		ReadWrite
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

	//----------------------------------

	template <typename T, typename FT>
	inline bool IsSetFlags(T flags, FT f)
	{
		return (flags & static_cast<decltype(flags)>(f)) != 0;
	}
}