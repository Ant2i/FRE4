#pragma once

#include <vector>

namespace FRE
{
	namespace Utils
	{
		template <typename _T, typename _I = unsigned>
		class FIndexMemory
		{
		public:
			FIndexMemory() :
				_nextFreeIndex(0),
				_numFreeIndex(0)
			{

			}

			FIndexMemory(const FIndexMemory & v) :
				_memory(v._memory),
				_nextFreeIndex(v._nextFreeIndex),
				_numFreeIndex(v._numFreeIndex)
			{

			}

			const _T & Get(_I index) const
			{
				return _memory[index];
			}

			_T & Get(_I index)
			{
				return _memory[index];
			}

			_I GetSize() const
			{
				return _memory.size();
			}

			_I Allocate(const _T & value)
			{
				_I index(0);
				if (_numFreeIndex == 0)
				{
					_memory.push_back(value);
					index = _memory.size() - 1;
				}
				else
				{
					_I oldIndex = *(_I *)(_memory.data() + _nextFreeIndex);
					new (&_memory[_nextFreeIndex]) _T(value);
					index = _nextFreeIndex;

					_nextFreeIndex = oldIndex;
					--_numFreeIndex;
				}
				return index;
			}

			void Free(_I index)
			{
				//assert(IsAlreadyFreeIndex(index) == false)

				_T * data = _memory.data() + index;
				_memory.get_allocator().destroy(data);
				*(_I *)(data) = _nextFreeIndex;
				_nextFreeIndex = index;
				++_numFreeIndex;
			}

		private:
			bool IsAlreadyFreeIndex(_I index) const
			{
				_I next = _nextFreeIndex;
				for (_I i = 0; i < _numFreeIndex; ++i)
				{
					if (next == index)
						return true;
					next = *(_I *)(_memory.data() + next);
				}
				return false;
			}

			typedef std::vector<_T> Memory;
			Memory _memory;
			_I _nextFreeIndex;
			_I _numFreeIndex;
		};
	}
}