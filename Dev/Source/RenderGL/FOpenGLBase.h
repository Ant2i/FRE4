#pragma once

#include "FPlatformTypes.h"
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
	GLVersion(unsigned major = 0, unsigned minor = 0) :
		Major(major),
		Minor(minor)
	{

	}

	unsigned Major;
	unsigned Minor;
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

	GLVersion Version;
};

class OpenGLBaseAPI
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

    static void ProcessQueryGLInt();
    static void ProcessExtensions(const char * & extensions);

    GL_API_FUNC GLenum GetDepthFormat()	{ return GL_DEPTH_COMPONENT16; }

    GL_API_FUNC void QueryTimestampCounter(GLuint QueryID) UGL_OPTIONAL_VOID
    GL_API_FUNC void BeginQuery(GLenum QueryType, GLuint QueryId) UGL_OPTIONAL_VOID
    GL_API_FUNC void EndQuery(GLenum QueryType) UGL_OPTIONAL_VOID
    GL_API_FUNC void GetQueryObject(GLuint QueryId, QueryMode QueryMode, uint64 * OutResult) UGL_OPTIONAL_VOID
    GL_API_FUNC void BindFragDataLocation(GLuint Program, GLuint Color, const GLchar * Name) UGL_OPTIONAL_VOID
    GL_API_FUNC void ReadBuffer(GLenum Mode) UGL_OPTIONAL_VOID
    GL_API_FUNC void DrawBuffer(GLenum Mode) UGL_OPTIONAL_VOID
    GL_API_FUNC void DeleteSync(UGLsync Sync) UGL_OPTIONAL_VOID
    GL_API_FUNC UGLsync FenceSync(GLenum Condition, GLbitfield Flags) UGL_OPTIONAL(0)
    GL_API_FUNC bool IsSync(UGLsync Sync) UGL_OPTIONAL(false)
    GL_API_FUNC FenceResult ClientWaitSync(UGLsync Sync, GLbitfield Flags, GLuint64 Timeout) UGL_OPTIONAL(FR_WaitFailed)
    GL_API_FUNC void GenSamplers(GLsizei Count, GLuint * Samplers) UGL_OPTIONAL_VOID
    GL_API_FUNC void DeleteSamplers(GLsizei Count, GLuint * Samplers) UGL_OPTIONAL_VOID
    GL_API_FUNC void SetSamplerParameter(GLuint Sampler, GLenum Parameter, GLint Value) UGL_OPTIONAL_VOID
    GL_API_FUNC void BindSampler(GLuint Unit, GLuint Sampler) UGL_OPTIONAL_VOID
    GL_API_FUNC void PolygonMode(GLenum Face, GLenum Mode) UGL_OPTIONAL_VOID
    GL_API_FUNC void VertexAttribDivisor(GLuint Index, GLuint Divisor) UGL_OPTIONAL_VOID
    GL_API_FUNC void PushGroupMarker(const ANSICHAR * Name) UGL_OPTIONAL_VOID
    GL_API_FUNC void PopGroupMarker() UGL_OPTIONAL_VOID
    GL_API_FUNC void LabelObject(GLenum Type, GLuint Object, const ANSICHAR * Name) UGL_OPTIONAL_VOID
    GL_API_FUNC GLsizei GetLabelObject(GLenum Type, GLuint Object, GLsizei BufferSize, ANSICHAR * OutName) UGL_OPTIONAL(0)
    GL_API_FUNC void DiscardFramebufferEXT(GLenum Target, GLsizei NumAttachments, const GLenum * Attachments) UGL_OPTIONAL_VOID
    GL_API_FUNC void CopyTextureLevels(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) UGL_OPTIONAL_VOID
    GL_API_FUNC void * MapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize, ResourceLockMode LockMode) UGL_REQUIRED(NULL)
    GL_API_FUNC void UnmapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize) UGL_REQUIRED_VOID
    GL_API_FUNC void UnmapBuffer(GLenum Type) UGL_REQUIRED_VOID
    GL_API_FUNC void GenQueries(GLsizei NumQueries, GLuint * QueryIDs) UGL_REQUIRED_VOID
    GL_API_FUNC void DeleteQueries(GLsizei NumQueries, const GLuint * QueryIDs) UGL_REQUIRED_VOID
    GL_API_FUNC void GetQueryObject(GLuint QueryId, QueryMode QueryMode, GLuint * OutResult) UGL_REQUIRED_VOID
    GL_API_FUNC void BindBufferBase(GLenum Target, GLuint Index, GLuint Buffer) UGL_REQUIRED_VOID
    GL_API_FUNC GLuint GetUniformBlockIndex(GLuint Program, const GLchar * UniformBlockName) UGL_REQUIRED(-1)
    GL_API_FUNC void UniformBlockBinding(GLuint Program, GLuint UniformBlockIndex, GLuint UniformBlockBinding) UGL_REQUIRED_VOID
    GL_API_FUNC void Uniform4uiv(GLint Location, GLsizei Count, const GLuint * Value) UGL_REQUIRED_VOID
    GL_API_FUNC void TexParameter(GLenum Target, GLenum Parameter, GLint Value) UGL_REQUIRED_VOID
    GL_API_FUNC void FramebufferTexture(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level) UGL_REQUIRED_VOID
    GL_API_FUNC void FramebufferTexture2D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level)
    {
        glFramebufferTexture2D(Target, Attachment, TexTarget, Texture, Level);
    }
    GL_API_FUNC void FramebufferTexture3D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint ZOffset) UGL_REQUIRED_VOID
    GL_API_FUNC void FramebufferTextureLayer(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint Layer) UGL_REQUIRED_VOID
    GL_API_FUNC void FramebufferRenderbuffer(GLenum Target, GLenum Attachment, GLenum RenderBufferTarget, GLuint RenderBuffer)
    {
        glFramebufferRenderbuffer(Target, Attachment, RenderBufferTarget, RenderBuffer);
    }
    GL_API_FUNC void BlitFramebuffer(GLint SrcX0, GLint SrcY0, GLint SrcX1, GLint SrcY1, GLint DstX0, GLint DstY0, GLint DstX1, GLint DstY1, GLbitfield Mask, GLenum Filter) UGL_REQUIRED_VOID
    GL_API_FUNC void DrawBuffers(GLsizei NumBuffers, const GLenum * Buffers) UGL_REQUIRED_VOID
    GL_API_FUNC void DepthRange(GLdouble Near, GLdouble Far) UGL_REQUIRED_VOID
    GL_API_FUNC void EnableIndexed(GLenum Parameter, GLuint Index) UGL_REQUIRED_VOID
    GL_API_FUNC void DisableIndexed(GLenum Parameter, GLuint Index) UGL_REQUIRED_VOID
    GL_API_FUNC void ColorMaskIndexed(GLuint Index, GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid * Pointer) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribIPointer(GLuint Index, GLint Size, GLenum Type, GLsizei Stride, const GLvoid * Pointer) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4Nsv(GLuint AttributeIndex, const GLshort * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4sv(GLuint AttributeIndex, const GLshort * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribI4sv(GLuint AttributeIndex, const GLshort * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribI4usv(GLuint AttributeIndex, const GLushort * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4Nubv(GLuint AttributeIndex, const GLubyte * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4ubv(GLuint AttributeIndex, const GLubyte * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribI4ubv(GLuint AttributeIndex, const GLubyte * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4Nbv(GLuint AttributeIndex, const GLbyte * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4bv(GLuint AttributeIndex, const GLbyte * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribI4bv(GLuint AttributeIndex, const GLbyte * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttrib4dv(GLuint AttributeIndex, const GLdouble * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribI4iv(GLuint AttributeIndex, const GLint * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void VertexAttribI4uiv(GLuint AttributeIndex, const GLuint * Values) UGL_REQUIRED_VOID
    GL_API_FUNC void DrawArraysInstanced(GLenum Mode, GLint First, GLsizei Count, GLsizei InstanceCount) UGL_REQUIRED_VOID
    GL_API_FUNC void DrawElementsInstanced(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid * Indices, GLsizei InstanceCount) UGL_REQUIRED_VOID
    GL_API_FUNC void DrawRangeElements(GLenum Mode, GLuint Start, GLuint End, GLsizei Count, GLenum Type, const GLvoid * Indices) UGL_REQUIRED_VOID
    GL_API_FUNC void ClearBufferfv(GLenum Buffer, GLint DrawBufferIndex, const GLfloat * Value) UGL_REQUIRED_VOID
    GL_API_FUNC void ClearBufferfi(GLenum Buffer, GLint DrawBufferIndex, GLfloat Depth, GLint Stencil) UGL_REQUIRED_VOID
    GL_API_FUNC void ClearBufferiv(GLenum Buffer, GLint DrawBufferIndex, const GLint * Value) UGL_REQUIRED_VOID
    GL_API_FUNC void ClearDepth(GLdouble Depth) UGL_REQUIRED_VOID
    GL_API_FUNC void TexImage3D(GLenum Target, GLint Level, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLenum Format, GLenum Type, const GLvoid * PixelData) UGL_REQUIRED_VOID
    GL_API_FUNC void CompressedTexImage3D(GLenum Target, GLint Level, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLsizei ImageSize, const GLvoid * PixelData) UGL_REQUIRED_VOID
    GL_API_FUNC void TexImage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations) UGL_REQUIRED_VOID
    GL_API_FUNC void TexBuffer(GLenum Target, GLenum InternalFormat, GLuint Buffer) UGL_REQUIRED_VOID
    GL_API_FUNC void TexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type, const GLvoid * PixelData) UGL_REQUIRED_VOID
    GL_API_FUNC void CopyTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height) UGL_REQUIRED_VOID
    GL_API_FUNC void GetCompressedTexImage(GLenum Target, GLint Level, GLvoid * OutImageData) UGL_REQUIRED_VOID
    GL_API_FUNC void GetTexImage(GLenum Target, GLint Level, GLenum Format, GLenum Type, GLvoid * OutPixelData) UGL_REQUIRED_VOID
    GL_API_FUNC void CopyBufferSubData(GLenum ReadTarget, GLenum WriteTarget, GLintptr ReadOffset, GLintptr WriteOffset, GLsizeiptr Size) UGL_REQUIRED_VOID
    GL_API_FUNC const ANSICHAR * GetStringIndexed(GLenum Name, GLuint Index) UGL_REQUIRED(NULL)
    //GL_API_FUNC GLuint GetMajorVersion() UGL_REQUIRED(0)
    //GL_API_FUNC GLuint GetMinorVersion() UGL_REQUIRED(0)
    //GL_API_FUNC ERHIFeatureLevel::Type GetFeatureLevel() UGL_REQUIRED(ERHIFeatureLevel::SM4)
    //GL_API_FUNC EShaderPlatform GetShaderPlatform() UGL_REQUIRED(SP_OPENGL_SM4)
    //GL_API_FUNC FString GetAdapterName() UGL_REQUIRED(TEXT(""))
    GL_API_FUNC void BlendFuncSeparatei(GLuint Buf, GLenum SrcRGB, GLenum DstRGB, GLenum SrcAlpha, GLenum DstAlpha) UGL_REQUIRED_VOID
    GL_API_FUNC void BlendEquationSeparatei(GLuint Buf, GLenum ModeRGB, GLenum ModeAlpha) UGL_REQUIRED_VOID
    GL_API_FUNC void BlendFunci(GLuint Buf, GLenum Src, GLenum Dst) UGL_REQUIRED_VOID
    GL_API_FUNC void BlendEquationi(GLuint Buf, GLenum Mode) UGL_REQUIRED_VOID
    GL_API_FUNC void PatchParameteri(GLenum Pname, GLint Value) UGL_REQUIRED_VOID
    GL_API_FUNC void BindImageTexture(GLuint Unit, GLuint Texture, GLint Level, GLboolean Layered, GLint Layer, GLenum Access, GLenum Format) UGL_REQUIRED_VOID
    GL_API_FUNC void DispatchCompute(GLuint NumGroupsX, GLuint NumGroupsY, GLuint NumGroupsZ) UGL_REQUIRED_VOID
    GL_API_FUNC void MemoryBarrier(GLbitfield Barriers) UGL_REQUIRED_VOID
    GL_API_FUNC bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, uint32 Flags) UGL_OPTIONAL(false)
    GL_API_FUNC void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type) UGL_REQUIRED_VOID
    GL_API_FUNC void CompressedTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLsizei ImageSize, const GLvoid * PixelData) UGL_REQUIRED_VOID
    GL_API_FUNC void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth) UGL_REQUIRED_VOID

    //static FPlatformOpenGLDevice*	CreateDevice() UGL_REQUIRED(NULL)
    //static FPlatformOpenGLContext*	CreateContext( FPlatformOpenGLDevice* Device, void* WindowHandle ) UGL_REQUIRED(NULL)

    GL_API_FUNC void BufferSubData(GLenum Target, GLintptr Offset, GLsizeiptr Size, const GLvoid * Data)
    {
        glBufferSubData(Target, Offset, Size, Data);
    }

    static const OpenGLCapability & GetCapability() { return _capability; }
    
protected:
    static OpenGLCapability _capability;
    
 };