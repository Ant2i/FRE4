#pragma once

#include "FreGLWinTypeObj.h"
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

		static GLWinContext * Create(HDC hdc, unsigned major, unsigned minor, GLWinContext * shared = nullptr);
		~GLWinContext();

		HGLRC GetHglrc() const { return _hglrc; }
		
		static bool CheckGLCapabilities(HDC hdc, unsigned major, unsigned minor);
		static HGLRC CreateGLContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc);
		static PIXELFORMATDESCRIPTOR GetDefaultPixelFormatDesc();

	private:
		GLWinContext(HGLRC hrc);

		HGLRC _hglrc;
		unsigned _pixelFormat;
	};
}