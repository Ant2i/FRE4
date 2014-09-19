#pragma once

#include "FOpenGLPlatform.h"
#include "FreRDResources.h"

namespace FRE
{
	class GLRenderTarget : public RDRenderTarget
	{
	public:
		GLRenderTarget(HGLRenderSurface hTarget) :
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

		void MakeCurrent(HGLContext hContext) const
		{
			GLContextMakeCurrent(hContext, _handle);
		}

		void Swap(HGLContext hContext)
		{
			GLContextSwap(hContext, _handle);
		}

	private:
		HGLRenderSurface _handle;
	};
}