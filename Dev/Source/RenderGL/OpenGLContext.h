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

		template <GLenum target> void BindBuffer(GLuint buffer);
		template <> void BindBuffer<GL_ARRAY_BUFFER>(GLuint buffer);
		template <> void BindBuffer<GL_ELEMENT_ARRAY_BUFFER>(GLuint buffer);
		
		void BindTexture(GLuint texture, GLenum target, GLint index, GLuint maxMipLevel, GLuint baseMipLevel = 0);

	private:
		void BindArrayBuffer(GLuint buffer);
		void BindElementArrayBuffer(GLuint buffer);
		void BindPixelUnpackBuffer(GLuint buffer);

		void ActivateTextureIndex(GLuint index);

	private:
		GLContextState _state;
		GLPlatformContextP _platformContext = nullptr;
	};

	template <GLenum target> 
	void GLContext::BindBuffer(GLuint buffer)
	{
		FRE_ASSERT(false);
	}

	template <> 
	void GLContext::BindBuffer<GL_ARRAY_BUFFER>(GLuint buffer)
	{
		BindArrayBuffer(buffer);
	}

	template <>
	void GLContext::BindBuffer<GL_ELEMENT_ARRAY_BUFFER>(GLuint buffer)
	{
		BindElementArrayBuffer(buffer);
	}
}