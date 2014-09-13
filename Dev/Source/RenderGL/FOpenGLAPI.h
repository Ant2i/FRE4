#pragma once

#include "FPlatform.h"

#define GL_API_FUNC static FORCEINLINE

#define UGL_REQUIRED_VOID			{ /*UE_LOG(LogOpenGL,Fatal,TEXT("%s is not supported."), ANSI_TO_TCHAR(__FUNCTION__));*/ }
#define UGL_REQUIRED(ReturnValue)	{ /*UE_LOG(LogOpenGL,Fatal,TEXT("%s is not supported."), ANSI_TO_TCHAR(__FUNCTION__)); return (ReturnValue);*/ }
#define UGL_OPTIONAL_VOID			{ }
#define UGL_OPTIONAL(ReturnValue)	{ /*return (ReturnValue);*/ }
#define check(ReturnValue)

typedef char ANSICHAR;
typedef GLsync UGLsync;

typedef void(*DebugCBFunc)(const char *);

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
	// GL_OES_mapbuffer
	bool SupportsMapBuffer = false;
	// GL_OES_depth_texture
	bool SupportsDepthTexture = false;
	//
	bool SupportsDrawBuffers = false;
	bool SupportsPixelBuffers = false;
	bool SupportsUniformBuffers = false;
	bool SupportsStructuredBuffers = false;
	bool SupportsTimestampQueries = false;
	bool SupportsDisjointTimeQueries = false;
	bool SupportsOcclusionQueries = false;
	bool SupportsExactOcclusionQueries = false;
	bool SupportsBlitFramebuffer = false;
	bool SupportsDepthStencilReadSurface = false;
	bool SupportsFloatReadSurface = false;
	bool SupportsMultipleRenderTargets = false;
	bool SupportsMultisampledTextures = false;
	bool SupportsFences = false;
	bool SupportsPolygonMode = false;
	bool SupportsSamplerObjects = false;
	bool SupportsTexture3D = false;
	bool SupportsTextureLODBias = false;
	bool SupportsTextureCompare = false;
	bool SupportsTextureBaseLevel = false;
	bool SupportsTextureMaxLevel = false;
	bool SupportsInstancing = false;
	bool SupportsVertexAttribInteger = false;
	bool SupportsVertexAttribShort = false;
	bool SupportsVertexAttribByte = false;
	bool SupportsVertexAttribDouble = false;
	// GL_OES_vertex_array_object, ARB_vertex_array_object
	bool SupportsVertexArrayObjects = false;
	bool SupportsDrawIndexOffset = false;
	bool SupportsResourceView = false;
	bool SupportsCopyBuffer = false;
	bool SupportsDiscardFrameBuffer = false;
	bool SupportsIndexedExtensions = false;
	bool SupportsVertexHalfFloat = false;
	bool SupportsTextureFloat = false;
	bool SupportsTextureHalfFloat = false;
	bool SupportsColorBufferHalfFloat = false;
	bool SupportsGSRenderTargetLayerSwitchingToMips = false;
	bool SupportsShaderFramebufferFetch = false;
	bool SupportsVertexArrayBGRA = false;
	bool SupportsBGRA8888 = false;
	bool SupportsSRGB = false;
	bool SupportsRGBA8 = false;
	bool SupportsDXT = false;
	bool SupportsPVRTC = false;
	bool SupportsATITC = false;
	bool SupportsASTC = false;
	bool SupportsETC1 = false;
	bool SupportsETC2 = false;
	bool SupportsCombinedDepthStencilAttachment = false;
	bool SupportsFastBufferData = false;
	bool SupportsCopyImage = false;
	bool SupportsCopyTextureLevels = false;
	bool SupportsTextureFilterAnisotropic = false;
	bool SupportsPackedDepthStencil = false;
	bool SupportsTextureCubeLodEXT = false;
	bool SupportsShaderTextureLod = false;
	bool SupportsSeparateAlphaBlend = false;
	bool SupportsTessellation = false;
	bool SupportsComputeShaders = false;
	bool SupportsTextureView = false;
	bool SupportsSeamlessCubeMap = false;
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

	GLVersion Version;
};

