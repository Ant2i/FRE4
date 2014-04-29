#include "Profiler.h"
#include <vector>
#include <ctime>
#include <mutex>

#include <cmath>

#define PROFILER_MIN_COUNT_MARKERS 1024

namespace FRE
{
    struct ProfilerThreadInfo
    {
		ProfilerThreadInfo(const std::thread::id & id) :
			threadId(id)
		{
            _markers.reserve(PROFILER_MIN_COUNT_MARKERS);
		}

		inline void PushMarker(const Profiler::MarkerPtr & marker)
		{
			_markers.push_back(marker);
		}

		inline Marker * GetLastMarker() const
		{
			auto size = _markers.size();
			if (size != 0)
				return _markers[size - 1].get();
			return nullptr;
		}

		const std::thread::id threadId;

	private:
        std::vector<Profiler::MarkerPtr> _markers;
    };
    
    static std::vector<ProfilerThreadInfo> profilerThreadInfos;
	std::mutex tiMutex;
    
    //-----------------------------------------------------------------------
    
	Profiler & Profiler::GetInstance()
	{
		static Profiler sProfiler;
		return sProfiler;
	}

    void Profiler::_Begin(const MarkerPtr & marker)
    {
		ProfilerThreadInfo & threadInfo = GetThreafInfo();
		threadInfo.PushMarker(marker);
		marker->Begin();
    }
    
    void Profiler::_End()
    {
        ProfilerThreadInfo & threadInfo = GetThreafInfo();
		auto marker = threadInfo.GetLastMarker();
		if (marker)
			marker->End();
    }
    
	ProfilerThreadInfo & Profiler::GetThreafInfo()
	{
		auto currThreadId = std::this_thread::get_id();

		for (ProfilerThreadInfo & info : profilerThreadInfos)
		{
			if (info.threadId == currThreadId)
				return info;
		}

		tiMutex.lock();
		profilerThreadInfos.push_back(ProfilerThreadInfo(currThreadId));
		tiMutex.unlock();
        
        size_t index = profilerThreadInfos.size() - 1;
		return profilerThreadInfos[index];
	}

    //-----------------------------------------------------------------------
    
	CPUMarker::CPUMarker() :
        _start(0),
        _end(0)
	{

	}

	CPUMarker::CPUMarker(const std::string & name) :
		_start(0),
		_end(0),
        _name(name)
	{

	}

	unsigned long long CPUMarker::GetTime() const
	{
        return _end - _start;
	}
    
    void CPUMarker::Begin()
    {
        _end = _start = clock();
    }
    
    void CPUMarker::End()
    {
        _end = clock();
    }

	//-----------------------------------------------------------------------
	
	void Test_Profiler()
	{
      	Profiler::Begin<CPUMarker>("Main");

		for (unsigned i = 0; i < 1000000; ++i)
		{
            std::sin(i);
		}

		Profiler::Begin<CPUMarker>("SubMain");
		for (unsigned i = 0; i < 1000000; ++i)
		{
            std::cos(i);
		}
		Profiler::End();

		Profiler::End();
	}
}

