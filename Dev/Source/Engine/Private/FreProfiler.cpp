//#include "FreProfiler.h"
//
//#include <vector>
//#include <ctime>
//#include <mutex>
//
//#include "FreMath.h"
//#include "FreIndexMemory.h"
//
//#include <map>
//#include <stack>
//#include <numeric>
//
//#define PROFILER_STACK_SIZE 32
//
//namespace FRE
//{
//	namespace Utils
//	{
//		template <typename _T, unsigned _Size = 10>
//		struct CircleStack
//		{
//		public:
//			CircleStack() :
//				_currIndex(0)
//			{
//				
//			}
//
//			unsigned Push(const _T & v)
//			{
//				const unsigned & index = IncrementIndex();
//				_array[index] = v;
//				return index;
//			}
//
//			unsigned Size() const 
//			{
//				return _Size;
//			}
//
//			const _T & Value(unsigned i) const
//			{
//				return _array[i % _Size];
//			}
//
//			_T & Value(unsigned i)
//			{
//				const auto p = i % _Size;
//				return _array[p];
//			}
//
//			unsigned CurrentIndex() const
//			{
//				return _currIndex;
//			}
//
//		private:
//			unsigned IncrementIndex()
//			{
//				if (_currIndex == _Size) 
//					_currIndex = 0;
//				return _currIndex++;
//			}
//
//		private:
//			_T _array[_Size];
//			unsigned _currIndex;
//		};
//
//		//-------------------------------------------------------------------
//
//		struct CPUTimerManager : public ITimerManager
//		{
//		public:
//			CPUTimerManager();
//			~CPUTimerManager();
//
//			virtual uint64_t GenTimer() override;
//			virtual void FreeTimer(uint64_t) override;
//
//			virtual void BeginTimer(uint64_t) override;
//			virtual void StopTimer(uint64_t) override;
//			virtual double GetTime(uint64_t) override;
//
//		private:
//			//Utils::IndexMemory<Timer, uint32_t> _data;
//            static Timer * CastTimer(uint64_t p)
//            {
//                return reinterpret_cast<Timer *>(p);
//            }
//		};
//
//		CPUTimerManager::CPUTimerManager()
//		{
//			Profiler::Register(ProfilerType::CPU, this);
//		}
//
//		CPUTimerManager::~CPUTimerManager()
//		{
//			Profiler::UnRegister(ProfilerType::CPU, this);
//		}
//
//		uint64_t CPUTimerManager::GenTimer()
//		{
//			return (uint64_t)new Timer();
//		}
//
//		void CPUTimerManager::FreeTimer(uint64_t h)
//		{
//			delete CastTimer(h);
//		}
//
//		void CPUTimerManager::BeginTimer(uint64_t h)
//		{
//			CastTimer(h)->Start();
//		}
//
//		void CPUTimerManager::StopTimer(uint64_t h)
//		{
//			CastTimer(h)->Stop();
//		}
//
//		double CPUTimerManager::GetTime(uint64_t h)
//		{
//			return CastTimer(h)->GetTime();
//		}
//
//		//-------------------------------------------------------------------
//
//		struct HTimerHandle
//		{
//			HTimerHandle() :
//				validate(false)
//			{
//
//			}
//
//			HTimerHandle(ProfilerType type, uint64_t h) :
//				validate(true),
//				handle(h),
//				type(type)
//			{
//
//			}
//
//			void Free()
//			{
//				validate = false;
//			}
//
//			bool validate;
//			uint64_t handle;
//			ProfilerType type;
//		};
//
//		struct ProfilerThreadInfo
//		{
//		public:
//			typedef CircleStack<HTimerHandle, PROFILER_STACK_SIZE> Stack;
//			typedef std::string Key;
//
//			struct RunTimerData
//			{
//				HTimerHandle * handle;
//			};
//
//		public:
//			ProfilerThreadInfo(const std::thread::id & id) :
//				ThreadId(id)
//			{
//				
//			}
//
//			const std::thread::id ThreadId;
//
//			void Start(ProfilerType type, const std::string & name)
//			{
//				RunTimerData data = { nullptr };
//
//				auto mgr = Profiler::GetTimeManager(type);
//				if (mgr)
//				{
//					auto & stack = _sampleTimes[name];
//
//					HTimerHandle & hh = stack.Value(stack.CurrentIndex());
//					if (hh.validate)
//					{
//						mgr->FreeTimer(hh.handle);
//						hh.Free();
//					}
//
//					const uint64_t handle = mgr->GenTimer();
//					unsigned index = stack.Push(HTimerHandle(type, handle));
//					data.handle = &stack.Value(index);
//
//					mgr->BeginTimer(handle);
//				}
//
//				_stack.push(data);
//			}
//
//			void Stop()
//			{
//				auto top = _stack.top();
//				if (top.handle && top.handle->validate && Profiler::GetTimeManager(top.handle->type))
//				{
//					Profiler::GetTimeManager(top.handle->type)->StopTimer(top.handle->handle);
//				}
//				_stack.pop();
//			}
//
//			Profiler::TimeValue GetSampleTime(const std::string & name)
//			{
//				Profiler::TimeValue ret = { 0.0, 0.0, 0.0 };
//				bool firstInit = true;
//				auto it = _sampleTimes.find(name);
//				if (it != _sampleTimes.end())
//				{
//					unsigned countValidSamples = 0;
//					auto & stack = it->second;
//					const auto size = stack.Size();
//					for (unsigned i = 0; i < size; ++i)
//					{
//						const HTimerHandle & handle = stack.Value(i);
//						if (handle.validate)
//						{
//							auto mgr = Profiler::GetTimeManager(handle.type);
//							if (mgr && handle.validate)
//							{
//								double value = mgr->GetTime(handle.handle);
//
//								if (firstInit)
//								{
//									ret.Max = ret.Min = ret.Avg = value;
//									firstInit = false;
//								}
//								else
//								{
//									ret.Avg += value;
//									ret.Min = freMin(value, ret.Min);
//									ret.Max = freMax(value, ret.Max);
//								}
//								++countValidSamples;
//							}
//						}
//					}
//
//					if (countValidSamples)
//						ret.Avg /= countValidSamples;
//				}
//
//				return ret;
//			}
//
//		public:
//			
//			typedef std::map<Key, Stack> Map;
//			Map _sampleTimes;
//			std::stack<RunTimerData> _stack;
//		};
//
//		static CPUTimerManager sCpuTimerManager;
//		static std::vector<ProfilerThreadInfo> sProfilerThreadInfos;
//		static ITimerManager * sRegisterTimeMgr[2] = { nullptr, nullptr };
//		std::mutex tiMutex;
//
//		ProfilerThreadInfo & GetThreafInfo()
//		{
//			const auto currThreadId = std::this_thread::get_id();
//
//			for (ProfilerThreadInfo & info : sProfilerThreadInfos)
//			{
//				if (info.ThreadId == currThreadId)
//					return info;
//			}
//
//			tiMutex.lock();
//			sProfilerThreadInfos.push_back(ProfilerThreadInfo(currThreadId));
//			tiMutex.unlock();
//
//			size_t index = sProfilerThreadInfos.size() - 1;
//			return sProfilerThreadInfos[index];
//		}
//
//		//-----------------------------------------------------------------------
//
//		void Profiler::Register(ProfilerType type, ITimerManager * mgr)
//		{
//			sRegisterTimeMgr[type] = mgr;
//		}
//
//		void Profiler::UnRegister(ProfilerType type, ITimerManager * mgr)
//		{
//			if (sRegisterTimeMgr[type] == mgr)
//				sRegisterTimeMgr[type] = nullptr;
//		}
//
//		ITimerManager * Profiler::GetTimeManager(ProfilerType type)
//		{
//			return sRegisterTimeMgr[type];
//		}
//
//		void Profiler::Start(ProfilerType type, const std::string & name)
//		{
//			auto & threadInfo = GetThreafInfo();
//			threadInfo.Start(type, name);
//		}
//
//		void Profiler::Stop()
//		{
//			auto & threadInfo = GetThreafInfo();
//			threadInfo.Stop();
//		}
//
//		Profiler::TimeValue Profiler::GetTime(unsigned threadIndex, const std::string & name)
//		{
//			if (threadIndex < sProfilerThreadInfos.size())
//				return sProfilerThreadInfos[threadIndex].GetSampleTime(name);
//
//			static Profiler::TimeValue empty = { 0, 0, 0 };
//			return empty;
//		}
//
//		void Profiler::Flush()
//		{
//			sProfilerThreadInfos.clear();
//		}
//	}
//}
//
