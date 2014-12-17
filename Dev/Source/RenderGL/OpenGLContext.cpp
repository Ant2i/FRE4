#include "OpenGLContext.h"

namespace FRE
{
	GLContext::GLContext()
	{
		_platformContext = GLPlatformContextCreate();
	}

	GLContext::GLContext(const GLContext & shared)
	{
		_platformContext = GLPlatformContextCreate(shared.GetPlatformContext());
	}

	GLContext::~GLContext()
	{
		GLPlatformContextDestroy(_platformContext);
	}

	void GLContext::MakeCurrent()
	{
		GLPlatformContextMakeCurrent(_platformContext);
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

	void GLContext::BindTexture(GLuint texture, GLenum target, GLint index, GLuint maxMipLevel, GLuint baseMipLevel)
	{
		TextureState & textureState = _state.Textures[index];

		const bool dirtyTarget = textureState.Target != target;
		const bool dirtyTextureName = textureState.Name != texture;
		const bool dirtyMaxMip = textureState.MaxLevel != maxMipLevel;
		const bool dirtyBaseMip = textureState.BaseLevel != baseMipLevel;

		if (dirtyTarget || dirtyTextureName || dirtyMaxMip || dirtyBaseMip)
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

			if (target != GL_NONE && target != GL_TEXTURE_BUFFER)
			{
				if (dirtyMaxMip && FOpenGL::GetCapability().SupportTextureMaxLevel)
				{
					FOpenGL::TexParameter(target, GL_TEXTURE_MAX_LEVEL, maxMipLevel);
					textureState.MaxLevel = maxMipLevel;
				}

				if (dirtyBaseMip && FOpenGL::GetCapability().SupportTextureBaseLevel)
				{
					FOpenGL::TexParameter(target, GL_TEXTURE_BASE_LEVEL, baseMipLevel);
					textureState.BaseLevel = baseMipLevel;
				}
			}
			else
			{
				textureState.BaseLevel = 0;
				textureState.MaxLevel = 0;
			}

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
}