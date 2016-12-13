//#pragma once
//
//#include <vector>
//#include <bitset>
//
//namespace FRE
//{
//	namespace Utils
//	{
//		template <typename _T, typename _I = unsigned>
//		class IndexMemory
//		{
//            struct MemoryBlock
//            {
//                MemoryBlock() : Valid(0xFF)
//                {
//                    
//                }
//                
//                _T * Get() { return reinterpret_cast<_T *>(Data); }
//                const _T * Get() const { return reinterpret_cast<const _T *>(Data); }
//                
//                void Create(const _T & v)
//                {
//                    //new (Data) _T(v);
//                    Valid = 0x1;
//                }
//
//                void Destroy()
//                {
//                    Valid = 0xFF;
//                    Get()->~_T();
//                }
//                
//                bool IsValid() const { return Valid == 0x1; }
//                
//                char Data[sizeof(_T)];
//                
//            private:
//                char Valid;
//            };
//            
//		public:
//			IndexMemory() :
//				_lastFreeIndex(0),
//				_numFreeIndex(0)
//			{
//
//			}
//
//            IndexMemory(const IndexMemory & m) :
//                _memory(m._memory),
//                _lastFreeIndex(m._lastFreeIndex),
//                _numFreeIndex(m._numFreeIndex)
//            {
//                const auto & validIndexes = m.GetValidBlockIndexes();
//                for (_I i = 0; i < validIndexes.size(); ++i)
//                {
//                    if (validIndexes[i])
//                        _memory[i].Create(m.Get(i));
//                }
//            }
//            
//			~IndexMemory()
//			{
//                const auto & validIndexes = GetValidBlockIndexes();
//				for (_I i = 0; i < validIndexes.size(); ++i)
//				{
//					if (validIndexes[i])
//						_memory[i].Destroy();
//				}
//			}
//
//            _I Insert(const _T & v)
//            {
//                _I index = Allocate();
//                _memory[index].Create(v);
//                return index;
//            }
//            
//            void Remove(_I index)
//            {
//                _memory[index].Destroy();
//                Free(index);
//            }
//            
//			const _T & Get(_I index) const
//			{
//				return *_memory[index].Get();
//			}
//
//            _T & Get(_I index)
//            {
//                return *_memory[index].Get();
//            }
//            
//			_I GetSize() const
//			{
//				return _memory.size() - _numFreeIndex;
//			}
//            
//        private:
//			_I Allocate()
//			{
//				_I index = 0;
//				if (_numFreeIndex == 0)
//				{
//                    _memory.emplace_back();
//					index = _memory.size() - 1;
//				}
//				else
//				{
//					_I prevFreeIndex = GetIndex(_lastFreeIndex);
//					index = _lastFreeIndex;
//					_lastFreeIndex = prevFreeIndex;
//					--_numFreeIndex;
//				}
//
//				return index;
//			}
//
//			void Free(_I index)
//			{
//				if (index < _memory.size())
//				{
//                    GetIndex(index) = _lastFreeIndex;
//					_lastFreeIndex = index;
//					++_numFreeIndex;
//				}
//			}
//            
//            _I & GetIndex(_I index)
//            {
//                return *reinterpret_cast<_I *>(_memory.data() + index);
//            }
//
//            const _I & GetIndex(_I index) const
//            {
//                return *reinterpret_cast<const _I *>(_memory.data() + index);
//            }
//            
//            std::vector<bool> GetValidBlockIndexes() const
//            {
//                std::vector<bool> validBlockIndexes(_memory.size(), true);
//                
//                _I freeIndex = _lastFreeIndex;
//                for (_I i = 0; i < _numFreeIndex; ++i)
//                {
//                    validBlockIndexes[freeIndex] = false;
//                    freeIndex = GetIndex(freeIndex);
//                }
//                
//                return validBlockIndexes;
//            }
//            
//        private:
//			typedef std::vector<MemoryBlock> Memory;
//			Memory _memory;
//			_I _lastFreeIndex;
//			_I _numFreeIndex;
//		};
//	}
//}