#pragma once

#include "DeviceInterfaces.h"
#include "GLPlatform.h"

namespace FRE
{
	typedef uint64 h_GLContext;
	typedef uint64 h_GLRenderTarget;

	class GLPlatform
	{
	public:
		virtual h_GLContext CreateContext(h_GLContext shared = 0) { return 0; }
		virtual h_GLRenderTarget CreateSurfaceTarget(h_GLContext context, const DarkParams & params) { return 0; }

		virtual bool MakeCurrentContext(h_GLContext context) { return false; }
		virtual bool MakeCurrentContext(h_GLContext context, h_GLRenderTarget target) { return false; }
		virtual bool SwapContext(h_GLContext context, h_GLRenderTarget target) { return false; }

		virtual void Destroy(int64 handle) { }
	};

	GLPlatform & GetCurrentPlatform();
	GLPlatform * InitPlatform();
	
	class GLRenderTarget : public IRenderTarget
	{
	public:
		GLRenderTarget(h_GLRenderTarget handle) :
			_handle(handle)
		{

		}

		~GLRenderTarget()
		{
			GetCurrentPlatform().Destroy(_handle);
		}

		virtual void Release() { delete this; }
		virtual void SetSize(unsigned width, unsigned height) {}

		void MakeCurrent(h_GLContext context) const
		{
			GetCurrentPlatform().MakeCurrentContext(context, _handle);
		}

		void Swap(h_GLContext context)
		{
			GetCurrentPlatform().SwapContext(context, _handle);
		}

	private:
		h_GLRenderTarget _handle;
	};
}
