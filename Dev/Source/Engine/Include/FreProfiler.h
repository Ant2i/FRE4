#pragma once

#include "FreBase.h"

#include <string>
#include <memory>
#include <thread>
#include "FreTimer.h"

namespace FRE
{
	namespace Utils
	{
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
			static void AddSampleTime(const std::string & name, double time);
			static void Flush();
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

		typedef FProfileMarkerT<FTimer> FCPUMarker;
	}
}

#define CPU_PROFILE_START(name) { FCPUMarker _##name(#name); _##name.Start(); 
#define CPU_PROFILE_STOP(name) _##name.Stop(); }