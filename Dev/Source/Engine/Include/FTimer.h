#pragma once

#include "Base.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace FRE
{
	namespace Utils
	{
		class RE_API FTimer
		{
		public:
			typedef double tTime;

		public:
			FTimer();

			void Start();
			void Stop();

			tTime GetTime();

		private:
			bool _startFlag;
#ifdef _WIN32
			static LARGE_INTEGER sFrequency;
			LARGE_INTEGER _startCount;
			LARGE_INTEGER _endCount;
#else
			timeval _startCount;
			timeval _endCount;
#endif
		};	
	}
}