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

		virtual char * GetName() const override;

		#include "FreRDMethodsDefs.inc"

		inline GLContext & GetCurrentContext();

	private:
		class GLRenderSurface * _drawSurface = nullptr;
		GLPlatformContextP _restoreContext = nullptr;

		GLContext _sharedContext;
		GLContext _renderContext;
	};
}

#undef RD_FUNC_IMPL_DEFS