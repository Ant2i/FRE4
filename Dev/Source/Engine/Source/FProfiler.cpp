#include "FProfiler.h"

#include <vector>
#include <ctime>
#include <mutex>

#include "FMath.h"

#define PROFILER_MIN_COUNT_MARKERS 1024
#define PROFILER_MAX_STACK_DEPTH 1024

namespace FRE
{
	namespace Utils
	{

		struct ProfilerThreadInfo
		{
		private:
			typedef std::pair<std::string, FProfiler::FMarkerPtr> MarkData;

			static FMarker * _GetMarker(const MarkData & data)
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

			inline bool PushMarker(const std::string & name, const FProfiler::FMarkerPtr & marker)
			{
				_markers.push_back(std::make_pair(name, marker));
				_pushStack[_currStack++] = _markers.size() - 1;
				return true;
			}

			inline FMarker * PopMarker()
			{
				if (_currStack)
				{
					auto pos = _pushStack[--_currStack];
					return _GetMarker(_markers[pos]);
				}
				return nullptr;
			}

			template <typename T>
			inline void Enumerate(T & functor) const
			{
				for (const MarkData & info : _markers)
					functor(info.first, _GetMarker(info));
			}

			const std::thread::id threadId;

		private:
			std::vector<MarkData> _markers;
			std::vector<size_t> _pushStack;
			size_t _currStack;
		};

		static std::vector<ProfilerThreadInfo> sProfilerThreadInfos;
		std::mutex tiMutex;

		//-----------------------------------------------------------------------

		FProfiler & FProfiler::GetInstance()
		{
			static FProfiler sProfiler;
			return sProfiler;
		}

		void FProfiler::_Start(const std::string & name, const FMarkerPtr & marker)
		{
			if (GetThreafInfo().PushMarker(name, marker))
				marker->Start();
		}

		void FProfiler::_Stop()
		{
			auto * marker = GetThreafInfo().PopMarker();
			if (marker)
				marker->Stop();
		}

		ProfilerThreadInfo & FProfiler::GetThreafInfo()
		{
			const auto currThreadId = std::this_thread::get_id();

			for (ProfilerThreadInfo & info : sProfilerThreadInfos)
			{
				if (info.threadId == currThreadId)
					return info;
			}

			tiMutex.lock();
			sProfilerThreadInfos.push_back(ProfilerThreadInfo(currThreadId));
			tiMutex.unlock();

			size_t index = sProfilerThreadInfos.size() - 1;
			return sProfilerThreadInfos[index];
		}

		struct CalcMarkerTime
		{
			CalcMarkerTime(const std::string & name) :
				_time(0),
				_name(name)
			{

			}

			void operator()(const std::string & markerName, const FMarker * marker)
			{
				if (_name == markerName)
					_time = _time + marker->GetTime();
			}

			FTimer::tTime GetTime() const { return _time; }

		private:
			FTimer::tTime _time;
			const std::string & _name;
		};

		FTimer::tTime FProfiler::GetMarkerTime(unsigned threadIndex, const std::string & name)
		{
			CalcMarkerTime timeCalc(name);

			if (threadIndex < sProfilerThreadInfos.size())
				sProfilerThreadInfos[threadIndex].Enumerate(timeCalc);

			return timeCalc.GetTime();
		}

		unsigned FProfiler::GetThreadCount()
		{
			return sProfilerThreadInfos.size();
		}

		void FProfiler::Flush()
		{
			sProfilerThreadInfos.clear();
		}

		//-----------------------------------------------------------------------

		FCPUMarker::FCPUMarker()
		{

		}

		FTimer::tTime FCPUMarker::GetStartTime() const
		{
			return _timer.GetStartTime();
		}

		FTimer::tTime FCPUMarker::GetTime() const
		{
			return _timer.GetIntervalTime();
		}

		void FCPUMarker::Start()
		{
			_timer.Start();
		}

		void FCPUMarker::Stop()
		{
			_timer.Stop();
		}
	}
}

