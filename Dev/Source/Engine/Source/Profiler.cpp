#include "Profiler.h"
#include <vector>

namespace FRE
{
    struct ProfilerThreadInfo
    {
        std::vector<Profiler::MarkerPtr> markers;
    };
    
    static std::vector<ProfilerThreadInfo> profilerThreadInfos;
    
    //----------------------------------------------------------
    
	Profiler & Profiler::GetInstance()
	{
		static Profiler sProfiler;
		return sProfiler;
	}

    void Profiler::Begin(const MarkerPtr & marker)
    {
        
    }
    
    void Profiler::End()
    {
        
    }
    
    //---------------------------------------------------------
    
	int CPUMarker::GetTime() const
	{
        return 0;
	}
    
    void CPUMarker::Begin()
    {
        _start = clock();
    }
    
    void CPUMarker::End()
    {
        _end = clock();
    }
	
	void Test_Profiler()
	{
        profilerThreadInfos.push_back(ProfilerThreadInfo());
        
		//CPUMarker::Begin("Name");
        //CPUMarker::End();
	}
}

