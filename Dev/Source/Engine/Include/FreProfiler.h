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

		//class RE_API ProfileMarker
		//{
		//public:
		//	ProfileMarker(ProfilerType, const std::string & name);
		//	ProfileMarker(ProfileMarker && marker);
		//	virtual ~ProfileMarker();

		//	void Start();
		//	void Stop();

		//private:
		//	const ProfilerType _type;
		//	const std::string _name;
		//	uint64 _handle;
		//};

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
			//static void AddSampleTime(const std::string & name, double time);

			static void Start(ProfilerType type, const std::string & name);
			static void Stop();

			static void Flush();

			static ITimerManager * GetTimeManager(ProfilerType);
			static void Register(ProfilerType, ITimerManager * mgr);
		};

		//-------------------------------------------------------------------

		class RE_API FProfileMarker
		{
		public:
			FProfileMarker(const std::string & name);
			virtual ~FProfileMarker();

			void Start();
			void Stop();

		protected:
			virtual void _Start() = 0;
			virtual void _Stop() = 0;
			virtual double _GetTime() = 0;

		private:
			const std::string _name;
			bool _start;
		};

		//-------------------------------------------------------------------

		template <typename T>
		class FProfileMarkerT : public FProfileMarker
		{
		public:
			FProfileMarkerT(const std::string & name) : FProfileMarker(name)
			{

			}

		protected:
			virtual void _Start() override
			{
				_marker.Start();
			}

			virtual void _Stop() override
			{
				_marker.Stop();
			}

			virtual double _GetTime() override
			{
				return (double)_marker.GetTime();
			}

		private:
			T _marker;
		};

		typedef FProfileMarkerT<Timer> FCPUMarker;
	}
}

#define CPU_PROFILE_START(name) { FProfiler::Start(FRE::Utils::ProfilerType::CPU, #name); 
#define CPU_PROFILE_STOP() FProfiler::Stop(); }