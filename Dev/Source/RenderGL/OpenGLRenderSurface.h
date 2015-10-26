#pragma once

#include "RDResources.h"
#include "GLPlatform.h"

namespace FRE
{
	class GLRenderSurface : public RDRenderOutput
	{
	public:
		GLRenderSurface(GLPSurface surface) :
			_handle(surface)
		{

		}

		virtual ~GLRenderSurface()
		{
			PGLSurfaceDestroy(_handle);
		}

		void MakeCurrent(GLPContext hContext) const
		{
			PGLContextMakeCurrent(hContext, _handle);
		}

		void Swap()
		{
			PGLSwapBuffers(_handle);
		}

	private:
		GLPSurface _handle;
	};
}