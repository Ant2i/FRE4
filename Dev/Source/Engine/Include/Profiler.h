#pragma once

#include <memory>
#include <thread>

namespace FRE
{
    class Marker;
    struct ProfilerThreadInfo;

	class Profiler
	{
    public:
        typedef std::shared_ptr<Marker> MarkerPtr;
    
	public:
		static Profiler & GetInstance();
        
		template <typename T>
		static void Begin(const std::string & name)
		{
			GetInstance()._Begin(std::make_shared<T>(name));
		}
		
		static void End()
		{
			GetInstance()._End();
		}

	private:
        void _Begin(const MarkerPtr & marker);
        void _End();

		ProfilerThreadInfo & GetThreafInfo();
	};
    
    class Marker
	{
	public:
        virtual ~Marker(){}
        
        virtual void Begin() = 0;
        virtual void End() = 0;
        
		virtual unsigned long long GetTime() const = 0;
	};
    
	class CPUMarker : public Marker
	{
	public:
		CPUMarker();
		CPUMarker(const std::string & name);

        virtual void Begin() override;
        virtual void End() override;
        
		virtual unsigned long long GetTime() const override;
        
    private:
		unsigned long long _start;
		unsigned long long _end;
		std::string _name;
	};
}