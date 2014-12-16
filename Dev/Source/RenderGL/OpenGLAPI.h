#pragma once

#include "FPlatform.h"

#define GL_API_FUNC static FORCEINLINE

typedef char ANSICHAR;
typedef GLsync UGLsync;

typedef void(*DebugCBFunc)(const char *);

namespace FRE
{
	enum class GLPlatformType
	{
		General,
		ES,
		WEB
	};

	struct GLVersion
	{
		GLVersion(int major = 0, int minor = 0) :
		Major(major),
		Minor(minor)
		{

		}

		int Major;
		int Minor;
	};

	struct OpenGLCapability
	{
		bool SupportPixelBuffers = false;
		bool SupportUniformBuffers = false;
		bool SupportStructuredBuffers = false;
		bool SupportTimestampQueries = false;
		bool SupportOcclusionQueries = false;
		bool SupportExactOcclusionQueries = false;
		bool SupportBlitFramebuffer = false;
		bool SupportFloatReadSurface = false;
		bool SupportMultipleRenderTargets = false;
		bool SupportMultisampledTextures = false;
		bool SupportFences = false;
		bool SupportSamplerObjects = false;
		bool SupportTexture3D = false;
		bool SupportTextureLODBias = false;
		bool SupportTextureCompare = false;
		bool SupportTextureBaseLevel = false;
		bool SupportTextureMaxLevel = false;
		bool SupportInstancing = false;
		bool SupportDrawIndexOffset = false;
		bool SupportTextureBuffer = false;
		bool SupportCopyBuffer = false;
		bool SupportDiscardFrameBuffer = false;
		bool SupportVertexHalfFloat = false;
		//GL_OES_texture_half_float
		bool SupportTextureHalfFloat = false;
		//GL_EXT_color_buffer_half_float
		bool SupportColorBufferHalfFloat = false;
		bool SupportGSRenderTargetLayerSwitchingToMips = false;

		bool SupportBGRA8888 = false;
		bool SupportSRGB = false;
		bool SupportRGBA8 = false;
		bool SupportDXT = false;
		//bool SupportPVRTC = false;
		//bool SupportATITC = false;
		//bool SupportASTC = false;
		//bool SupportETC1 = false;
		//bool SupportETC2 = false;
		bool SupportCombinedDepthStencilAttachment = false;
		bool SupportFastBufferData = false;
		bool SupportCopyImage = false;
		bool SupportCopyTextureLevels = false;
		bool SupportTextureFilterAnisotropic = false;
		bool SupportPackedDepthStencil = false;
		bool SupportTextureCubeLodEXT = false;
		bool SupportShaderTextureLod = false;
		bool SupportSeparateAlphaBlend = false;
		bool SupportTessellation = false;
		bool SupportComputeShaders = false;
		bool SupportTextureView = false;
		bool SupportSeamlessCubeMap = false;
		bool HasSamplerRestrictions = false;
		bool HasHardwareHiddenSurfaceRemoval = false;

		GLint MaxTextureImageUnits = 0;
		GLint MaxCombinedTextureImageUnits = 0;
		GLint MaxVertexTextureImageUnits = 0;
		GLint MaxGeometryTextureImageUnits = 0;
		GLint MaxHullTextureImageUnits = 0;
		GLint MaxDomainTextureImageUnits = 0;
		GLint MaxVertexUniformComponents = 0;
		GLint MaxPixelUniformComponents = 0;
		GLint MaxGeometryUniformComponents = 0;
		GLint MaxHullUniformComponents = 0;
		GLint MaxDomainUniformComponents = 0;
		GLint MaxComputeTextureImageUnits = 0;
		GLint MaxComputeUniformComponents = 0;
		GLint MaxTextureBufferSize = 0;

		GLVersion Version;
		GLPlatformType Platform = GLPlatformType::General;
	};

	class OpenGLAPI
	{
	public:
		enum class LockMode
		{
			ReadWrite,
			Read,
			Write,
			WriteUnsynchronized
		};

		enum class QueryMode
		{
			Result,
			ResultAvailable
		};

		enum class FenceResult
		{
			AlreadySignaled,
			TimeoutExpired,
			ConditionSatisfied,
			WaitFailed
		};

		static void Init(const char * extensions);

		GL_API_FUNC GLenum GetDepthFormat()	{ return GL_DEPTH_COMPONENT16; }

		GL_API_FUNC void QueryTimestampCounter(GLuint hQuery) {}

		GL_API_FUNC void GenQueries(GLsizei numQueries, GLuint * hQueries) {}
		GL_API_FUNC void DeleteQueries(GLsizei numQueries, const GLuint * hQueries) {}
		GL_API_FUNC void BeginQuery(GLenum queryType, GLuint hQuery) {}
		GL_API_FUNC void EndQuery(GLenum queryType) {}
		//https://www.opengl.org/sdk/docs/man/html/glGetQueryObject.xhtml
		GL_API_FUNC void GetQueryObject(GLuint hQuery, QueryMode mode, uint64 * result) {}
		GL_API_FUNC void GetQueryObject(GLuint hQuery, QueryMode mode, GLuint * result) {}

