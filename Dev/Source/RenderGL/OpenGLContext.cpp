#include "OpenGLContext.h"

namespace FRE
{
	GLContext::GLContext()
	{
		ContextParams params;
		_platformContext = GLPlatformContextCreate(params);
	}

	GLContext::GLContext(const GLContext & shared)
	{
		ContextParams params;
		params.HShared = shared.GetPlatformContext();
		_platformContext = GLPlatformContextCreate(params);
	}

	GLContext::~GLContext()
	{
		GLPlatformContextDestroy(_platformContext);
	}

	void GLContext::MakeCurrent()
	{
		GLPlatformContextMakeCurrent(_platformContext);
	}

	void GLContext::UseProgram(GLuint program)
	{
		if (_state.UseProgram != program)
		{
			glUseProgram(program);
			_state.UseProgram = program;
		}
	}

	void GLContext::BindPixelUnpackBuffer(GLuint buffer)
	{
		if (_state.PixelUnpackBufferBound != buffer)
		{
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffer);
			_state.PixelUnpackBufferBound = buffer;
		}
	}

	void GLContext::BindArrayBuffer(GLuint buffer)
	{
		if (_state.ArrayBufferBound != buffer)
		{
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			_state.ArrayBufferBound = buffer;
		}
	}

	void GLContext::BindElementArrayBuffer(GLuint buffer)
	{
		if (_state.ElementArrayBufferBound != buffer)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
			_state.ElementArrayBufferBound = buffer;
		}
	}

	void GLContext::BindTexture(GLint index, GLuint texture, GLenum target)
	{
		TextureState & textureState = _state.Textures[index];

		const bool dirtyTarget = textureState.Target != target;
		const bool dirtyTextureName = textureState.Name != texture;

		if (dirtyTarget || dirtyTextureName)
		{
			ActivateTextureIndex(index);

			if (!dirtyTarget)
			{
				glBindTexture(target, texture);
			}
			else
			{
				if (textureState.Target != GL_NONE)
					glBindTexture(textureState.Target, 0);

				if (target != GL_NONE)
					glBindTexture(target, texture);
			}

			//if (target != GL_NONE && target != GL_TEXTURE_BUFFER)
			//{
			//	if (dirtyMaxMip && FOpenGL::GetCapability().SupportTextureMaxLevel)
			//	{
			//		FOpenGL::TexParameter(target, GL_TEXTURE_MAX_LEVEL, maxMipLevel);
			//		textureState.MaxLevel = maxMipLevel;
			//	}

			//	if (dirtyBaseMip && FOpenGL::GetCapability().SupportTextureBaseLevel)
			//	{
			//		FOpenGL::TexParameter(target, GL_TEXTURE_BASE_LEVEL, baseMipLevel);
			//		textureState.BaseLevel = baseMipLevel;
			//	}
			//}
			//else
			//{
			//	textureState.BaseLevel = 0;
			//	textureState.MaxLevel = 0;
			//}

			textureState.Target = target;
			textureState.Name = texture;
		}
	}

	void GLContext::ActivateTextureIndex(GLuint index)
	{
		if (_state.ActiveTexture != index)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			_state.ActiveTexture = index;
		}
	}

	//

	void GLContext::FlushArrayBuffer(GLuint buffer)
	{
		if (_state.ArrayBufferBound == buffer)
			_state.ArrayBufferBound = -1;
	}

	void GLContext::FlushElementArrayBuffer(GLuint buffer)
	{
		if (_state.ElementArrayBufferBound == buffer)
			_state.ElementArrayBufferBound = -1;
	}

	void GLContext::FlushPixelUnpackBuffer(GLuint buffer)
	{
		if (_state.PixelUnpackBufferBound == buffer)
			_state.PixelUnpackBufferBound = -1;
	}

	void GLContext::FlushUseProgram(GLuint program)
	{
		if (_state.UseProgram == program)
			_state.UseProgram = -1;
	}
}