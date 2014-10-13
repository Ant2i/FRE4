#pragma once

namespace FRE
{
	enum class ShaderPlatform
	{
		OGL_SM4,
		OGL_SM5,
		OGL_ES2,
		OGL_ES3,
		D3D_SM4,
		D3D_SM5
	};

	enum class RendetQuetyType
	{

	};

	const unsigned char MaxSimultaneousRenderTargets = 8;
}