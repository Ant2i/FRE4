#pragma once

#include "FBase.h"

#include <string>
#include <memory>
#include <thread>

namespace FRE
{
    class Marker;
    struct ProfilerThreadInfo;

	typedef unsigned long long t_tick;

	class RE_API Profiler
	{
    public:
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

		t_tick GetTicks(const std::string & name);
		void Flush();

	private:
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
        
		virtual t_tick GetBeginTime() const = 0;
		virtual t_tick GetTime() const = 0;
	};
    
	class RE_API CPUMarker : public Marker
	{
	public:
		CPUMarker();

        virtual void Begin() override;
        virtual void End() override;
        
		virtual t_tick GetBeginTime() const override;
		virtual t_tick GetTime() const override;
        
    private:
		t_tick _start;
		t_tick _end;
	};
}