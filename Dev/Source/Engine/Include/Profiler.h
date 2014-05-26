#pragma once

#include "FBase.h"

#include <string>
#include <memory>
#include <thread>
#include <chrono>

namespace FRE
{
    class Marker;
    struct ProfilerThreadInfo;

	class RE_API Profiler
	{
    public:
        typedef std::chrono::nanoseconds Time;
        typedef std::shared_ptr<Marker> MarkerPtr;
    
	public:
		static Profiler & GetInstance();
        
		template <typename T>
		static void Begin(const std::string & name)
		{
			GetInstance()._Begin(name, std::make_shared<T>());
		}
		
		static void End()
		{
			GetInstance()._End();
		}

		static long long GetTimeIntervalMilliSec(unsigned threadIndex, const std::string & name);
		static long long GetTimeIntervalNanoSec(unsigned threadIndex, const std::string & name);

        static unsigned GetThreadCount();
		static void Flush();

	private:
        static Time GetTimeInterval(unsigned threadIndex, const std::string & name);
        
        void _Begin(const std::string & name, const MarkerPtr & marker);
        void _End();
		
		ProfilerThreadInfo & GetThreafInfo();
	};
    
    class RE_API Marker
	{
	public:
        virtual ~Marker(){}
        
        virtual void Begin() = 0;
        virtual void End() = 0;
        
		virtual Profiler::Time GetBeginTime() const = 0;
		virtual Profiler::Time GetTimeInterval() const = 0;
	};
    
	class RE_API CPUMarker : public Marker
	{
	public:
		CPUMarker();

        virtual void Begin() override;
        virtual void End() override;
        
		virtual Profiler::Time GetBeginTime() const override;
		virtual Profiler::Time GetTimeInterval() const override;
        
    private:
		std::chrono::nanoseconds _start;
		std::chrono::nanoseconds _end;
	};
}