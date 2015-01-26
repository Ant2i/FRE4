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

		uint8 bNormalized;
		uint8 AttributeIndex;
		uint8 bShouldConvertToFloat;
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