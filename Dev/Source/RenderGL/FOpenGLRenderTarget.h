#pragma once

#include "FOpenGLPlatform.h"

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
			GLPlatformDestroyEntity(_handle);
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLPlatformSurfaceTargetUpdate(_handle, width, height);
		}

		void MakeCurrent(h_GLContext context) const
		{
			GLPlatformContextMakeCurrent(context, _handle);
		}

		void Swap(h_GLContext context)
		{
			GLPlatformContextSwap(context, _handle);
		}

	private:
		h_GLRenderTarget _handle;
	};
}