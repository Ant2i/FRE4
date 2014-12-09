#pragma once

enum class GLShaderStage
{
	Vertex = 0,
	TessControl,
	TessEvaluation,
	Geometry,
	Fragment
};

const unsigned char GL_NumFixedShaderStage = 5;
const unsigned GL_MaxUniformBufferBindings = GL_NumFixedShaderStage * 12;
const unsigned GL_MaxCombineTexture = 100;



