#pragma once

#include "FreRDResources.h"
#include "GLPlatform.h"

namespace FRE
{
	class GLRenderTarget : public RDRenderOutput
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