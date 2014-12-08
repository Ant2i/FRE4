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
		void SetupTextureStage(GLint index, GLenum target, GLuint textureName);

	private:
		GLContextState _state;
		GLPlatformContextP _platformContext = nullptr;
	};
}