class OpenGLAPI
{
public:
	enum class ResourceLockMode
	{
		ReadWrite,
		ReadOnly,
		WriteOnly,
		WriteOnlyUnsynchronized,
	};

	enum class QueryMode
	{
		Result,
		ResultAvailable,
	};

	enum class FenceResult
	{
		AlreadySignaled,
		TimeoutExpired,
		ConditionSatisfied,
		WaitFailed,
	};

	static void Init(const char * extensions);

	GL_API_FUNC GLenum GetDepthFormat()	{ return GL_DEPTH_COMPONENT16; }

	GL_API_FUNC void QueryTimestampCounter(GLuint hQuery) {}
	GL_API_FUNC void BeginQuery(GLenum queryType, GLuint hQuery) {}
	GL_API_FUNC void EndQuery(GLenum queryType) {}
	GL_API_FUNC void GetQueryObject(GLuint hQuery, QueryMode mode, uint64 * result) {}
	GL_API_FUNC void BindFragDataLocation(GLuint hProgram, GLuint color, const GLchar * name) {}
	GL_API_FUNC void ReadBuffer(GLenum mode) {}
	GL_API_FUNC void DrawBuffer(GLenum mode) {}
	GL_API_FUNC void DeleteSync(UGLsync hSync) {}
	GL_API_FUNC UGLsync FenceSync(GLenum condition, GLbitfield flags) { return 0; }
	GL_API_FUNC bool IsSync(UGLsync hSync) { return false; }
	GL_API_FUNC FenceResult ClientWaitSync(UGLsync hSync, GLbitfield flags, GLuint64 timeout) { return FenceResult::WaitFailed; }
	GL_API_FUNC void GenSamplers(GLsizei count, GLuint * hSamplers) {}
	GL_API_FUNC void DeleteSamplers(GLsizei count, GLuint * hSamplers) {}
	GL_API_FUNC void SetSamplerParameter(GLuint hSampler, GLenum parameter, GLint value) {}
	GL_API_FUNC void BindSampler(GLuint unit, GLuint hSampler) {}
	GL_API_FUNC void PolygonMode(GLenum face, GLenum mode) {}
	GL_API_FUNC void VertexAttribDivisor(GLuint index, GLuint divisor) {}
	GL_API_FUNC void PushGroupMarker(const ANSICHAR * name) {}
	GL_API_FUNC void PopGroupMarker() {}
	GL_API_FUNC void LabelObject(GLenum type, GLuint hObject, const ANSICHAR * name) {}
	GL_API_FUNC GLsizei GetLabelObject(GLenum type, GLuint hObject, GLsizei bufferSize, ANSICHAR * outName) { return 0; }
	GL_API_FUNC void DiscardFramebufferEXT(GLenum target, GLsizei numAttachments, const GLenum * attachments) {}
	GL_API_FUNC void CopyTextureLevels(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) {}
	GL_API_FUNC void * MapBufferRange(GLenum type, uint32 inOffset, uint32 inSize, ResourceLockMode lockMode) { return nullptr; }
	GL_API_FUNC void UnmapBufferRange(GLenum type, uint32 inOffset, uint32 inSize) {}
	GL_API_FUNC void UnmapBuffer(GLenum type) {}
	GL_API_FUNC void GenQueries(GLsizei numQueries, GLuint * hQueries) {}
	GL_API_FUNC void DeleteQueries(GLsizei numQueries, const GLuint * hQueries) {}
	GL_API_FUNC void GetQueryObject(GLuint hQuery, QueryMode mode, GLuint * result) {}
	GL_API_FUNC void BindBufferBase(GLenum target, GLuint index, GLuint hBuffer) {}
	GL_API_FUNC GLuint GetUniformBlockIndex(GLuint hProgram, const GLchar * uniformBlockName) { return -1; }
	GL_API_FUNC void UniformBlockBinding(GLuint hProgram, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {}
	GL_API_FUNC void Uniform4uiv(GLint location, GLsizei count, const GLuint * value) {}
	GL_API_FUNC void TexParameter(GLenum target, GLenum parameter, GLint value) {}
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
	GL_API_FUNC void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {}
	GL_API_FUNC void DrawBuffers(GLsizei numBuffers, const GLenum * hBuffers) {}
	GL_API_FUNC void DepthRange(GLdouble Near, GLdouble Far) {}
	GL_API_FUNC void EnableIndexed(GLenum parameter, GLuint index) {}
	GL_API_FUNC void DisableIndexed(GLenum parameter, GLuint index) {}
	GL_API_FUNC void ColorMaskIndexed(GLuint index, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {}
	GL_API_FUNC void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {}
	GL_API_FUNC void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) {}
	GL_API_FUNC void VertexAttrib4Nsv(GLuint index, const GLshort * values) {}
	GL_API_FUNC void VertexAttrib4sv(GLuint index, const GLshort * values) {}
	GL_API_FUNC void VertexAttribI4sv(GLuint index, const GLshort * values) {}
	GL_API_FUNC void VertexAttribI4usv(GLuint index, const GLushort * values) {}
	GL_API_FUNC void VertexAttrib4Nubv(GLuint index, const GLubyte * values) {}
	GL_API_FUNC void VertexAttrib4ubv(GLuint index, const GLubyte * values) {}
	GL_API_FUNC void VertexAttribI4ubv(GLuint index, const GLubyte * values) {}
	GL_API_FUNC void VertexAttrib4Nbv(GLuint index, const GLbyte * values) {}
	GL_API_FUNC void VertexAttrib4bv(GLuint index, const GLbyte * values) {}
	GL_API_FUNC void VertexAttribI4bv(GLuint index, const GLbyte * values) {}
	GL_API_FUNC void VertexAttrib4dv(GLuint index, const GLdouble * values) {}
	GL_API_FUNC void VertexAttribI4iv(GLuint index, const GLint * values) {}
	GL_API_FUNC void VertexAttribI4uiv(GLuint index, const GLuint * values) {}
	GL_API_FUNC void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount) {}
	GL_API_FUNC void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instanceCount) {}
	GL_API_FUNC void DrawRangeElements(GLenum node, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) {}
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
	GL_API_FUNC void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {}
	
	GL_API_FUNC const char * GetExtensionString();

	//GL_API_FUNC ERHIFeatureLevel::Type GetFeatureLevel() UGL_REQUIRED(ERHIFeatureLevel::SM4)
    //GL_API_FUNC EShaderPlatform GetShaderPlatform() UGL_REQUIRED(SP_OPENGL_SM4)
    //GL_API_FUNC FString GetAdapterName() UGL_REQUIRED(TEXT(""))

	GL_API_FUNC void BlendFuncSeparatei(GLuint indexDrawBuffer, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {}
	GL_API_FUNC void BlendEquationSeparatei(GLuint indexDrawBuffer, GLenum modeRGB, GLenum modeAlpha) {}
	GL_API_FUNC void BlendFunci(GLuint indexDrawBuffer, GLenum src, GLenum dst) {}
	GL_API_FUNC void BlendEquationi(GLuint indexDrawBuffer, GLenum mode) {}
	GL_API_FUNC void PatchParameteri(GLenum pName, GLint value) {}
	GL_API_FUNC void BindImageTexture(GLuint unit, GLuint hTexture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {}
	GL_API_FUNC void DispatchCompute(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ) {}
	GL_API_FUNC void MemoryBarrier(GLbitfield barriers) {}
	GL_API_FUNC bool TexStorage2D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, uint32 flags) {	return false; }
	GL_API_FUNC void TexStorage3D(GLenum target, GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type) {}
	GL_API_FUNC void CompressedTexSubImage3D(GLenum target, GLint level, GLint xOffset, GLint yOffset, GLint zOffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * pixelData) {}
	GL_API_FUNC void CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth) {}

    GL_API_FUNC void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data)
    {
        glBufferSubData(target, offset, size, data);
    }

    static const OpenGLCapability & GetCapability() { return _capability; }
    
protected:
    static OpenGLCapability _capability;
 };