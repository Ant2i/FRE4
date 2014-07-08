#pragma once

#include "GLBase.h"

namespace FRE
{
	class GLDebug
	{
	public:
		typedef void (*CallbackFunc)(const char *);

	public:
		static bool Enable();
		static void Disable();

		static void SetCallBack(CallbackFunc cb);
	};
}