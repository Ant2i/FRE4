#pragma once

#include "FArrayMemory.h"

namespace FRE
{
	namespace Utils
	{
		template <class _F, typename _I = unsigned>
		class FTypedArray
		{
			typedef typename _F::Type VType;

		private:
			struct HolderBase
			{
				HolderBase(VType type) :
					_type(type)
				{

				}

				virtual ~HolderBase()
				{

				}

				VType Type() const { return _type; }
				virtual void * Value() const = 0;

			private:
				VType _type;
			};

			template <typename _T>
			struct Holder : public HolderBase
			{
				Holder(_T value, VType type) :
					HolderBase(type),
					_value(value)
				{

				}

				virtual ~Holder()
				{

				}

				virtual void * Value() const override
				{
					return (void *)&_value;
				}

			private:
				_T _value;
			};

		public:
			FTypedArray()
			{

			}

			FTypedArray(const FTypedArray & arr) :
				_memory(arr._memory)
			{

			}

			template <typename _T>
			std::pair<bool, _T> Get(_I index) const
			{
				std::pair<bool, _T> ret;
				ret.first = false;

				if (index < _memory.GetSize())
				{
					const auto & holder = _memory.Get(index);
					if (holder && _F::GetType<_T>() == holder->Type())
					{
						ret.first = true;
						ret.second = *reinterpret_cast<_T *>(holder->Value());
					}
				}
				return ret;
			}

			template <typename _T>
			_I Add(_T value)
			{
				HolderBase * holder = new Holder<_T>(value, _F::GetType<_T>());
				return _memory.Allocate(holder);
			}

			void Remove(_I index)
			{
				if (index < _memory.GetSize())
				{
					delete _memory.Get(index);
					_memory.Free(index);
				}
			}

		private:
			FArrayMemory<HolderBase *, _I> _memory;
		};
	}
}