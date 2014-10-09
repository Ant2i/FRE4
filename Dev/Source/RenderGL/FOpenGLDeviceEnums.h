#pragma once

enum class GLShaderStage
{
	Vertex = 0,
	TessControl,
	TessEvaluation,
	Geometry,
	Fragment
};

const unsigned char GLNumFixedShaderStage = 5;
const unsigned GLMaxUniformBufferBindings = GLNumFixedShaderStage * 12;



