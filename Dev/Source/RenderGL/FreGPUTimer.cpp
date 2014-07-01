#pragma once

#include "FreGPUTimer.h"

namespace FRE
{
	namespace Utils
	{
		GPUTimer::GPUTimer() :
			_available(false),
			_time(0)
		{
			glGenQueries(1, &_handle);
		}

		GPUTimer::~GPUTimer()
		{
			glDeleteQueries(1, &_handle);
		}

		void GPUTimer::Start()
		{
			glBeginQuery(GL_TIME_ELAPSED, _handle);
			_available = false;
		}

		void GPUTimer::Stop()
		{
			glEndQuery(_handle);
		}

		double GPUTimer::GetTime()
		{
			if (_available)
			{
				while (!_available)
					glGetQueryObjectiv(_handle, GL_QUERY_RESULT_AVAILABLE, &_available);
				glGetQueryObjectui64v(_handle, GL_QUERY_RESULT, &_time);
			}

			return _time / 1000000.0;
		}
	}
}