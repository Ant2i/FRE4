#pragma once

//#include "FreBase.h"
#include "RDEnums.h"
#include "OpenGLDeviceEnums.h"
#include <array>

namespace FRE
{
	struct TextureState
	{
		GLenum Target = 0;
		GLuint Name = 0;
	};

	struct SamplerState
	{
		//GL_TEXTURE_WRAP_S
		GLint WrapS = GL_REPEAT;
		//GL_TEXTURE_WRAP_T
		GLint WrapT = GL_REPEAT;
		//GL_TEXTURE_WRAP_R
		GLint WrapR = GL_REPEAT;
		//GL_TEXTURE_LOD_BIAS
		GLint LODBias = 0;
		//GL_TEXTURE_MAG_FILTER
		GLint MagFilter = GL_NEAREST;
		//GL_TEXTURE_MIN_FILTER
		GLint MinFilter = GL_NEAREST;
		//GL_TEXTURE_MAX_ANISOTROPY_EXT
		GLint MaxAnisotropy = 1;
		//GL_TEXTURE_COMPARE_MODE
		GLint CompareMode = GL_NONE;
		//GL_TEXTURE_COMPARE_FUNC
		GLint CompareFunc = GL_ALWAYS;
	};

	struct BlendState
	{
		//EnableIndex/DisableIndex GL_BLEND
		GLboolean AlphaBlendEnable = GL_FALSE;
		//BlendEquationSeparatei
		GLenum ColorBlendOperation = GL_NONE;
		GLenum AlphaBlendOperation = GL_NONE;

		//glBlendFuncSeparate
		//glBlendFunci
		//glBlendFunc
		GLenum ColorSourceBlendFactor = GL_NONE;
		GLenum ColorDestBlendFactor = GL_NONE;
		GLenum AlphaSourceBlendFactor = GL_NONE;
		GLenum AlphaDestBlendFactor = GL_NONE;

		// Needed separate alpha blend
		GLboolean SeparateAlphaBlendEnable = GL_FALSE;
		
		//glColorMaskIndexed
		GLboolean ColorWriteMaskR = GL_FALSE;
		GLboolean ColorWriteMaskG = GL_FALSE;
		GLboolean ColorWriteMaskB = GL_FALSE;
		GLboolean ColorWriteMaskA = GL_FALSE;
	};

	typedef std::array<BlendState, RD_MaxSimultaneousRenderTargets> BlendTargetStateList;
	typedef std::array<GLuint, GL_MaxUniformBufferBindings> UniformBufferList;
	typedef std::array<TextureState, GL_MaxCombineTexture> TextureStateList;

	struct GLContextState
	{
		//Raster state.
		//glPolygonMode
		GLenum FillMode = GL_FILL;
		//glCullFace
		GLenum CullMode = GL_NONE;
		//glPolygonOffset
		GLfloat DepthBias = 0.0f;
		GLfloat SlopeScaleDepthBias = 0.0f;

		//Depth state.
		//Enable/Disable GL_DEPTH_TEST
		GLboolean ZEnable = GL_FALSE;
		//glDepthMask
		GLboolean ZWriteEnable = GL_TRUE;
		//glDepthFunc
		GLenum ZFunc = GL_LESS;

		//Stensil state.
		//Enable/Disable GL_STENCIL_TEST
		GLboolean StencilEnable = GL_FALSE;
		//Check needed two side render.
		GLboolean TwoSidedStencilMode = GL_FALSE;
		//glStencilFunc/glStencilFuncSeparate(GL_BACK
		GLenum StencilFunc = GL_ALWAYS;
		GLint StencilRefValue = 0;
		GLint StencilReadMask = 0xFFFFFFFF;
		//glStencilOp/glStencilOpSeparate(GL_BACK
		GLenum StencilFail = GL_KEEP;
		GLenum StencilZFail = GL_KEEP;
		GLenum StencilPass = GL_KEEP;
		//glStencilFuncSeparate(GL_FRONT
		GLenum CCWStencilFunc = GL_ALWAYS;
		//glStencilOpSeparate(GL_FRONT
		GLenum CCWStencilFail = GL_KEEP;
		GLenum CCWStencilZFail = GL_KEEP;
		GLenum CCWStencilPass = GL_KEEP;
		//glStencilMask
		GLint StencilWriteMask = 0xFFFFFFFF;

		GLuint Framebuffer = 0;
		GLuint RenderTargetWidth = 0;
		GLuint RenderTargetHeight = 0;
		//glUseProgram
		GLint UseProgram = -1;
		//glActiveTexture
		GLenum ActiveTexture = 0;

		//Enable/Disable GL_SCISSOR_TEST
		GLboolean ScissorEnabled = GL_FALSE;
		//glScissor
		GLint ScissorX = 0;
		GLint ScissorY = 0;
		GLsizei ScissorWidth = 0;
		GLsizei ScissorHeight = 0;
		
		//glViewport
		GLint ViewportX = 0;
		GLint ViewportY = 0;
		GLsizei ViewportWidth = 0;
		GLsizei ViewportHeight = 0;

		//glDepthRange
		GLfloat DepthMinZ = 0.0f;
		GLfloat DepthMaxZ = 1.0f;

		//glBindBuffer(GL_ARRAY_BUFFER
		GLint ArrayBufferBound = -1;
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER
		GLint ElementArrayBufferBound = -1;
		//glBindBuffer(GL_PIXEL_UNPACK_BUFFER
		GLint PixelUnpackBufferBound = -1;
		//glBindBuffer(GL_UNIFORM_BUFFER
		GLint UniformBufferBound = -1;

		//glClearColor
		GLfloat ClearColorR = 0.0f;
		GLfloat ClearColorG = 0.0f;
		GLfloat ClearColorB = 0.0f;
		GLfloat ClearColorA = 0.0f;

		//glClearStencil
		GLuint ClearStencil = 0;
		//glClearDepth
		GLfloat ClearDepth = 1.0f;
		//Enable/Disable GL_TEXTURE_CUBE_MAP_SEAMLESS
		bool SeamlessCubemapEnabled;

		//Blend state.
		BlendTargetStateList BlendSate;
		//Active texture state.
		TextureStateList Textures;
		//glBindBufferBase
		UniformBufferList UniformBuffers;

	};
}