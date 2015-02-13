#pragma once

#include <vector>

namespace FRE
{
	namespace Utils
	{
		template <bool>
		struct ClassDestroer
		{
		public:
			void Destroy(_T * v)
			{
				v->~_T();
			}
		};

		template <>
		struct ClassDestroer<false>
		{
		public:
			void Destroy(_T * v)
			{

			}
		};


		struct MBlock : public ClassDestroer<std::is_scalar<_T>::value>
		{
			MBlock(const _T & v)
			{
				Init();
				new (data)_T(v);
			}

			MBlock(const MBlock & v)
			{
				Init();
				new (data)_T(*(_T *)v.data);
			}

			void Destroy()
			{
#ifdef _DEBUG
				Validate();
				_check = 0x1;
#endif
				__super::Destroy(reinterpret_cast<_T *>(data));
			}

			void Validate() const
			{
#ifdef _DEBUG
				assert(_check == 0x0);
#endif
			}

			char data[sizeof(_T)];

		private:
			void Init()
			{
#ifdef _DEBUG
				_check = 0x0;
#endif
			}

#ifdef _DEBUG
			_I _check;
#endif
		};

		template <typename _T, typename _I = unsigned>
		class IndexMemory
		{
		public:
			IndexMemory() :
				_nextFreeIndex(0),
				_numFreeIndex(0)
			{

			}

			IndexMemory(const IndexMemory & v) :
				_memory(v._memory),
				_nextFreeIndex(v._nextFreeIndex),
				_numFreeIndex(v._numFreeIndex)
			{

			}

			~IndexMemory()
			{
				const auto size = _memory.size();
				std::vector<bool> freeIndexes(size);
				std::fill(freeIndexes.begin(), freeIndexes.end(), true);

				_I next = _nextFreeIndex;
				for (_I i = 0; i < _numFreeIndex; ++i)
				{
					freeIndexes[next] = false;
					next = *reinterpret_cast<_I *>(_memory.data() + next);
				}

				for (_I i = 0; i < size; ++i)
				{
					if (freeIndexes[i])
						(_memory.data() + i)->Destroy();
				}
			}

			const _T & Get(_I index) const
			{
				return (const _T &)_memory[index];
			}

			_T & Get(_I index)
			{
				return (_T &)_memory[index];
			}

			_I GetSize() const
			{
				return _memory.size() - _numFreeIndex;
			}

			_I Allocate(const _T & value)
			{
				_I index = 0;
				if (_numFreeIndex == 0)
				{
					_memory.push_back(value);
					index = _memory.size() - 1;
				}
				else
				{
					_I oldIndex = *(_I *)(_memory.data() + _nextFreeIndex);
					new (&_memory[_nextFreeIndex]) MBlock(value);
					index = _nextFreeIndex;

					_nextFreeIndex = oldIndex;
					--_numFreeIndex;
				}

				return index;
			}

			void Free(_I index)
			{
				if (index < _memory.size())
				{
					MBlock * data = _memory.data() + index;
					data->Destroy();
					*(_I *)(data) = _nextFreeIndex;
					_nextFreeIndex = index;
					++_numFreeIndex;
				}
			}

		private:
			typedef std::vector<MBlock> Memory;
			Memory _memory;
			_I _nextFreeIndex;
			_I _numFreeIndex;
		};
	}
}