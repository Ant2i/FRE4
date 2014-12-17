#pragma once

#include "OpenGLBase.h"
#include "OpenGLState.h"
#include "FreAssert.h"

namespace FRE
{
	class GLContext
	{
	public:
		GLContext();
		GLContext(const GLContext & shared);
		~GLContext();

		void MakeCurrent();

		inline GLPlatformContextP GetPlatformContext() const
		{
			return _platformContext;
		}

		void BindTexture(GLuint texture, GLenum target, GLint index, GLuint maxMipLevel, GLuint baseMipLevel = 0);

		void BindArrayBuffer(GLuint buffer);
		void BindElementArrayBuffer(GLuint buffer);
		void BindPixelUnpackBuffer(GLuint buffer);

    private:
		void ActivateTextureIndex(GLuint index);

	private:
		GLContextState _state;
		GLPlatformContextP _platformContext = nullptr;
	};
}