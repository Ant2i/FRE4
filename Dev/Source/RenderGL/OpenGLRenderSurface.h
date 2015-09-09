#pragma once

#include "RDResources.h"
#include "GLPlatform.h"

namespace FRE
{
	class GLRenderSurface : public RDRenderOutput
	{
	public:
		GLRenderSurface(GLPlatformRenderSurfaceP hTarget) :
			_handle(hTarget)
		{

		}

		virtual ~GLRenderSurface()
		{
			GLPlatformSurfaceDestroy(_handle);
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLPlatformSurfaceUpdate(_handle, width, height);
		}

		void MakeCurrent(GLPlatformContextH hContext) const
		{
			GLPlatformContextMakeCurrent(hContext, _handle);
		}

		void Swap(GLPlatformContextH hContext)
		{
			GLPlatformContextSwap(hContext, _handle);
		}

	private:
		GLPlatformRenderSurfaceP _handle;
	};
}