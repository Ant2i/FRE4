#pragma once

#include "RDResources.h"
#include "GLPlatform.h"

namespace FRE
{
	class GLRenderSurface : public RDRenderOutput
	{
	public:
		GLRenderSurface(PGLSurface surface) :
			_handle(surface)
		{

		}

		virtual ~GLRenderSurface()
		{
			PGLSurfaceDestroy(_handle);
		}

		void MakeCurrent(PGLContext hContext) const
		{
			PGLContextMakeCurrent(hContext, _handle);
		}

		void Swap()
		{
			PGLSwapBuffers(_handle);
		}

	private:
		PGLSurface _handle;
	};
}
