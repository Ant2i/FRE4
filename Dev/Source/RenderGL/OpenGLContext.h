#pragma once

#include "OpenGLBase.h"
#include "OpenGLState.h"
#include "FAssert.h"

namespace FRE
{
	class GLContext
	{
	public:
		GLContext();
		GLContext(const GLContext & shared);
		~GLContext();

		void MakeCurrent();

		inline GLPlatformContextH GetPlatformContext() const
		{
			return _platformContext;
		}

		void BindTexture(GLint index, GLuint texture, GLenum target);

		void UseProgram(GLuint program);
		void BindArrayBuffer(GLuint buffer);
		void BindElementArrayBuffer(GLuint buffer);
		void BindPixelUnpackBuffer(GLuint buffer);

		//
		void FlushArrayBuffer(GLuint buffer);
		void FlushElementArrayBuffer(GLuint buffer);
		void FlushPixelUnpackBuffer(GLuint buffer);
		void FlushUseProgram(GLuint program);

    private:
		void ActivateTextureIndex(GLuint index);

	private:
		GLContextState _state;
		GLPlatformContextH _platformContext = 0;
	};
}