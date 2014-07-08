#include "FreGPUTimer.h"

namespace FRE
{
	namespace Utils
	{
		static GPUTimeManager sGpuTimerManager;

		GPUTimeManager::GPUTimeManager()
		{
			Profiler::Register(GPU, this);
		}

		GPUTimeManager::~GPUTimeManager()
		{
			Profiler::UnRegister(GPU, this);
		}
		
		uint64 GPUTimeManager::GenTimer()
		{
			GLuint handle = 0;
			glGenQueries(1, &handle);
			return handle;
		}

		void GPUTimeManager::FreeTimer(uint64 h)
		{
			const GLuint handle = (GLuint)h;
			glDeleteQueries(1, &handle);
		}

		void GPUTimeManager::BeginTimer(uint64 h)
		{
			const GLuint handle = (GLuint)h;
			glBeginQuery(GL_TIME_ELAPSED, handle);
		}

		void GPUTimeManager::StopTimer(uint64 h)
		{
			glEndQuery(GL_TIME_ELAPSED);
		}

		double GPUTimeManager::GetTime(uint64 h)
		{
			const GLuint handle = (GLuint)h;
			GLint available = 0;
			while (!available)
				glGetQueryObjectiv(handle, GL_QUERY_RESULT_AVAILABLE, &available);

			GLuint64 time = 0;
			if (glGetQueryObjectui64v)
				glGetQueryObjectui64v(handle, GL_QUERY_RESULT, &time);
			return time / 1000000.0;
		}
	}
}