#pragma once

#include "FOpenGLPlatform.h"
#include "FreRDResources.h"

namespace FRE
{
	class GLRenderTarget : public RDRenderTarget
	{
	public:
		GLRenderTarget(GLPlatformRenderSurfaceP hTarget) :
			_handle(hTarget)
		{

		}

		virtual ~GLRenderTarget()
		{
			GLSurfaceDestroy(_handle);
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLSurfaceUpdate(_handle, width, height);
		}

		void MakeCurrent(GLPlatformContextP hContext) const
		{
			GLContextMakeCurrent(hContext, _handle);
		}

		void Swap(GLPlatformContextP hContext)
		{
			GLContextSwap(hContext, _handle);
		}

	private:
		GLPlatformRenderSurfaceP _handle;
	};
}