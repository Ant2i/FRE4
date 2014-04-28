#pragma once

#include <memory>

namespace FRE
{
    class Marker;
    
	class Profiler
	{
    public:
        typedef std::shared_ptr<Marker> MarkerPtr;
    
	public:
		static Profiler & GetInstance();
        
        void Begin(const MarkerPtr & marker);
        void End();
	};
    
    class Marker
	{
	public:
        virtual ~Marker(){}
        
        virtual void Begin() = 0;
        virtual void End() = 0;
        
		virtual int GetTime() const = 0;
	};
    
	class CPUMarker : public Marker
	{
	public:
        virtual void Begin() override;
        virtual void End() override;
        
		virtual int GetTime() const override;
        
    private:
        uint64_t _start;
		uint64_t _end;
	};
}