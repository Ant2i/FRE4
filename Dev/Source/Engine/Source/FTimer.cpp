#include "FTimer.h"

LARGE_INTEGER FRE::Utils::FTimer::sFrequency;

namespace FRE
{
	namespace Utils
	{
		FTimer::FTimer() :
			_startFlag(false)
		{
#ifdef _WIN32
			bool static initFrequency = false;
			if (!initFrequency)
			{
				QueryPerformanceFrequency(&sFrequency);
				initFrequency = true;
			}

			_startCount.QuadPart = 0;
			_endCount.QuadPart = 0;
#else
			_startCount.tv_sec = _startCount.tv_usec = 0;
			_endCount.tv_sec = _endCount.tv_usec = 0;
#endif
		}

		void FTimer::Start()
		{
			_startFlag = true;
#ifdef _WIN32
			QueryPerformanceCounter(&_startCount);
#else
			gettimeofday(&_startCount, NULL);
#endif
		}

		void FTimer::Stop()
		{
			_startFlag = false;
#ifdef _WIN32
			QueryPerformanceCounter(&_endCount);
#else
			gettimeofday(&_endCount, NULL);
#endif
		}

		FTimer::tTime FTimer::GetStartTime()
		{
#ifdef _WIN32
			return ((_startCount.QuadPart / (double)sFrequency.QuadPart));
#else
			return startCount.tv_sec + startCount.tv_usec;
#endif
		}

		FTimer::tTime FTimer::GetIntervalTime()
		{
#ifdef _WIN32
			if(_startFlag)
				QueryPerformanceCounter(&_endCount);
			return ((_endCount.QuadPart - _startCount.QuadPart) / (double)sFrequency.QuadPart);
#else
			if(_startFlag)
				gettimeofday(&_endCount, NULL);
			return (endCount.tv_sec - startCount.tv_sec) + (endCount.tv_usec - startCount.tv_usec);
#endif
		}

	}
}

