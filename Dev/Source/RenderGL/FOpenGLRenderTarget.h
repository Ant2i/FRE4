#pragma once

#include "FOpenGLPlatform.h"
#include "FreRDResources.h"

namespace FRE
{
	class GLRenderTarget : public RD_RenderTarget
	{
	public:
		GLRenderTarget(h_GLRenderTarget handle) :
			_handle(handle)
		{

		}

		virtual ~GLRenderTarget()
		{
			GLContextDestroy(_handle);
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLTargetUpdate(_handle, width, height);
		}

		void MakeCurrent(h_GLContext context) const
		{
			GLContextMakeCurrent(context, _handle);
		}

		void Swap(h_GLContext context)
		{
			GLContextSwap(context, _handle);
		}

	private:
		h_GLRenderTarget _handle;
	};
}