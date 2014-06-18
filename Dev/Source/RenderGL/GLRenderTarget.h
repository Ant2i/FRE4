#pragma once

#include "GLPlatform.h"

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