		GL_API_FUNC void BindFragDataLocation(GLuint hProgram, GLuint color, const GLchar * name) {}
		//https://www.opengl.org/sdk/docs/man3/xhtml/glReadBuffer.xml
		GL_API_FUNC void ReadBuffer(GLenum mode) {}
		//https://www.opengl.org/sdk/docs/man3/xhtml/glDrawBuffer.xml
		GL_API_FUNC void DrawBuffer(GLenum mode) {}

		GL_API_FUNC UGLsync FenceSync(GLenum condition, GLbitfield flags) { return 0; }
		GL_API_FUNC void DeleteSync(UGLsync hSync) {}
		GL_API_FUNC bool IsSync(UGLsync hSync) { return false; }
		GL_API_FUNC FenceResult ClientWaitSync(UGLsync hSync, GLbitfield flags, GLuint64 timeout) { return FenceResult::WaitFailed; }

		GL_API_FUNC void GenSamplers(GLsizei count, GLuint * hSamplers) {}
		GL_API_FUNC void DeleteSamplers(GLsizei count, GLuint * hSamplers) {}
		//https://www.opengl.org/sdk/docs/man/html/glSamplerParameter.xhtml
		GL_API_FUNC void SetSamplerParameter(GLuint hSampler, GLenum parameter, GLint value) {}
		GL_API_FUNC void BindSampler(GLuint unit, GLuint hSampler) {}

		GL_API_FUNC void PolygonMode(GLenum face, GLenum mode) {}
		GL_API_FUNC void VertexAttribDivisor(GLuint index, GLuint divisor) {}

		//https://www.khronos.org/registry/gles/extensions/EXT/EXT_debug_marker.txt
		GL_API_FUNC void PushGroupMarker(const ANSICHAR * name) {}
		GL_API_FUNC void PopGroupMarker() {}

		//https://www.opengl.org/sdk/docs/man/html/glObjectLabel.xhtml
		GL_API_FUNC void LabelObject(GLenum type, GLuint hObject, const ANSICHAR * name) {}
		GL_API_FUNC GLsizei GetLabelObject(GLenum type, GLuint hObject, GLsizei bufferSize, ANSICHAR * outName) { return 0; }

		GL_API_FUNC void DiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum * attachments) {}
		GL_API_FUNC void CopyTextureLevels(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) {}

		//https://www.opengl.org/sdk/docs/man/html/glMapBufferRange.xhtml
		GL_API_FUNC void * MapBufferRange(GLenum type, GLuint offset, GLuint size, LockMode lockMode) { return nullptr; }
		GL_API_FUNC void UnmapBufferRange(GLenum type, GLuint offset, GLuint size) {}
		GL_API_FUNC void UnmapBuffer(GLenum type) {}

		GL_API_FUNC void BindBufferBase(GLenum target, GLuint index, GLuint hBuffer) {}

