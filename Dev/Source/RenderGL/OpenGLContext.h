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

		void BindArrayBuffer(GLuint buffer);
		void BindElementArrayBuffer(GLuint buffer);
		void BindPixelUnpackBuffer(GLuint buffer);

		void BindTexture(GLuint texture, GLenum target, GLint index, GLuint maxMipLevel, GLuint baseMipLevel = 0);

	private:
		void ActivateTextureIndex(GLuint index);

	private:
		GLContextState _state;
		GLPlatformContextP _platformContext = nullptr;
	};
}