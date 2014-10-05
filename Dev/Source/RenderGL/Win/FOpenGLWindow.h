#pragma once

#include "FOpenGLWinDecl.h"
#include "FOpenGL4API.h"
#include "windows.h"

#include <vector>
#include <memory>

struct OpenGLWindowsAPI : public OpenGL4API
{
	GL_API_FUNC bool IsDebugContext()
	{
		return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}

	GL_API_FUNC void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)
	{
		if (glObjectLabel)
			glObjectLabel(Type, Object, -1, Name);
	}

	GL_API_FUNC void PushGroupMarker(const ANSICHAR * Name)
	{
		if (glPushDebugGroup)
			glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 1, -1, Name);
	}

	GL_API_FUNC void PopGroupMarker()
	{
		if (glPopDebugGroup)
			glPopDebugGroup();
	}

	GL_API_FUNC bool TexStorage2D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLenum Format, GLenum Type, uint32 Flags)
	{
		if (glTexStorage2D)
		{
			glTexStorage2D(Target, Levels, InternalFormat, Width, Height);
			return true;
		}
		return false;
	}

	GL_API_FUNC void TexStorage3D(GLenum Target, GLint Levels, GLint InternalFormat, GLsizei Width, GLsizei Height, GLsizei Depth, GLenum Format, GLenum Type)
	{
		if (glTexStorage3D)
		{
			glTexStorage3D(Target, Levels, InternalFormat, Width, Height, Depth);
		}
		else
		{
			__glTexStorage3D(Target, Levels, InternalFormat, Width, Height, Depth, Format, Type);
		}
	}
};

typedef OpenGLWindowsAPI TOpenGLAPI;

//------------------------------------------------------

struct WGLSurface
{
	WGLSurface(HWND hwnd, HDC hdc);
	~WGLSurface();

	bool Swap() const;
	void Resize(unsigned width, unsigned height);

	HWND Hwnd;
	HDC Hdc;
};

struct WGLContext
{
	WGLContext(HGLRC hrc);
	~WGLContext();

	HGLRC Hglrc;
};

WGLContext * CreateContext(HDC hdc, unsigned major, unsigned minor, WGLContext * shared = nullptr, bool debug = false);
WGLSurface * CreateWindowSurface(int pixelFormat, HWND parent);

bool WGLInitialize(HDC hdc, unsigned major, unsigned minor);
HGLRC WGLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc, bool debug);
PIXELFORMATDESCRIPTOR WGLGetDefaultPixelFormatDesc();

HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
void WinDestroyWindow(HWND hwnd);
DWORD WinGetLastError(const char ** msg);
