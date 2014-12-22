#pragma once

#include "FreRDInterfaces.h"

#include "OpenGLBase.h"
#include "OpenGLContext.h"

#include <memory>

#define RD_FUNC_IMPL_DEFS(ReturnType, Name, DefParams, CallParams, DefReturn) virtual ReturnType Name DefParams override;

namespace FRE
{
	class GLDevice : public IRenderDevice
	{
	public:
		static bool Init();

	public:
		GLDevice();
		virtual ~GLDevice();
		virtual void Release() override;

		virtual const char * GetName() const override;

		#include "FreRDMethodsDefs.inc"

        GLContext & GetCurrentContext();
		inline GLContext & GetRenderContext() { return _renderContext; }
		inline GLContext & GetSharedContext() { return _sharedContext; }

	private:
		class GLRenderSurface * _drawSurface = nullptr;
		GLPlatformContextP _restoreContext = nullptr;

		GLContext _sharedContext;
		GLContext _renderContext;
	};
}

#undef RD_FUNC_IMPL_DEFS