#pragma once

#include "OpenGLBase.h"
#include "OpenGLState.h"

namespace FRE
{
	class GLContext
	{
	public:
		GLContext();
		~GLContext();

		inline GLPlatformContextP GetPlatformContext() const
		{
			return _platformContext;
		}

		void BindPixelUnpackBuffer(GLuint bufferName);
		void BindTexture(GLint index, GLenum target, GLuint texture, GLuint mipLevel, GLboolean limitMip = GL_FALSE);

	private:
		void _GLActiveTexture(GLuint index);

	private:
		GLContextState _state;
		GLPlatformContextP _platformContext = nullptr;
	};
}