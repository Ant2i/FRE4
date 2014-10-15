#include "FOpenGLPlatform.h"
#include <string>

OpenGLCapability OpenGLAPI::_capability;

void OpenGLAPI::Init(const char * extensions)
{
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_capability.MaxTextureImageUnits);
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_capability.MaxVertexTextureImageUnits);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_capability.MaxCombinedTextureImageUnits);
}

const char * OpenGLAPI::GetExtensionString() 
{
	static std::string extensionString;
	extensionString.clear();

	auto stringOutput = (const char *)glGetString(GL_EXTENSIONS);
	if (stringOutput)
	{
		extensionString += std::string(stringOutput);
		extensionString += std::string(" ");
	}

	return extensionString.data();
}

//-----------------------------------------------------------------------------

#ifdef OPENGL3_API

void OpenGL3API::Init(const char * extensions)
{
	OpenGLAPI::Init(extensions);

	_capability.SupportMapBuffer = true;
	_capability.SupportPixelBuffers = true;
	_capability.SupportUniformBuffers = true;
	_capability.SupportStructuredBuffers = true;

	GLint TimestampQueryBits = 0;
	glGetQueryiv(GL_TIMESTAMP, GL_QUERY_COUNTER_BITS, &TimestampQueryBits);
	_capability.SupportTimestampQueries = TimestampQueryBits > 0;

	_capability.SupportOcclusionQueries = true;
	_capability.SupportExactOcclusionQueries = true;
	_capability.SupportBlitFramebuffer = true;
	_capability.SupportFloatReadSurface = true;
	_capability.SupportMultipleRenderTargets = true;
	_capability.SupportMultisampledTextures = true;
	_capability.SupportFences = true;

	_capability.SupportSamplerObjects = true;
	_capability.SupportTexture3D = true;

	_capability.SupportTextureLODBias = true;
	//GL_TEXTURE_COMPARE_...
	_capability.SupportTextureCompare = true;
	_capability.SupportTextureBaseLevel = true;
	_capability.SupportTextureMaxLevel = true;
	//Support draw instance.
	_capability.SupportInstancing = true;

	//Support glDrawRangeElements
	_capability.SupportDrawIndexOffset = true;
	//Support 
	_capability.SupportTextureBuffer = true;
	_capability.SupportCopyBuffer = true;
	// glDiscardFramebufferEXT
	_capability.SupportDiscardFrameBuffer = false;
	_capability.SupportVertexHalfFloat = true;

	
	_capability.SupportTextureHalfFloat = true;
	bool SupportColorBufferHalfFloat = false;
	bool SupportGSRenderTargetLayerSwitchingToMips = false;
	
	
	bool SupportBGRA8888 = false;
	bool SupportSRGB = false;
	bool SupportRGBA8 = false;
	bool SupportDXT = false;
	bool SupportPVRTC = false;
	bool SupportATITC = false;
	bool SupportASTC = false;
	bool SupportETC1 = false;
	bool SupportETC2 = false;
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


	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &_capability.MaxVertexUniformComponents);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &_capability.MaxPixelUniformComponents);
	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &_capability.MaxGeometryUniformComponents);

	glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &_capability.MaxGeometryTextureImageUnits);
	glGetIntegerv(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS, &_capability.MaxHullTextureImageUnits);
	glGetIntegerv(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS, &_capability.MaxDomainTextureImageUnits);

	glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &_capability.MaxTextureBufferSize);
	

	glGetIntegerv(GL_MAJOR_VERSION, &_capability.Version.Major);
	glGetIntegerv(GL_MINOR_VERSION, &_capability.Version.Minor);
}

const char * OpenGL3API::GetExtensionString()
{
	static std::string extensionString;
	extensionString.clear();

	GLint numExtension = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &numExtension);
	for (GLint i = 0; i < numExtension; ++i)
	{
		std::string strExt((const char *)glGetStringi(GL_EXTENSIONS, i));
		extensionString += strExt;
		extensionString += std::string(" ");
	}

	return extensionString.data();
}

#endif

//-----------------------------------------------------------------------------

#ifdef OPENGL4_API

void OpenGL4API::Init(const char * extensions)
{
	OpenGL3API::Init(extensions);

	glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, &_capability.MaxComputeTextureImageUnits);
	glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &_capability.MaxComputeUniformComponents);
	glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &_capability.MaxHullUniformComponents);
	glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, &_capability.MaxDomainUniformComponents);
}

#endif