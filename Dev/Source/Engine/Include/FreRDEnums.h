#pragma once

namespace FRE
{
	enum class ShaderPlatform
	{
		OPENGL_SM4,
		OPENGL_SM5,
		OPENGL_ES2,
		OPENGL_ES3,
		D3D_SM4,
		D3D_SM5
	};

	enum class RendetQuetyType
	{

	};

	const unsigned char MaxSimultaneousRenderTargets = 8;
}