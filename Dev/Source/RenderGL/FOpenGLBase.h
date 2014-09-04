#pragma once

#include "FPlatformTypes.h"
#include "FPlatform.h"

#define UGL_REQUIRED_VOID			{ /*UE_LOG(LogOpenGL,Fatal,TEXT("%s is not supported."), ANSI_TO_TCHAR(__FUNCTION__));*/ }
#define UGL_REQUIRED(ReturnValue)	{ /*UE_LOG(LogOpenGL,Fatal,TEXT("%s is not supported."), ANSI_TO_TCHAR(__FUNCTION__)); return (ReturnValue);*/ }
#define UGL_OPTIONAL_VOID			{ }
#define UGL_OPTIONAL(ReturnValue)	{ /*return (ReturnValue);*/ }
#define check(ReturnValue)

typedef char ANSICHAR;
typedef GLsync UGLsync;

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

class FOpenGLBase
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

	//static FORCEINLINE bool SupportsMapBuffer(){ return true; }
	
    //static FORCEINLINE bool SupportsDepthTexture() { return true; }
    //static FORCEINLINE bool SupportsDrawBuffers() { return true; }
    //static FORCEINLINE bool SupportsPixelBuffers() { return true; }
    //static FORCEINLINE bool SupportsUniformBuffers() { return true; }
    //static FORCEINLINE bool SupportsStructuredBuffers() { return true; }
    //static FORCEINLINE bool SupportsTimestampQueries() { return true; }
    //static FORCEINLINE bool SupportsDisjointTimeQueries() { return false; }
    //static FORCEINLINE bool SupportsOcclusionQueries() { return true; }
    //static FORCEINLINE bool SupportsExactOcclusionQueries()	{ return true; }
    //static FORCEINLINE bool SupportsBlitFramebuffer() { return true; }
    //static FORCEINLINE bool SupportsDepthStencilReadSurface()			{ return true; }
    //static FORCEINLINE bool SupportsFloatReadSurface()					{ return true; }
    //static FORCEINLINE bool SupportsMultipleRenderTargets()				{ return true; }
    //static FORCEINLINE bool SupportsMultisampledTextures()				{ return true; }
    //static FORCEINLINE bool SupportsFences()							{ return true; }
    //static FORCEINLINE bool SupportsPolygonMode()						{ return true; }
    //static FORCEINLINE bool SupportsSamplerObjects()					{ return true; }
    //static FORCEINLINE bool SupportsTexture3D()							{ return true; }
    //static FORCEINLINE bool SupportsTextureLODBias()					{ return true; }
    //static FORCEINLINE bool SupportsTextureCompare()					{ return true; }
    //static FORCEINLINE bool SupportsTextureBaseLevel()					{ return true; }
    //static FORCEINLINE bool SupportsTextureMaxLevel()					{ return true; }
    //static FORCEINLINE bool SupportsInstancing()						{ return true; }
    //static FORCEINLINE bool SupportsVertexAttribInteger()				{ return true; }
    //static FORCEINLINE bool SupportsVertexAttribShort()					{ return true; }
    //static FORCEINLINE bool SupportsVertexAttribByte()					{ return true; }
    //static FORCEINLINE bool SupportsVertexAttribDouble()				{ return true; }
    //static FORCEINLINE bool SupportsVertexArrayObjects()				{ return false; }
    //static FORCEINLINE bool SupportsDrawIndexOffset()					{ return true; }
    //static FORCEINLINE bool SupportsResourceView()						{ return true; }
    //static FORCEINLINE bool SupportsCopyBuffer()						{ return true; }
    //static FORCEINLINE bool SupportsDiscardFrameBuffer()				{ return false; }
    //static FORCEINLINE bool SupportsIndexedExtensions()					{ return true; }
    //static FORCEINLINE bool SupportsVertexHalfFloat()					{ return true; }
    //static FORCEINLINE bool SupportsTextureFloat()						{ return true; }
    //static FORCEINLINE bool SupportsTextureHalfFloat()					{ return true; }
    //static FORCEINLINE bool SupportsColorBufferHalfFloat()				{ return true; }
    //static FORCEINLINE bool SupportsGSRenderTargetLayerSwitchingToMips() { return true; }
    //static FORCEINLINE bool SupportsShaderFramebufferFetch()			{ return false; }
    //static FORCEINLINE bool SupportsVertexArrayBGRA()					{ return true; }
    //static FORCEINLINE bool SupportsBGRA8888()							{ return true; }
    //static FORCEINLINE bool SupportsSRGB()								{ return true; }
    //static FORCEINLINE bool SupportsRGBA8()								{ return true; }
    //static FORCEINLINE bool SupportsDXT()								{ return true; }
    //static FORCEINLINE bool SupportsPVRTC()								{ return false; }
    //static FORCEINLINE bool SupportsATITC()								{ return false; }
    //static FORCEINLINE bool SupportsASTC()								{ return bSupportsASTC; }
    //static FORCEINLINE bool SupportsETC1()								{ return false; }
    //static FORCEINLINE bool SupportsETC2()								{ return false; }
    //static FORCEINLINE bool SupportsCombinedDepthStencilAttachment()	{ return true; }
    //static FORCEINLINE bool SupportsFastBufferData()					{ return true; }
    //static FORCEINLINE bool SupportsCopyImage()							{ return bSupportsCopyImage; }
    //static FORCEINLINE bool SupportsCopyTextureLevels()					{ return false; }
    //static FORCEINLINE bool SupportsTextureFilterAnisotropic()			{ return false; }
    //static FORCEINLINE bool SupportsPackedDepthStencil()				{ return true; }
    //static FORCEINLINE bool SupportsTextureCubeLodEXT()					{ return true; }
    //static FORCEINLINE bool SupportsShaderTextureLod()					{ return false; }
    //static FORCEINLINE bool SupportsSeparateAlphaBlend()				{ return false; }
    //static FORCEINLINE bool SupportsTessellation()						{ return false; }
    //static FORCEINLINE bool SupportsComputeShaders()					{ return false; }
    //static FORCEINLINE bool SupportsTextureView()						{ return false; }
    //static FORCEINLINE bool SupportsSeamlessCubeMap()					{ return false; }
    //static FORCEINLINE bool HasSamplerRestrictions()					{ return false; }
    //static FORCEINLINE bool HasHardwareHiddenSurfaceRemoval()			{ return false; }

    static FORCEINLINE GLenum GetDepthFormat()							{ return GL_DEPTH_COMPONENT16; }

    //static FORCEINLINE GLint GetMaxTextureImageUnits()			{ check(MaxTextureImageUnits != -1); return MaxTextureImageUnits; }
    //static FORCEINLINE GLint GetMaxVertexTextureImageUnits()	{ check(MaxVertexTextureImageUnits != -1); return MaxVertexTextureImageUnits; }
    //static FORCEINLINE GLint GetMaxGeometryTextureImageUnits()	{ check(MaxGeometryTextureImageUnits != -1); return MaxGeometryTextureImageUnits; }
    //static FORCEINLINE GLint GetMaxHullTextureImageUnits()		{ check(MaxHullTextureImageUnits != -1); return MaxHullTextureImageUnits; }
    //static FORCEINLINE GLint GetMaxDomainTextureImageUnits()	{ check(MaxDomainTextureImageUnits != -1); return MaxDomainTextureImageUnits; }
    //static FORCEINLINE GLint GetMaxComputeTextureImageUnits()	{ return 0; }
    //static FORCEINLINE GLint GetMaxCombinedTextureImageUnits()	{ check(MaxCombinedTextureImageUnits != -1); return MaxCombinedTextureImageUnits; }

    //static FORCEINLINE GLint GetFirstPixelTextureUnit()			{ return 0; }
    //static FORCEINLINE GLint GetFirstVertexTextureUnit()		{ return GetFirstPixelTextureUnit() + GetMaxTextureImageUnits(); }
    //static FORCEINLINE GLint GetFirstGeometryTextureUnit()		{ return GetFirstVertexTextureUnit() + GetMaxVertexTextureImageUnits(); }
    //static FORCEINLINE GLint GetFirstHullTextureUnit()			{ return GetFirstGeometryTextureUnit() + GetMaxGeometryTextureImageUnits(); }
    //static FORCEINLINE GLint GetFirstDomainTextureUnit()		{ return GetFirstHullTextureUnit() + GetMaxHullTextureImageUnits(); }

    //static FORCEINLINE GLint GetFirstComputeTextureUnit()		{ return 0; }
    //static FORCEINLINE GLint GetFirstComputeUAVUnit()			{ return 0; }

    //static FORCEINLINE GLint GetMaxPixelUniformComponents()		{ check(MaxPixelUniformComponents != -1); return MaxPixelUniformComponents; }
    //static FORCEINLINE GLint GetMaxVertexUniformComponents()	{ check(MaxVertexUniformComponents != -1); return MaxVertexUniformComponents; }
    //static FORCEINLINE GLint GetMaxGeometryUniformComponents()	{ check(MaxGeometryUniformComponents != -1); return MaxGeometryUniformComponents; }
    //static FORCEINLINE GLint GetMaxHullUniformComponents()		{ check(MaxHullUniformComponents != -1); return MaxHullUniformComponents; }
    //static FORCEINLINE GLint GetMaxDomainUniformComponents()	{ check(MaxDomainUniformComponents != -1); return MaxDomainUniformComponents; }
    //static FORCEINLINE GLint GetMaxComputeUniformComponents()	{ return 0; }

    //static FORCEINLINE bool IsDebugContent()					{ return false; }
    //static FORCEINLINE void InitDebugContext()					{ }


    // Silently ignored if not implemented:
    static FORCEINLINE void QueryTimestampCounter(GLuint QueryID) UGL_OPTIONAL_VOID
    static FORCEINLINE void BeginQuery(GLenum QueryType, GLuint QueryId) UGL_OPTIONAL_VOID
    static FORCEINLINE void EndQuery(GLenum QueryType) UGL_OPTIONAL_VOID
    static FORCEINLINE void GetQueryObject(GLuint QueryId, QueryMode QueryMode, uint64 * OutResult) UGL_OPTIONAL_VOID
    static FORCEINLINE void BindFragDataLocation(GLuint Program, GLuint Color, const GLchar * Name) UGL_OPTIONAL_VOID
    static FORCEINLINE void ReadBuffer(GLenum Mode) UGL_OPTIONAL_VOID
    static FORCEINLINE void DrawBuffer(GLenum Mode) UGL_OPTIONAL_VOID
    static FORCEINLINE void DeleteSync(UGLsync Sync) UGL_OPTIONAL_VOID
    static FORCEINLINE UGLsync FenceSync(GLenum Condition, GLbitfield Flags) UGL_OPTIONAL(0)
    static FORCEINLINE bool IsSync(UGLsync Sync) UGL_OPTIONAL(false)
    static FORCEINLINE FenceResult ClientWaitSync(UGLsync Sync, GLbitfield Flags, GLuint64 Timeout) UGL_OPTIONAL(FR_WaitFailed)
    static FORCEINLINE void GenSamplers(GLsizei Count, GLuint * Samplers) UGL_OPTIONAL_VOID
    static FORCEINLINE void DeleteSamplers(GLsizei Count, GLuint * Samplers) UGL_OPTIONAL_VOID
    static FORCEINLINE void SetSamplerParameter(GLuint Sampler, GLenum Parameter, GLint Value) UGL_OPTIONAL_VOID
    static FORCEINLINE void BindSampler(GLuint Unit, GLuint Sampler) UGL_OPTIONAL_VOID
    static FORCEINLINE void PolygonMode(GLenum Face, GLenum Mode) UGL_OPTIONAL_VOID
    static FORCEINLINE void VertexAttribDivisor(GLuint Index, GLuint Divisor) UGL_OPTIONAL_VOID
    static FORCEINLINE void PushGroupMarker(const ANSICHAR * Name) UGL_OPTIONAL_VOID
    static FORCEINLINE void PopGroupMarker() UGL_OPTIONAL_VOID
    static FORCEINLINE void LabelObject(GLenum Type, GLuint Object, const ANSICHAR * Name) UGL_OPTIONAL_VOID
    static FORCEINLINE GLsizei GetLabelObject(GLenum Type, GLuint Object, GLsizei BufferSize, ANSICHAR * OutName) UGL_OPTIONAL(0)
    static FORCEINLINE void DiscardFramebufferEXT(GLenum Target, GLsizei NumAttachments, const GLenum * Attachments) UGL_OPTIONAL_VOID
    static FORCEINLINE void CopyTextureLevels(GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount) UGL_OPTIONAL_VOID

    // Will assert at run-time if not implemented:
    static FORCEINLINE void * MapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize, ResourceLockMode LockMode) UGL_REQUIRED(NULL)
    static FORCEINLINE void UnmapBufferRange(GLenum Type, uint32 InOffset, uint32 InSize) UGL_REQUIRED_VOID
    static FORCEINLINE void UnmapBuffer(GLenum Type) UGL_REQUIRED_VOID
    static FORCEINLINE void GenQueries(GLsizei NumQueries, GLuint * QueryIDs) UGL_REQUIRED_VOID
    static FORCEINLINE void DeleteQueries(GLsizei NumQueries, const GLuint * QueryIDs) UGL_REQUIRED_VOID
    static FORCEINLINE void GetQueryObject(GLuint QueryId, QueryMode QueryMode, GLuint * OutResult) UGL_REQUIRED_VOID
    static FORCEINLINE void BindBufferBase(GLenum Target, GLuint Index, GLuint Buffer) UGL_REQUIRED_VOID
    static FORCEINLINE GLuint GetUniformBlockIndex(GLuint Program, const GLchar * UniformBlockName) UGL_REQUIRED(-1)
    static FORCEINLINE void UniformBlockBinding(GLuint Program, GLuint UniformBlockIndex, GLuint UniformBlockBinding) UGL_REQUIRED_VOID
    static FORCEINLINE void Uniform4uiv(GLint Location, GLsizei Count, const GLuint * Value) UGL_REQUIRED_VOID
    static FORCEINLINE void TexParameter(GLenum Target, GLenum Parameter, GLint Value) UGL_REQUIRED_VOID
    static FORCEINLINE void FramebufferTexture(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level) UGL_REQUIRED_VOID
    static FORCEINLINE void FramebufferTexture2D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level)
    {
        glFramebufferTexture2D(Target, Attachment, TexTarget, Texture, Level);
    }
    static FORCEINLINE void FramebufferTexture3D(GLenum Target, GLenum Attachment, GLenum TexTarget, GLuint Texture, GLint Level, GLint ZOffset) UGL_REQUIRED_VOID
    static FORCEINLINE void FramebufferTextureLayer(GLenum Target, GLenum Attachment, GLuint Texture, GLint Level, GLint Layer) UGL_REQUIRED_VOID
    static FORCEINLINE void FramebufferRenderbuffer(GLenum Target, GLenum Attachment, GLenum RenderBufferTarget, GLuint RenderBuffer)
    {
        glFramebufferRenderbuffer(Target, Attachment, RenderBufferTarget, RenderBuffer);
    }
    static FORCEINLINE void BlitFramebuffer(GLint SrcX0, GLint SrcY0, GLint SrcX1, GLint SrcY1, GLint DstX0, GLint DstY0, GLint DstX1, GLint DstY1, GLbitfield Mask, GLenum Filter) UGL_REQUIRED_VOID
    static FORCEINLINE void DrawBuffers(GLsizei NumBuffers, const GLenum * Buffers) UGL_REQUIRED_VOID
    static FORCEINLINE void DepthRange(GLdouble Near, GLdouble Far) UGL_REQUIRED_VOID
    static FORCEINLINE void EnableIndexed(GLenum Parameter, GLuint Index) UGL_REQUIRED_VOID
    static FORCEINLINE void DisableIndexed(GLenum Parameter, GLuint Index) UGL_REQUIRED_VOID
    static FORCEINLINE void ColorMaskIndexed(GLuint Index, GLboolean Red, GLboolean Green, GLboolean Blue, GLboolean Alpha) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribPointer(GLuint Index, GLint Size, GLenum Type, GLboolean Normalized, GLsizei Stride, const GLvoid * Pointer) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribIPointer(GLuint Index, GLint Size, GLenum Type, GLsizei Stride, const GLvoid * Pointer) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4Nsv(GLuint AttributeIndex, const GLshort * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4sv(GLuint AttributeIndex, const GLshort * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribI4sv(GLuint AttributeIndex, const GLshort * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribI4usv(GLuint AttributeIndex, const GLushort * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4Nubv(GLuint AttributeIndex, const GLubyte * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4ubv(GLuint AttributeIndex, const GLubyte * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribI4ubv(GLuint AttributeIndex, const GLubyte * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4Nbv(GLuint AttributeIndex, const GLbyte * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4bv(GLuint AttributeIndex, const GLbyte * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribI4bv(GLuint AttributeIndex, const GLbyte * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttrib4dv(GLuint AttributeIndex, const GLdouble * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribI4iv(GLuint AttributeIndex, const GLint * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void VertexAttribI4uiv(GLuint AttributeIndex, const GLuint * Values) UGL_REQUIRED_VOID
    static FORCEINLINE void DrawArraysInstanced(GLenum Mode, GLint First, GLsizei Count, GLsizei InstanceCount) UGL_REQUIRED_VOID
    static FORCEINLINE void DrawElementsInstanced(GLenum Mode, GLsizei Count, GLenum Type, const GLvoid * Indices, GLsizei InstanceCount) UGL_REQUIRED_VOID
    static FORCEINLINE void DrawRangeElements(GLenum Mode, GLuint Start, GLuint End, GLsizei Count, GLenum Type, const GLvoid * Indices) UGL_REQUIRED_VOID
    static FORCEINLINE void ClearBufferfv(GLenum Buffer, GLint DrawBufferIndex, const GLfloat * Value) UGL_REQUIRED_VOID
    static FORCEINLINE void ClearBufferfi(GLenum Buffer, GLint DrawBufferIndex, GLfloat Depth, GLint Stencil) UGL_REQUIRED_VOID
    static FORCEINLINE void ClearBufferiv(GLenum Buffer, GLint DrawBufferIndex, const GLint * Value) UGL_REQUIRED_VOID
    static FORCEINLINE void ClearDepth(GLdouble Depth) UGL_REQUIRED_VOID
    static FORCEINLINE void TexImage3D(GLenum Target, GLint Level, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLenum Format, GLenum Type, const GLvoid * PixelData) UGL_REQUIRED_VOID
    static FORCEINLINE void CompressedTexImage3D(GLenum Target, GLint Level, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLint Border, GLsizei ImageSize, const GLvoid * PixelData) UGL_REQUIRED_VOID
    static FORCEINLINE void TexImage2DMultisample(GLenum Target, GLsizei Samples, GLint InternalFormat, GLsizei Width, GLsizei Height, GLboolean FixedSampleLocations) UGL_REQUIRED_VOID
    static FORCEINLINE void TexBuffer(GLenum Target, GLenum InternalFormat, GLuint Buffer) UGL_REQUIRED_VOID
    static FORCEINLINE void TexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type, const GLvoid * PixelData) UGL_REQUIRED_VOID
    static FORCEINLINE void	CopyTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLint X, GLint Y, GLsizei Width, GLsizei Height) UGL_REQUIRED_VOID
    static FORCEINLINE void GetCompressedTexImage(GLenum Target, GLint Level, GLvoid * OutImageData) UGL_REQUIRED_VOID
    static FORCEINLINE void GetTexImage(GLenum Target, GLint Level, GLenum Format, GLenum Type, GLvoid * OutPixelData) UGL_REQUIRED_VOID
    static FORCEINLINE void CopyBufferSubData(GLenum ReadTarget, GLenum WriteTarget, GLintptr ReadOffset, GLintptr WriteOffset, GLsizeiptr Size) UGL_REQUIRED_VOID
    static FORCEINLINE const ANSICHAR * GetStringIndexed(GLenum Name, GLuint Index) UGL_REQUIRED(NULL)
    //static FORCEINLINE GLuint GetMajorVersion() UGL_REQUIRED(0)
    //static FORCEINLINE GLuint GetMinorVersion() UGL_REQUIRED(0)
    //static FORCEINLINE ERHIFeatureLevel::Type GetFeatureLevel() UGL_REQUIRED(ERHIFeatureLevel::SM4)
    //static FORCEINLINE EShaderPlatform GetShaderPlatform() UGL_REQUIRED(SP_OPENGL_SM4)
    //static FORCEINLINE FString GetAdapterName() UGL_REQUIRED(TEXT(""))
    static FORCEINLINE void BlendFuncSeparatei(GLuint Buf, GLenum SrcRGB, GLenum DstRGB, GLenum SrcAlpha, GLenum DstAlpha) UGL_REQUIRED_VOID
    static FORCEINLINE void BlendEquationSeparatei(GLuint Buf, GLenum ModeRGB, GLenum ModeAlpha) UGL_REQUIRED_VOID
    static FORCEINLINE void BlendFunci(GLuint Buf, GLenum Src, GLenum Dst) UGL_REQUIRED_VOID
    static FORCEINLINE void BlendEquationi(GLuint Buf, GLenum Mode) UGL_REQUIRED_VOID
    static FORCEINLINE void PatchParameteri(GLenum Pname, GLint Value) UGL_REQUIRED_VOID
    static FORCEINLINE void BindImageTexture(GLuint Unit, GLuint Texture, GLint Level, GLboolean Layered, GLint Layer, GLenum Access, GLenum Format) UGL_REQUIRED_VOID
    static FORCEINLINE void DispatchCompute(GLuint NumGroupsX, GLuint NumGroupsY, GLuint NumGroupsZ) UGL_REQUIRED_VOID
    static FORCEINLINE void MemoryBarrier(GLbitfield Barriers) UGL_REQUIRED_VOID
    static FORCEINLINE bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, uint32 Flags) UGL_OPTIONAL(false)
    static FORCEINLINE void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type) UGL_REQUIRED_VOID
    static FORCEINLINE void CompressedTexSubImage3D(GLenum Target, GLint Level, GLint XOffset, GLint YOffset, GLint ZOffset, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLsizei ImageSize, const GLvoid * PixelData) UGL_REQUIRED_VOID
    static FORCEINLINE void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth) UGL_REQUIRED_VOID

    //static FPlatformOpenGLDevice*	CreateDevice() UGL_REQUIRED(NULL)
    //static FPlatformOpenGLContext*	CreateContext( FPlatformOpenGLDevice* Device, void* WindowHandle ) UGL_REQUIRED(NULL)

    static FORCEINLINE void BufferSubData(GLenum Target, GLintptr Offset, GLsizeiptr Size, const GLvoid * Data)
    {
        glBufferSubData(Target, Offset, Size, Data);
    }

protected:
    //static GLint MaxTextureImageUnits;
    //static GLint MaxCombinedTextureImageUnits;
    //static GLint MaxVertexTextureImageUnits;
    //static GLint MaxGeometryTextureImageUnits;
    //static GLint MaxHullTextureImageUnits;
    //static GLint MaxDomainTextureImageUnits;
    //static GLint MaxVertexUniformComponents;
    //static GLint MaxPixelUniformComponents;
    //static GLint MaxGeometryUniformComponents;
    //static GLint MaxHullUniformComponents;
    //static GLint MaxDomainUniformComponents;

    ///** GL_KHR_texture_compression_astc_ldr */
    //static bool bSupportsASTC;

    ///** GL_ARB_copy_image */
    //static bool bSupportsCopyImage;

    ///** GL_ARB_seamless_cube_map */
    //static bool bSupportsSeamlessCubemap;
};