#pragma once

#include "Base.h"

#include <string>
#include <memory>
#include <thread>
#include "FTimer.h"

namespace FRE
{
	namespace Utils
	{
		class FMarker;
		struct ProfilerThreadInfo;

		class RE_API FProfiler
		{
		public:
			typedef std::shared_ptr<FMarker> FMarkerPtr;

		public:
			static FProfiler & GetInstance();

			template <typename T>
			static void Start(const std::string & name)
			{
				GetInstance()._Start(name, std::make_shared<T>());
			}

			static void Stop()
			{
				GetInstance()._Stop();
			}

			static FTimer::tTime GetMarkerTime(unsigned threadIndex, const std::string & name);

			static unsigned GetThreadCount();
			static void Flush();

		private:
			void _Start(const std::string & name, const FMarkerPtr & marker);
			void _Stop();

			ProfilerThreadInfo & GetThreafInfo();
		};

		class RE_API FMarker
		{
		public:
			virtual ~FMarker(){}

			virtual void Start() = 0;
			virtual void Stop() = 0;

			virtual FTimer::tTime GetStartTime() const = 0;
			virtual FTimer::tTime GetTime() const = 0;
		};

		class RE_API FCPUMarker : public FMarker
		{
		public:
			FCPUMarker();

			virtual void Start() override;
			virtual void Stop() override;

			virtual FTimer::tTime GetStartTime() const override;
			virtual FTimer::tTime GetTime() const override;

		private:
			mutable FTimer _timer;
		};
	}
}