#pragma once

#include "FPlatform.h"

#ifdef PLATFORM_WIN
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace FRE
{
	class Timer
	{
	public:
		Timer();

		void Start();
		void Stop();

		double GetTime();

	private:
		bool _startFlag;

#ifdef PLATFORM_WIN
		static LARGE_INTEGER sFrequency;
		LARGE_INTEGER _startCount;
		LARGE_INTEGER _endCount;
#else
		timeval _startCount;
		timeval _endCount;
#endif
	};
}