#include "Profiler.h"
#include <vector>
#include <stack>
#include <ctime>
#include <mutex>

#include "FMath.h"

#define PROFILER_MIN_COUNT_MARKERS 1024

namespace FRE
{
    struct ProfilerThreadInfo
    {
	private:
		typedef std::pair<std::string, Profiler::MarkerPtr> MarkData;

		static Marker * _GetMarker(const MarkData & data)
		{
			return data.second.get();
		}

	public:
		ProfilerThreadInfo(const std::thread::id & id) :
			threadId(id)
		{
            _markers.reserve(PROFILER_MIN_COUNT_MARKERS);
		}

		inline void PushMarker(const std::string & name, const Profiler::MarkerPtr & marker)
		{
			_markers.push_back(std::make_pair(name, marker));
			_pushStack.push(_markers.size());
		}

		inline Marker * PopMarker()
		{
			if (!_pushStack.empty())
			{
				auto pos = _pushStack.top() - 1;
				_pushStack.pop();
				return _GetMarker(_markers[pos]);
			}
			return nullptr;
		}

		inline void Enumerate(std::function<void(const std::string &, const Marker *)> func) const
		{
			for (const MarkData & info : _markers)
				func(info.first, _GetMarker(info));
		}

		const std::thread::id threadId;

	private:
        std::vector<MarkData> _markers;
		std::stack<size_t> _pushStack;
    };
    
    static std::vector<ProfilerThreadInfo> profilerThreadInfos;
	std::mutex tiMutex;
    
    //-----------------------------------------------------------------------
    
	Profiler & Profiler::GetInstance()
	{
		static Profiler sProfiler;
		return sProfiler;
	}

    void Profiler::_Begin(const std::string & name, const MarkerPtr & marker)
    {
		ProfilerThreadInfo & threadInfo = GetThreafInfo();
		threadInfo.PushMarker(name, marker);
		marker->Begin();
    }
    
    void Profiler::_End()
    {
        ProfilerThreadInfo & threadInfo = GetThreafInfo();
		auto marker = threadInfo.PopMarker();
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

	t_tick Profiler::GetTicks(const std::string & name)
	{
		t_tick ticks = 0;

		auto enumerate = [&ticks, &name](const std::string & markerName, const Marker * marker)
		{
			if (markerName == name)
				ticks += marker->GetTime();
		};

		for(ProfilerThreadInfo & info : profilerThreadInfos)
		{
			info.Enumerate(enumerate);
		}

		return ticks;
	}

	void Profiler::Flush()
	{

	}

    //-----------------------------------------------------------------------
    
	CPUMarker::CPUMarker() :
        _start(0),
        _end(0)
	{

	}

	t_tick CPUMarker::GetBeginTime() const
	{
		return _start;
	}

	t_tick CPUMarker::GetTime() const
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

}

