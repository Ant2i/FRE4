#pragma once

#include "FreBase.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

namespace FRE
{
	namespace Utils
	{
		class RE_API Timer
		{
		public:
			Timer();

			void Start();
			void Stop();

			double GetTime();

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