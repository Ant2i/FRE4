#include "Profiler.h"
#include <stack>
#include <vector>
#include <ctime>
#include <mutex>

namespace FRE
{
    struct ProfilerThreadInfo
    {
		ProfilerThreadInfo(const std::thread::id & id) :
			threadId(id)
		{

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
	std::mutex threadInfoMutex;
    
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

		threadInfoMutex.lock();
		profilerThreadInfos.push_back(ProfilerThreadInfo(currThreadId));
		size_t index = profilerThreadInfos.size() - 1;
		threadInfoMutex.lock();

		return profilerThreadInfos[index];
	}

    //-----------------------------------------------------------------------
    
	CPUMarker::CPUMarker()
	{

	}

	CPUMarker::CPUMarker(const std::string & name) :
		_name(name),
		_start(0),
		_end(0)
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

		for (unsigned i = 0; i < 10000000; ++i)
		{
			sin(i);
		}

		Profiler::Begin<CPUMarker>("SubMain");
		for (unsigned i = 0; i < 10000000; ++i)
		{
			cos(i);
		}
		Profiler::End();

		Profiler::End();
	}
}

