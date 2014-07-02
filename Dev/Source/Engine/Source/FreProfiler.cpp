#include "FreProfiler.h"

#include <vector>
#include <ctime>
#include <mutex>

#include "FreMath.h"
#include "FreIndexMemory.h"

#include <map>
#include <stack>
#include <numeric>

#define PROFILER_STACK_SIZE 16

namespace FRE
{
	namespace Utils
	{
		static ITimerManager * sRegisterTimeMgr[2] = { nullptr, nullptr };

		template <typename _T, unsigned _Size = 10>
		struct CircleStack
		{
		public:
			CircleStack() :
				_currIndex(0)
			{
				
			}

			unsigned Push(const _T & v)
			{
				const unsigned & index = IncrementIndex();
				_array[index] = v;
				return index;
			}

			unsigned Size() const 
			{
				return _Size;
			}

			const _T & Value(unsigned i) const
			{
				return _array[i % _Size];
			}

			_T & Value(unsigned i)
			{
				return _array[i % _Size];
			}

			unsigned CurrentIndex() const
			{
				return _currIndex;
			}

		private:
			unsigned IncrementIndex()
			{
				if (_currIndex == _Size) 
					_currIndex = 0;
				return _currIndex++;
			}

		private:
			_T _array[_Size];
			unsigned _currIndex;
		};

		struct CPUTimerManager : public ITimerManager
		{
		public:
			CPUTimerManager();

			virtual uint64 GenTimer() override;
			virtual void FreeTimer(uint64) override;

			virtual void BeginTimer(uint64) override;
			virtual void StopTimer(uint64) override;
			virtual double GetTime(uint64) override;

		private:
			Utils::FIndexMemory<Timer, uint32> _data;
		};

		CPUTimerManager::CPUTimerManager()
		{
			FProfiler::Register(ProfilerType::CPU, this);
		}

		uint64 CPUTimerManager::GenTimer()
		{
			return _data.Allocate(Timer());
		}

		void CPUTimerManager::FreeTimer(uint64 h)
		{
			_data.Free((uint32)h);
		}

		void CPUTimerManager::BeginTimer(uint64 h)
		{
			_data.Get((uint32)h).Start();
		}

		void CPUTimerManager::StopTimer(uint64 h)
		{
			_data.Get((uint32)h).Stop();
		}

		double CPUTimerManager::GetTime(uint64 h)
		{
			return _data.Get((uint32)h).GetTime();
		}

		//-------------------------------------------------------------------

		struct HTimerHandle
		{
			HTimerHandle() :
				validate(false)
			{

			}

			HTimerHandle(ProfilerType type, uint64 h) :
				validate(true),
				handle(h),
				type(type)
			{

			}

			void Free()
			{
				validate = false;
			}

			bool validate;
			uint64 handle;
			ProfilerType type;
		};

		//struct HTimerHandle
		//{
		//	HTimerHandle() :
		//		_validate(false)
		//	{

		//	}

		//	HTimerHandle(ProfilerType type, uint64 h) :
		//		_type(type),
		//		_handle(h),
		//		_validate(true)
		//	{

		//	}

		//	HTimerHandle(HTimerHandle && other) :
		//		_type(other._type),
		//		_handle(other._handle),
		//		_validate(other._validate)
		//	{
		//		other._validate = false;
		//	}

		//	HTimerHandle & operator=(HTimerHandle && other)
		//	{
		//		_type = other._type;
		//		_handle = other._handle;
		//		_validate = other._validate;

		//		other._validate = false;
		//	}

		//	~HTimerHandle()
		//	{
		//		if (_validate)
		//		{
		//			auto mgr = FProfiler::GetTimeManager(_type);
		//			if (mgr)
		//				mgr->FreeTimer(_handle);
		//		}
		//	}

		//private:
		//	HTimerHandle(const HTimerHandle & ){}
		//	HTimerHandle & operator=(const HTimerHandle&){}

