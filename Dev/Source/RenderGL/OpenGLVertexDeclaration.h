#pragma once

#include "RDResources.h"
#include "OpenGLBase.h"
#include <vector>

namespace FRE
{
	struct GLVertexElement
	{
		GLenum Type;
		GLuint StreamIndex;
		GLuint Offset;
		GLuint Size;
		GLuint Divisor;

		uint8_t bNormalized;
		uint8_t AttributeIndex;
		uint8_t bShouldConvertToFloat;
	};

	typedef std::vector<GLVertexElement> GLVertexElements;

	class GLVertexDeclaration : public RDVertexDeclaration
	{
	public:
		GLVertexElements VertexElements;

		explicit GLVertexDeclaration(const GLVertexElements & elements)
			: VertexElements(elements)
		{
		}
	};

}