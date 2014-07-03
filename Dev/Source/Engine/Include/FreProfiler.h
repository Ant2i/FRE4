#pragma once

#include "FreBase.h"

#include <string>
#include <memory>
#include <thread>

#include "FreTypes.h"
#include "FreTimer.h"

namespace FRE
{
	namespace Utils
	{
		class ITimerManager
		{
		public:
			virtual uint64 GenTimer() = 0;
			virtual void FreeTimer(uint64) = 0;

			virtual void BeginTimer(uint64) = 0;
			virtual void StopTimer(uint64) = 0;
			virtual double GetTime(uint64) = 0;
		};

		enum ProfilerType
		{
			CPU = 0,
			GPU
		};

		class RE_API FProfiler
		{
		public:
			struct Stat
			{
				double Max;
				double Avg;
				double Min;
 			};

			static Stat GetTime(unsigned threadIndex, const std::string & name);

			static void Start(ProfilerType type, const std::string & name);
			static void Stop();

			static void Flush();

			static ITimerManager * GetTimeManager(ProfilerType);
			static void Register(ProfilerType, ITimerManager * mgr);
		};
	}
}

#define CPU_PROFILE_START(name) FRE::Utils::FProfiler::Start(FRE::Utils::ProfilerType::CPU, #name); 
#define CPU_PROFILE_STOP(name) FRE::Utils::FProfiler::Stop();