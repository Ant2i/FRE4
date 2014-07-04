#pragma once

#include <functional>

namespace FRE
{
	class GLDebug
	{
	public:
		typedef std::function<void(const char *)> CallbackFunc;

	public:
		static bool Enable();
		static void Disable();

		static void SetCallBack(const CallbackFunc & cb);
	};
}