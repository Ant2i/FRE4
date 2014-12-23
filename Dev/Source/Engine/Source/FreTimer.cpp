#include "FreTimer.h"

#ifdef PLATFORM_WIN
LARGE_INTEGER FRE::Timer::sFrequency;
#endif

namespace FRE
{
	Timer::Timer() :
		_startFlag(false)
	{
#ifdef PLATFORM_WIN
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

	void Timer::Start()
	{
		_startFlag = true;
#ifdef PLATFORM_WIN
		QueryPerformanceCounter(&_startCount);
#else
		gettimeofday(&_startCount, NULL);
#endif
	}

	void Timer::Stop()
	{
		_startFlag = false;
#ifdef PLATFORM_WIN
		QueryPerformanceCounter(&_endCount);
#else
		gettimeofday(&_endCount, NULL);
#endif
	}

	double Timer::GetTime()
	{
#ifdef PLATFORM_WIN
		if (_startFlag)
			QueryPerformanceCounter(&_endCount);
		return ((_endCount.QuadPart - _startCount.QuadPart) / (double)sFrequency.QuadPart);
#else
		if(_startFlag)
			gettimeofday(&_endCount, NULL);
		return (_endCount.tv_sec - _startCount.tv_sec) + (_endCount.tv_usec - _startCount.tv_usec)/1000000.0;
#endif
	}
}

