#include "Profiler.h"
#include <vector>
#include <ctime>
#include <mutex>

#include "FMath.h"

#define PROFILER_MIN_COUNT_MARKERS 1024
#define PROFILER_MAX_STACK_DEPTH 1024

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
			threadId(id),
			_currStack(0)
		{
            _markers.reserve(PROFILER_MIN_COUNT_MARKERS);
			_pushStack.resize(PROFILER_MAX_STACK_DEPTH);
		}

		inline bool PushMarker(const std::string & name, const Profiler::MarkerPtr & marker)
		{
			_markers.push_back(std::make_pair(name, marker));
			_pushStack[_currStack++] = _markers.size() - 1;
			return true;
		}

		inline Marker * PopMarker()
		{
			if (_currStack)
			{
				auto pos = _pushStack[--_currStack];
				return _GetMarker(_markers[pos]);
			}
			return nullptr;
		}

		inline void Enumerate(const std::function<void(const std::string &, const Marker *)> & func) const
		{
			for (const MarkData & info : _markers)
				func(info.first, _GetMarker(info));
		}

		const std::thread::id threadId;

	private:
        std::vector<MarkData> _markers;
		std::vector<size_t> _pushStack;
		size_t _currStack;
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
		if (GetThreafInfo().PushMarker(name, marker))
			marker->Begin();
    }
    
    void Profiler::_End()
    {
		auto marker = GetThreafInfo().PopMarker();
		if (marker)
			marker->End();
    }
    
	ProfilerThreadInfo & Profiler::GetThreafInfo()
	{
		const auto currThreadId = std::this_thread::get_id();

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

	t_tick Profiler::GetTicks(unsigned threadIndex, const std::string & name)
	{
		t_tick ticks = 0;

		auto timeCalc = [&ticks, &name](const std::string & markerName, const Marker * marker)
		{
			if (markerName == name)
				ticks += marker->GetTime();
		};

		if (threadIndex < profilerThreadInfos.size())
			profilerThreadInfos[threadIndex].Enumerate(timeCalc);

		return ticks;
	}

	unsigned Profiler::GetThreadCount() const
	{
		return profilerThreadInfos.size();
	}

	void Profiler::Flush()
	{
		profilerThreadInfos.clear();
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

