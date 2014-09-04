#pragma once

#include "FOpenGLPlatform.h"
#include "FreProfiler.h"

namespace FRE
{
	namespace Utils
	{
		class GPUTimeManager : public ITimerManager
		{
		public:
			GPUTimeManager();
			~GPUTimeManager();

			virtual uint64 GenTimer() override;
			virtual void FreeTimer(uint64) override;

			virtual void BeginTimer(uint64) override;
			virtual void StopTimer(uint64) override;
			virtual double GetTime(uint64) override;
		};
	}
}

#define GPU_PROFILE_START(name) FRE::Utils::Profiler::Start(FRE::Utils::ProfilerType::GPU, #name);
#define GPU_PROFILE_STOP(name) FRE::Utils::Profiler::Stop();