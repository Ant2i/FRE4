#include "OpenGLContext.h"

namespace FRE
{
	GLContext::GLContext()
	{

	}

	GLContext::~GLContext()
	{

	}

	void GLContext::BindPixelUnpackBuffer(GLuint buffer)
	{
		if (_state.PixelUnpackBufferBound != buffer)
		{
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffer);
			_state.PixelUnpackBufferBound = buffer;
		}
	}

	void GLContext::SetupTextureStage(GLint index, GLenum target, GLuint textureName)
	{
		
	}
}