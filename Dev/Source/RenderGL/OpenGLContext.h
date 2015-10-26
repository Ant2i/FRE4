#pragma once

#include "OpenGLBase.h"
#include "OpenGLState.h"
#include "FAssert.h"

namespace FRE
{
	class GLContext
	{
	public:
		GLContext(GLPConfig config);
		GLContext(GLPConfig config, const GLContext & shared);
		~GLContext();

		void MakeCurrent();

		inline GLPContext GetPlatformContext() const
		{
			return _platformContext;
		}

		void BindTexture(GLint index, GLuint texture, GLenum target);

		void UseProgram(GLuint program);
		void BindArrayBuffer(GLuint buffer);
		void BindElementArrayBuffer(GLuint buffer);
		void BindPixelUnpackBuffer(GLuint buffer);

		void FlushUseProgram(GLuint program);
		void FlushArrayBuffer(GLuint buffer);
		void FlushElementArrayBuffer(GLuint buffer);
		void FlushPixelUnpackBuffer(GLuint buffer);

    private:
		void ActivateTextureIndex(GLuint index);

	private:
		GLContextState _state;
		GLPContext _platformContext = nullptr;
	};
}