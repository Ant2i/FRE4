#include "FOpenGLPlatform.h"

OpenGLCapability OpenGLAPI::_capability;

void OpenGLAPI::Init(const char * & extensions)
{
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_capability.MaxTextureImageUnits);
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_capability.MaxVertexTextureImageUnits);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_capability.MaxCombinedTextureImageUnits);
}

void OpenGL3API::Init(const char * & extensions)
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

void OpenGL4API::Init(const char * & extensions)
{
	OpenGL3API::Init(extensions);

	glGetIntegerv(GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, &_capability.MaxComputeTextureImageUnits);
	glGetIntegerv(GL_MAX_COMPUTE_UNIFORM_COMPONENTS, &_capability.MaxComputeUniformComponents);
	glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &_capability.MaxHullUniformComponents);
	glGetIntegerv(GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, &_capability.MaxDomainUniformComponents);
}