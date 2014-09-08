#pragma once

#include "gl\glew.h"
#include "windows.h"

#include "FOpenGL4API.h"
#include "FreAnyTypeArray.h"

#include <vector>
#include <memory>

#define FGL_MAX(a, b) a > b ? a : b

struct OpenGLWindowsAPI : public OpenGL4API
{
	GL_API_FUNC bool IsDebugContext()
	{
		return glIsEnabled(GL_DEBUG_OUTPUT) != GL_FALSE;
	}

	GL_API_FUNC void LabelObject(GLenum Type, GLuint Object, const ANSICHAR* Name)
	{
		if (glObjectLabel && IsDebugContext())
		{
			glObjectLabel(Type, Object, -1, Name);
		}
	}

	GL_API_FUNC void PushGroupMarker(const ANSICHAR * Name)
	{
		if (glPushDebugGroup && IsDebugContext())
		{
			glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 1, -1, Name);
		}
	}

	GL_API_FUNC void PopGroupMarker()
	{
		if (glPopDebugGroup && IsDebugContext())
		{
			glPopDebugGroup();
		}
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
			const bool bArrayTexture = Target == GL_TEXTURE_2D_ARRAY || Target == GL_TEXTURE_CUBE_MAP_ARRAY;

			for (uint32 MipIndex = 0; MipIndex < uint32(Levels); ++MipIndex)
			{
				glTexImage3D(
					Target,
					MipIndex,
					InternalFormat,
					FGL_MAX(1, (Width >> MipIndex)),
					FGL_MAX(1, (Height >> MipIndex)),
					bArrayTexture ? Depth : FGL_MAX(1, (Depth >> MipIndex)),
					0,
					Format,
					Type,
					NULL
					);
			}
		}
	}

	GL_API_FUNC void CopyImageSubData(GLuint SrcName, GLenum SrcTarget, GLint SrcLevel, GLint SrcX, GLint SrcY, GLint SrcZ, GLuint DstName, GLenum DstTarget, GLint DstLevel, GLint DstX, GLint DstY, GLint DstZ, GLsizei Width, GLsizei Height, GLsizei Depth)
	{
		glCopyImageSubData(SrcName, SrcTarget, SrcLevel, SrcX, SrcY, SrcZ, DstName, DstTarget, DstLevel, DstX, DstY, DstZ, Width, Height, Depth);
	}

	static void ProcessExtensions(const char * & extensions);
};

typedef OpenGLWindowsAPI TOpenGLAPI;

//------------------------------------------------------

struct GLWinSurfaceTarget
{
	GLWinSurfaceTarget(HWND hwnd, HDC hdc);
	~GLWinSurfaceTarget();

	bool Swap() const;
	void Resize(unsigned width, unsigned height);

	HWND Hwnd;
	HDC Hdc;
};

struct GLWinContext
{
	GLWinContext(HGLRC hrc);
	~GLWinContext();
	HGLRC Hglrc;
};

GLWinContext * CreateContext(HDC hdc, unsigned major, unsigned minor, GLWinContext * shared = nullptr, bool debug = false);
GLWinSurfaceTarget * CreateTarget(int pixelFormat, HWND parent);

bool WGLInitialize(HDC hdc, unsigned major, unsigned minor);
HGLRC WGLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc, bool debug);
PIXELFORMATDESCRIPTOR WGLGetDefaultPixelFormatDesc();

HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
void WinDestroyWindow(HWND hwnd);
DWORD WinGetLastError(const char ** msg);