		//	ProfilerType _type;
		//	uint64 _handle;
		//	bool _validate;
		//};

		struct ProfilerThreadInfo
		{
		public:
			typedef CircleStack<HTimerHandle, PROFILER_STACK_SIZE> Stack;
			typedef std::string Key;

			struct RunTimerData
			{
				HTimerHandle * handle;
			};

		public:
			ProfilerThreadInfo(const std::thread::id & id) :
				ThreadId(id)
			{
				
			}

			const std::thread::id ThreadId;

			//void AddSampleTime(const std::string & name, double time)
			//{
			//	_sampleTimes[name].Push(time);
			//}

			void Start(ProfilerType type, const std::string & name)
			{
				RunTimerData data = { nullptr };

				auto mgr = FProfiler::GetTimeManager(type);
				if (mgr)
				{
					uint64 handle = mgr->GenTimer();

					auto & stack = _sampleTimes[name];

					HTimerHandle & hh = stack.Value(stack.CurrentIndex() + 1);
					if (hh.validate)
					{
						mgr->FreeTimer(hh.handle);
						hh.Free();
					}

					unsigned index = stack.Push(HTimerHandle(type, handle));
					data.handle = &stack.Value(index);

					mgr->BeginTimer(handle);
				}

				_stack.push(data);
			}

			void Stop()
			{
				auto top = _stack.top();
				if (top.handle && top.handle->validate && FProfiler::GetTimeManager(top.handle->type))
				{
					FProfiler::GetTimeManager(top.handle->type)->StopTimer(top.handle->handle);
				}
				_stack.pop();
			}

			FProfiler::Stat MarkTime(const std::string & name)
			{
				FProfiler::Stat stat = { 0, 0, 0 };

				auto & stack = _sampleTimes[name];
				for (unsigned i = 0; i < stack.Size(); ++i)
				{
					double value(0.0);

					const HTimerHandle & handle = stack.Value(i);
					if (handle.validate)
					{
						auto mgr = FProfiler::GetTimeManager(handle.type);
						if (mgr)
							value = mgr->GetTime(handle.handle);
					}

					stat.Avg += value;
					stat.Min = std::min(value, stat.Min);
					stat.Max = std::max(value, stat.Max);
				}
				stat.Avg /= stack.Size();
				return stat;
			}

		public:
			
			typedef std::map<Key, Stack> Map;
			Map _sampleTimes;
			std::stack<RunTimerData> _stack;
		};

		static CPUTimerManager sCpuTimerManager;
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

		void FProfiler::Register(ProfilerType type, ITimerManager * mgr)
		{
			sRegisterTimeMgr[type] = mgr;
		}

		ITimerManager * FProfiler::GetTimeManager(ProfilerType type)
		{
			return sRegisterTimeMgr[type];
		}

		void FProfiler::Start(ProfilerType type, const std::string & name)
		{
			auto & threadInfo = GetThreafInfo();
			threadInfo.Start(type, name);
		}

		void FProfiler::Stop()
		{
			auto & threadInfo = GetThreafInfo();
			threadInfo.Stop();
		}

		//void FProfiler::AddSampleTime(const std::string & name, double time)
		//{
		//	auto & threadInfo = GetThreafInfo();
		//	threadInfo.AddSampleTime(name, time);
		//}

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
				//FProfiler::AddSampleTime(_name, time);
				_start = false;
			}
		}

		//-------------------------------------------------------------------

		//ProfileMarker::ProfileMarker(ProfilerType type, const std::string & name) :
		//	_type(type),
		//	_name(name),
		//	_handle(0)
		//{
		//	//auto timeMgr = FProfiler::GetTimeManager(type);
		//	//if (timeMgr)
		//		//_handle = timeMgr->GenTimer();
		//}

		//ProfileMarker::ProfileMarker(ProfileMarker && marker) :
		//	_handle(marker._handle),
		//	_name(std::move(marker._name)),
		//	_type(marker._type)
		//{
		//	marker._handle = 0;
		//}

	}
}

