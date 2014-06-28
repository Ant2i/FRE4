#pragma once

#include "GLPlatform.h"
#include "GLWinTypeObj.h"
#include "windows.h"

namespace FRE
{
	class GLWinContext
	{
	public:
		enum
		{
			Type = GLTypeObject::Context
		};

		static GLWinContext * Create(HDC hdc, GLWinContext * shared = nullptr);
		~GLWinContext();

		HGLRC GetHglrc() const { return _hglrc; }
		
		static bool Init(HDC hdc);
		static HGLRC CreateGLContext(HDC hdc, HGLRC shareHrc);
		static PIXELFORMATDESCRIPTOR GetDefaultPixelFormatDesc();

	private:
		GLWinContext(HGLRC hrc);

		HGLRC _hglrc;
		unsigned _pixelFormat;
	};
}