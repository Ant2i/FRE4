#pragma once

#include "GLWinTypeObj.h"
#include "windows.h"

namespace FRE
{
	class GLWinSurfaceTarget
	{
	public:
		enum
		{
			Type = GLTypeObject::Surface
		};

		static GLWinSurfaceTarget * Create(int pixelFormat, HWND parent);
		~GLWinSurfaceTarget();

		HDC GetHDC() const 
		{ 
			return _hdc; 
		}

		bool Swap() const
		{
			return SwapBuffers(_hdc) == TRUE;
		}

		void Resize(unsigned width, unsigned height);

	private:
		GLWinSurfaceTarget(HWND hwnd, HDC hdc);

		HWND _hwnd;
		HDC _hdc;
	};

	HWND _CreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
	void _DestroyWindow(HWND hwnd);
	DWORD _GetLastError(const char ** msg);
}