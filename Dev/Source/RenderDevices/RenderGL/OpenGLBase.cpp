#include "OpenGLBase.h"
#include <string>
#include <cstring>

namespace FRE
{
	OpenGLCapability OpenGLAPI::_capability;
	
	void OpenGLAPI::Init(const char * extensions)
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_capability.MaxTextureImageUnits);
		glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_capability.MaxVertexTextureImageUnits);
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_capability.MaxCombinedTextureImageUnits);

		_capability.SupportCopyImage = strstr(extensions, "GL_ARB_copy_image") != nullptr;
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
	
		_capability.SupportPixelBuffers = true;
		_capability.SupportUniformBuffers = true;
		_capability.SupportStructuredBuffers = true;
	
		GLint timestampQueryBits = 0;
		glGetQueryiv(GL_TIMESTAMP, GL_QUERY_COUNTER_BITS, &timestampQueryBits);
		_capability.SupportTimestampQueries = timestampQueryBits > 0;
	
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
		
		_capability.SupportTextureCompare = true;
		_capability.SupportTextureBaseLevel = true;
		_capability.SupportTextureMaxLevel = true;
		_capability.SupportInstancing = true;
		
		_capability.SupportDrawIndexOffset = true;
		
		_capability.SupportTextureBuffer = true;
		_capability.SupportCopyBuffer = true;
		
		_capability.SupportDiscardFrameBuffer = false;
		_capability.SupportVertexHalfFloat = true;
	
		_capability.SupportTextureHalfFloat = true;
		_capability.SupportColorBufferHalfFloat = true;
		_capability.SupportGSRenderTargetLayerSwitchingToMips = false;
		
		_capability.SupportBGRA8888 = strstr(extensions, "EXT_texture_format_BGRA8888") != nullptr;
		_capability.SupportSRGB = strstr(extensions, "EXT_texture_sRGB") != nullptr;
		_capability.SupportRGBA8 = true;
		_capability.SupportDXT = strstr(extensions, "EXT_texture_compression_s3tc") != nullptr;
		_capability.SupportPVRTC = strstr(extensions, "IMG_texture_compression_pvrtc") != nullptr;
		_capability.SupportRGTC = strstr(extensions, "EXT_texture_compression_rgtc") != nullptr;

		_capability.SupportCombinedDepthStencilAttachment = true;
		_capability.SupportFastBufferData = true;
		//GL_APPLE_copy_texture_levels
		_capability.SupportCopyTextureLevels = false;
		_capability.SupportPackedDepthStencil = false;
		_capability.SupportTextureCubeLodEXT = false;
		
		_capability.SupportShaderTextureLod = false;
		_capability.SupportSeparateAlphaBlend = true;

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

		_capability.SupportTessellation = true;
		_capability.SupportComputeShaders = true;
	}

	#endif
}
