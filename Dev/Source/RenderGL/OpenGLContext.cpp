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

	void GLContext::BindTexture(GLint index, GLenum target, GLuint texture, GLuint mipLevel, GLboolean limitMip)
	{
		TextureState & textureState = _state.Textures[index];

		const bool dirtyTarget = textureState.Target != target;
		const bool dirtyTextureName = textureState.Name != texture;
		const bool dirtyMip = textureState.MaxLevel != mipLevel || textureState.BaseLevel != mipLevel;

		if (dirtyTarget || dirtyTextureName || dirtyMip)
		{
			_GLActiveTexture(index);

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
				if (dirtyMip)
				{
					if (FOpenGL::GetCapability().SupportTextureBaseLevel)
					{
						GLint baseLevel = limitMip ? mipLevel : 0;
						FOpenGL::TexParameter(target, GL_TEXTURE_BASE_LEVEL, baseLevel);
						textureState.BaseLevel = baseLevel;
					}

					if (FOpenGL::GetCapability().SupportTextureMaxLevel)
					{
						FOpenGL::TexParameter(target, GL_TEXTURE_MAX_LEVEL, mipLevel);
						textureState.MaxLevel = mipLevel;
					}
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

		//if (Target != GL_NONE && Target != GL_TEXTURE_BUFFER && !FOpenGL::SupportsTextureView())
		//{
		//	const bool bSameLimitMip = bSameTarget && bSameResource && TextureState.LimitMip == LimitMip;
		//	const bool bSameNumMips = bSameTarget && bSameResource && TextureState.NumMips == NumMips;

		//	if (FOpenGL::SupportsTextureBaseLevel() && !bSameLimitMip)
		//	{
		//		GLint BaseMip = LimitMip == -1 ? 0 : LimitMip;
		//		FOpenGL::TexParameter(Target, GL_TEXTURE_BASE_LEVEL, BaseMip);
		//	}
		//	TextureState.LimitMip = LimitMip;

		//	if (FOpenGL::SupportsTextureMaxLevel() && !bSameNumMips)
		//	{
		//		GLint MaxMip = LimitMip == -1 ? NumMips - 1 : LimitMip;
		//		FOpenGL::TexParameter(Target, GL_TEXTURE_MAX_LEVEL, MaxMip);
		//	}
		//	TextureState.NumMips = NumMips;
		//}
		//else
		//{
		//	TextureState.LimitMip = 0;
		//	TextureState.NumMips = 0;
		//}
	}

	void GLContext::_GLActiveTexture(GLuint index)
	{
		if (_state.ActiveTexture != index)
		{
			glActiveTexture(GL_TEXTURE0 + index);
			_state.ActiveTexture = index;
		}
	}
}