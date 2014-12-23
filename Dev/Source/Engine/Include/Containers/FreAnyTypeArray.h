#pragma once

#include "FreIndexMemory.h"

namespace FRE
{
	namespace Utils
	{
		template <class _F, typename _I = unsigned>
		class FAnyTypeArray
		{
			typedef typename _F::Type VType;

		private:
			struct HolderBase
			{
				HolderBase(VType type) :
					next(nullptr),
					prev(nullptr),
                    _type(type)
				{

				}

				virtual ~HolderBase()
				{

				}

				VType Type() const { return _type; }
				virtual void * Value() const = 0;

				HolderBase * next;
				HolderBase * prev;

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
			FAnyTypeArray() : 
				headHolder(nullptr)
			{

			}

			~FAnyTypeArray()
			{
				HolderBase * holder = headHolder;
				while (holder)
				{
					HolderBase * next = holder->next;
					delete holder;
					holder = next;
				}
			}

			template <typename _T>
			std::pair<bool, _T> Get(_I index) const
			{
				std::pair<bool, _T> ret;
				ret.first = false;

				if (index < _memory.GetSize())
				{
					const auto & holder = _memory.Get(index);
					if (holder && _F::template GetType<_T>() == holder->Type())
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
				HolderBase * holder = new Holder<_T>(value, _F::template GetType<_T>());
				holder->next = headHolder;
				if (headHolder)
					headHolder->prev = holder;
				headHolder = holder;

				return _memory.Allocate(holder);
			}

			void Remove(_I index)
			{
				if (index < _memory.GetSize())
				{
					HolderBase * holder = _memory.Get(index);
					if (holder->prev != nullptr)
						holder->prev->next = holder->next;
					else
						headHolder = holder->next;

					if (holder->next != nullptr)
						holder->next->prev = holder->prev;

					delete holder;
					_memory.Free(index);
				}
			}

		private:
			FAnyTypeArray(const FAnyTypeArray & arr)
			{
			}

			FAnyTypeArray & operator=(const FAnyTypeArray &) 
			{
			}

		private:
			FIndexMemory<HolderBase *, _I> _memory;
			HolderBase * headHolder;
		};
	}
}