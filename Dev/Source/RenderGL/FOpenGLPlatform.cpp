#include "FOpenGLPlatform.h"

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

void OpenGL3API::Init(const char * extensions)
{
	OpenGLAPI::Init(extensions);

	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &_capability.MaxVertexUniformComponents);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &_capability.MaxPixelUniformComponents);
	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &_capability.MaxGeometryUniformComponents);

	glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, &_capability.MaxGeometryTextureImageUnits);
	glGetIntegerv(GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS, &_capability.MaxHullTextureImageUnits);
	glGetIntegerv(GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS, &_capability.MaxDomainTextureImageUnits);

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

//-----------------------------------------------------------------------------

void OpenGL4API::Init(const char * extensions)
{
	OpenGL3API::Init(extensions);

	glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, &_capability.MaxComputeTextureImageUnits);
	glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &_capability.MaxComputeUniformComponents);
	glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &_capability.MaxHullUniformComponents);
	glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, &_capability.MaxDomainUniformComponents);
}