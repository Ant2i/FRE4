#pragma once

#include "FreGLPlatform.h"

namespace FRE
{
	class GLRenderTarget : public RI_RenderTarget
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

		virtual void Destroy() override
		{ 
			delete this;
		}

		virtual void SetSize(unsigned width, unsigned height) override
		{
			GLPlatformUpdateSurfaceTarget(_handle, width, height);
		}

		void MakeCurrent(h_GLContext context) const
		{
			GLPlatformMakeCurrentContext(context, _handle);
		}

		void Swap(h_GLContext context)
		{
			GLPlatformSwapContext(context, _handle);
		}

	private:
		h_GLRenderTarget _handle;
	};
}