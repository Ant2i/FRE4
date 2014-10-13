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
			GLPlatformSurfaceDestroy(_handle);
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLPlatformSurfaceUpdate(_handle, width, height);
		}

		void MakeCurrent(GLPlatformContextP hContext) const
		{
			GLPlatformContextMakeCurrent(hContext, _handle);
		}

		void Swap(GLPlatformContextP hContext)
		{
			GLPlatformContextSwap(hContext, _handle);
		}

	private:
		GLPlatformRenderSurfaceP _handle;
	};
}