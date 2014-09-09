#pragma once

#include "FOpenGLPlatform.h"
#include "FreRDResources.h"

namespace FRE
{
	class GLRenderTarget : public RD_RenderTarget
	{
	public:
		GLRenderTarget(h_GLRenderTarget hTarget) :
			_handle(hTarget)
		{

		}

		virtual ~GLRenderTarget()
		{
			GLTargetDestroy(_handle);
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLTargetUpdate(_handle, width, height);
		}

		void MakeCurrent(h_GLContext hContext) const
		{
			GLContextMakeCurrent(hContext, _handle);
		}

		void Swap(h_GLContext hContext)
		{
			GLContextSwap(hContext, _handle);
		}

	private:
		h_GLRenderTarget _handle;
	};
}