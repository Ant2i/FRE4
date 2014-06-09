#include "FProfiler.h"

#include <vector>
#include <ctime>
#include <mutex>

#include "FMath.h"
#include <map>

#define PROFILER_STACK_SIZE 16

namespace FRE
{
	namespace Utils
	{
		template <unsigned _Size, typename _T>
		struct CircleStack
		{
		public:
			CircleStack() :
				_index(0)
			{
				_array.resize(_Size, 0.0);
			}

			void Push(_T v)
			{
				_array[IncrementIndex()] = v;
			}

			unsigned Size() const 
			{
				return _Size;
			}

			_T Value(unsigned i) const
			{
				return _array[i];
			}

		private:
			unsigned IncrementIndex()
			{
				unsigned i = _index;
				++_index;
				if (_index == _Size) 
					_index = 0;
				return i;
			}

		private:
			std::vector<_T> _array;
			unsigned _index;
		};


		struct ProfilerThreadInfo
		{
		public:
			typedef CircleStack<PROFILER_STACK_SIZE, double> Stack;

		public:
			ProfilerThreadInfo(const std::thread::id & id) :
				ThreadId(id)
			{
				
			}

			const std::thread::id ThreadId;

			void AddSampleTime(const std::string & name, double time)
			{
				_sampleTimes[name].Push(time);
			}

			FProfiler::Stat MarkTime(const std::string & name)
			{
				FProfiler::Stat stat = { 0, 0, 0 };

				auto & stack = _sampleTimes[name];
				for (unsigned i = 0; i < stack.Size(); ++i)
				{
					const auto & value = stack.Value(i);
					stat.Avg += value;
					stat.Min = std::min(value, stat.Min);
					stat.Max = std::max(value, stat.Max);
				}
				stat.Avg /= stack.Size();
				return stat;
			}

		private:
			std::map<std::string, CircleStack<PROFILER_STACK_SIZE, double>> _sampleTimes;
		};

		static std::vector<ProfilerThreadInfo> sProfilerThreadInfos;
		std::mutex tiMutex;

		ProfilerThreadInfo & GetThreafInfo()
		{
			const auto currThreadId = std::this_thread::get_id();

			for (ProfilerThreadInfo & info : sProfilerThreadInfos)
			{
				if (info.ThreadId == currThreadId)
					return info;
			}

			tiMutex.lock();
			sProfilerThreadInfos.push_back(ProfilerThreadInfo(currThreadId));
			tiMutex.unlock();

			size_t index = sProfilerThreadInfos.size() - 1;
			return sProfilerThreadInfos[index];
		}

		//-----------------------------------------------------------------------

		void FProfiler::AddSampleTime(const std::string & name, double time)
		{
			auto & threadInfo = GetThreafInfo();
			threadInfo.AddSampleTime(name, time);
		}

		FProfiler::Stat FProfiler::GetTime(unsigned threadIndex, const std::string & name)
		{
			if (threadIndex < sProfilerThreadInfos.size())
				return sProfilerThreadInfos[threadIndex].MarkTime(name);

			static FProfiler::Stat empty = { 0, 0, 0 };
			return empty;
		}

		void FProfiler::Flush()
		{
			sProfilerThreadInfos.clear();
		}

		//-----------------------------------------------------------------------

		FProfileMarker::FProfileMarker(const std::string & name) :
			_name(name),
			_start(false)
		{

		}

		FProfileMarker::~FProfileMarker()
		{
			Stop();
		}

		void FProfileMarker::Start()
		{
			_Start();
			_start = true;
		}

		void FProfileMarker::Stop()
		{
			if (_start)
			{
				_Stop();
				auto time = _GetTime();
				FProfiler::AddSampleTime(_name, time);
				_start = false;
			}
		}
	}
}

