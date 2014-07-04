#include "FreGLDebug.h"
#include "GLBase.h"
#include <sstream>

std::string GetStringForSource(GLenum source)
{
	switch (source)
	{
	case GL_DEBUG_SOURCE_API_ARB: return ("API");
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB: return ("Window System");
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: return ("Shader Compiler");
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB: return ("Third Party");
	case GL_DEBUG_SOURCE_APPLICATION_ARB: return ("Application");
	case GL_DEBUG_SOURCE_OTHER_ARB: return ("Other");
	}
	return ("");
}

std::string GetStringForSeverity(GLenum severity)
{
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB: return ("High");
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: return ("Medium");
	case GL_DEBUG_SEVERITY_LOW_ARB: return ("Low");
	}
	return ("");
}

std::string GetStringForType(GLenum type)
{
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR_ARB: return ("Error");
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: return ("Deprecated Behaviour");
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB: return ("Undefined Behaviour");
	case GL_DEBUG_TYPE_PORTABILITY_ARB: return ("Portability Issue");
	case GL_DEBUG_TYPE_PERFORMANCE_ARB: return ("Performance Issue");
	case GL_DEBUG_TYPE_OTHER_ARB: return ("Other");
	}
	return ("");
}


void _DebugLog(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
{
	std::stringstream ss;
	ss << " -- \n" << 
		"Type: " << GetStringForType(type) << 
		"; Source: " << GetStringForSource(source) << 
		"; ID: " << id << 
		"; Severity: " << GetStringForSeverity(severity) << "\n" << message << "\n";

	//#if (defined _WIN32 || defined _LINUX)
	//		printStack();
	//#endif

	//	exit(1);
}

FRE::GLDebug::CallbackFunc sDebugCallbackFunction;

namespace FRE
{
	bool GLDebug::Enable()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallbackARB((GLDEBUGPROCARB)_DebugLog, nullptr);
		return true;
	}

	void GLDebug::Disable()
	{
		glDisable(GL_DEBUG_OUTPUT);
	}

	void GLDebug::SetCallBack(const CallbackFunc & cb)
	{
		sDebugCallbackFunction = cb;
	}
}