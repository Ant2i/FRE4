#include "OpenGLBase.h"
#include "FAssert.h"
#include <sstream>

char * GetOpenGLDebugStringorSource(GLenum source)
{
	switch (source)
	{
	case GL_DEBUG_SOURCE_API_ARB: return "API";
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: return "Window System";
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: return "Shader Compiler";
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: return "Third Party";
	case GL_DEBUG_SOURCE_APPLICATION_ARB: return "Application";
	case GL_DEBUG_SOURCE_OTHER_ARB: return "Other";
	}
	return "";
}

char * GetOpenGLDebugStringForSeverity(GLenum severity)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB: return "High";
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: return "Medium";
	case GL_DEBUG_SEVERITY_LOW_ARB: return "Low";
	}
	return "";
}

char * GetOpenGLDebugStringForType(GLenum type)
{
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB: return "Error";
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: return "Deprecated Behaviour";
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: return "Undefined Behaviour";
	case GL_DEBUG_TYPE_PORTABILITY_ARB: return "Portability Issue";
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: return "Performance Issue";
	case GL_DEBUG_TYPE_OTHER_ARB: return "Other";
	}
	return "";
}

static void APIENTRY OpenGLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, GLvoid *userParam)
{
	std::stringstream ss;
	ss << "[" << GetOpenGLDebugStringForType(type) << "]["
		<< GetOpenGLDebugStringorSource(source) << "][" << id << "]["
		<< GetOpenGLDebugStringForSeverity(severity) << "] " << message;

	Output::_OutputDebugString(ss.str().c_str());

	if (severity == GL_DEBUG_SEVERITY_HIGH_ARB && type == GL_DEBUG_TYPE_ERROR_ARB)
	{
		//P_BREAKPOINT;
	}
}

namespace FRE
{
	void InitOpenGLContextForDebug()
	{
		if (glDebugMessageCallbackARB)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			glDebugMessageCallbackARB(OpenGLDebugMessageCallback, nullptr);
		}
	}
}