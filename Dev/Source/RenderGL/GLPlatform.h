#pragma once

#include "DeviceInterfaces.h"

namespace FRE
{
	typedef uint64 t_GLContext;
	typedef uint64 t_GLRenderTarget;

	class GLRenderTarget : public IRenderTarget
	{
	public:
		GLRenderTarget(t_GLRenderTarget handle) :
			_handle(handle)
		{

		}

		~GLRenderTarget()
		{
			GetCurrentPlatform().Destroy(_handle);
		}

	private:
		t_GLRenderTarget _handle;
	};

	class GLPlatform
	{
	public:
		virtual t_GLContext CreateContext() = 0;
		virtual t_GLRenderTarget CreateSurfaceTarget(t_GLContext context, const DarkParams & params) = 0;

		virtual bool MakeCurrentContext(t_GLContext context) = 0;
		virtual bool MakeCurrentContext(t_GLContext context, t_GLRenderTarget target) = 0;
		virtual bool SwapContext(t_GLContext context, t_GLRenderTarget target) = 0;

		virtual void Destroy(int64 handle) = 0;
	};

	GLPlatform & GetCurrentPlatform();
}
