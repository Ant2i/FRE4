#pragma once

#include "FreGLPlatform.h"

namespace FRE
{
	class GLRenderTarget : public IRenderTarget
	{
	public:
		GLRenderTarget(h_GLRenderTarget handle) :
			_handle(handle)
		{

		}

		~GLRenderTarget()
		{
			PlatformDestroyEntity(_handle);
		}

		virtual void Release() 
		{ 
			delete this;
		}

		virtual void SetSize(unsigned width, unsigned height) 
		{
			PlatformUpdateSurfaceTarget(_handle, width, height);
		}

		void MakeCurrent(h_GLContext context) const
		{
			PlatformMakeCurrentContext(context, _handle);
		}

		void Swap(h_GLContext context)
		{
			PlatformSwapContext(context, _handle);
		}

	private:
		h_GLRenderTarget _handle;
	};
}