		GL_API_FUNC GLuint GetUniformBlockIndex(GLuint hProgram, const GLchar * uniformBlockName) { return -1; }
		GL_API_FUNC void UniformBlockBinding(GLuint hProgram, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {}
		GL_API_FUNC void Uniform4uiv(GLint location, GLsizei count, const GLuint * value) {}

		//https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glTexParameter.xml
		GL_API_FUNC void TexParameter(GLenum target, GLenum parameter, GLint value) {}

		//https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glFramebufferTexture.xml
		GL_API_FUNC void FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint Level) {}
		GL_API_FUNC void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum texTarget, GLuint hTexture, GLint level)
		{
			glFramebufferTexture2D(target, attachment, texTarget, hTexture, level);
		}
		GL_API_FUNC void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum texTarget, GLuint hTexture, GLint level, GLint zOffset) {}
		GL_API_FUNC void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint hTexture, GLint level, GLint layer) {}
		GL_API_FUNC void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderBufferTarget, GLuint hRenderBuffer)
		{
			glFramebufferRenderbuffer(target, attachment, renderBufferTarget, hRenderBuffer);
		}

		//https://www.opengl.org/sdk/docs/man3/xhtml/glBlitFramebuffer.xml
		GL_API_FUNC void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {}
		//https://www.opengl.org/sdk/docs/man4/html/glDrawBuffers.xhtml
		GL_API_FUNC void DrawBuffers(GLsizei numBuffers, const GLenum * hBuffers) {}
		GL_API_FUNC void DepthRange(GLdouble Near, GLdouble Far) {}

		//https://www.opengl.org/sdk/docs/man/html/glEnable.xhtml
		GL_API_FUNC void EnableIndexed(GLenum parameter, GLuint index) {}
		GL_API_FUNC void DisableIndexed(GLenum parameter, GLuint index) {}

		//https://www.opengl.org/sdk/docs/man3/xhtml/glColorMask.xml
		GL_API_FUNC void ColorMaskIndexed(GLuint index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {}

		GL_API_FUNC void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {}
		GL_API_FUNC void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) {}

		//https://www.opengl.org/sdk/docs/man3/xhtml/glDrawArraysInstanced.xml
		GL_API_FUNC void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount) {}
		//https://www.opengl.org/sdk/docs/man3/xhtml/glDrawElementsInstanced.xml
		GL_API_FUNC void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instanceCount) {}
		//https://www.opengl.org/sdk/docs/man2/xhtml/glDrawRangeElements.xml
		GL_API_FUNC void DrawRangeElements(GLenum node, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) {}

		//https://www.opengl.org/sdk/docs/man3/xhtml/glClearBuffer.xml
		GL_API_FUNC void ClearBufferfv(GLenum buffer, GLint drawBufferIndex, const GLfloat * value) {}
		GL_API_FUNC void ClearBufferfi(GLenum buffer, GLint drawBufferIndex, GLfloat depth, GLint stencil) {}
		GL_API_FUNC void ClearBufferiv(GLenum buffer, GLint drawBufferIndex, const GLint * value) {}
		GL_API_FUNC void ClearDepth(GLdouble depth) {}

		GL_API_FUNC void TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixelData) {}
		GL_API_FUNC void CompressedTexImage3D(GLenum target, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * pixelData) {}
		GL_API_FUNC void TexImage2DMultisample(GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations) {}
		GL_API_FUNC void TexBuffer(GLenum target, GLenum internalFormat, GLuint hBuffer) {}
		GL_API_FUNC void TexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixelData) {}
		GL_API_FUNC void CopyTexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLint x, GLint y, GLsizei width, GLsizei height) {}
		GL_API_FUNC void GetCompressedTexImage(GLenum target, GLint level, GLvoid * outImageData) {}
		GL_API_FUNC void GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * outPixelData) {}
		//https://www.opengl.org/sdk/docs/man3/xhtml/glCopyBufferSubData.xml
		GL_API_FUNC void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {}

		GL_API_FUNC const char * GetExtensionString();

		//GL_API_FUNC ERHIFeatureLevel::Type GetFeatureLevel() UGL_REQUIRED(ERHIFeatureLevel::SM4)
		//GL_API_FUNC FString GetAdapterName() UGL_REQUIRED(TEXT(""))

		GL_API_FUNC void BlendFuncSeparatei(GLuint indexDrawBuffer, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {}
		GL_API_FUNC void BlendEquationSeparatei(GLuint indexDrawBuffer, GLenum modeRGB, GLenum modeAlpha) {}
		GL_API_FUNC void BlendFunci(GLuint indexDrawBuffer, GLenum src, GLenum dst) {}
		GL_API_FUNC void BlendEquationi(GLuint indexDrawBuffer, GLenum mode) {}
		GL_API_FUNC void PatchParameteri(GLenum pName, GLint value) {}

		//https://www.opengl.org/registry/specs/ARB/shader_image_load_store.txt
		//https://www.opengl.org/sdk/docs/man/html/glBindImageTexture.xhtml
		GL_API_FUNC void BindImageTexture(GLuint unit, GLuint hTexture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {}
		GL_API_FUNC void MemoryBarrier(GLbitfield barriers) {}
		//https://www.opengl.org/registry/specs/ARB/compute_shader.txt
		//https://www.opengl.org/sdk/docs/man/html/glDispatchCompute.xhtml
		GL_API_FUNC void DispatchCompute(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ) {}

		GL_API_FUNC bool TexStorage2D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, uint32 flags) { return false; }
		GL_API_FUNC void TexStorage3D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type) {}
		GL_API_FUNC void CompressedTexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * pixelData) {}
		//https://www.opengl.org/sdk/docs/man/html/glCopyImageSubData.xhtml
		GL_API_FUNC void CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) {}
		//https://www.opengl.org/sdk/docs/man3/xhtml/glBufferSubData.xml
		GL_API_FUNC void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data)
		{
			glBufferSubData(target, offset, size, data);
		}

		FORCEINLINE static GLuint GenerateBuffer()
		{
			GLuint name;
			glGenBuffers(1, &name);
			return name;
		}

		FORCEINLINE static GLint GetCurrentBufferBinding(GLenum target)
		{
			GLint name;
			glGetIntegerv(target, &name);
			return name;
		}

		FORCEINLINE static const OpenGLCapability & GetCapability() { return _capability; }

	protected:
		static OpenGLCapability _capability;
	};

	//Init OpenGL platform.
	bool PlatformInitOpenGL();
}