#include "FreTimer.h"

#ifdef _WIN32
    LARGE_INTEGER FRE::Utils::FTimer::sFrequency;
#endif

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

		FTimer::tTime FTimer::GetTime()
		{
#ifdef _WIN32
			if(_startFlag)
				QueryPerformanceCounter(&_endCount);
			return ((_endCount.QuadPart - _startCount.QuadPart) / (double)sFrequency.QuadPart);
#else
			if(_startFlag)
				gettimeofday(&_endCount, NULL);
			return (_endCount.tv_sec - _startCount.tv_sec) + (_endCount.tv_usec - _startCount.tv_usec)/1000000.0;
#endif
		}

	}
}

