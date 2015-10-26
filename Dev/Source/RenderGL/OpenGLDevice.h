#pragma once

#include "RDInterfaces.h"

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

		//Add autogenerate method for render device.
		#include "RDMethodsDefs.inc"
		
        GLContext & GetCurrentContext();
		inline GLContext & GetRenderContext() { return _renderContext; }
		inline GLContext & GetSharedContext() { return _sharedContext; }

		static GLPConfig GetDefaultPixelFormat();

	private:
		class GLRenderSurface * _drawSurface = nullptr;
		GLContext _sharedContext;
		GLContext _renderContext;

		GLPContext _restoreContext = nullptr;
	};
}

#undef RD_FUNC_IMPL_DEFS