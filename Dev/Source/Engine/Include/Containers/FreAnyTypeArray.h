#pragma once

#include "FreIndexMemory.h"

namespace FRE
{
	namespace Utils
	{
		template <class _F, typename _I = unsigned>
		class AnyTypeArray
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
			AnyTypeArray()
			{

			}

			~AnyTypeArray()
			{
				
			}

			template <typename _T>
			std::pair<bool, _T> Get(_I index) const
			{
				std::pair<bool, _T> ret;
				ret.first = false;

				const auto & holder = _data.Get(index);
				if (_F::template GetType<_T>() == holder->Type())
				{
					ret.first = true;
					ret.second = *reinterpret_cast<_T *>(holder->Value());
				}
                
				return ret;
			}

			template <typename _T>
			_I Add(_T value)
			{
				HolderBase * holder = new Holder<_T>(value, _F::template GetType<_T>());
                return _data.Insert(std::shared_ptr<HolderBase>(holder));
			}

			void Remove(_I index)
			{
                _data.Remove(index);
			}

		private:
			AnyTypeArray(const AnyTypeArray & arr)
			{
			}

			AnyTypeArray & operator=(const AnyTypeArray &) 
			{
			}

		private:
            IndexMemory<std::shared_ptr<HolderBase>, _I> _data;
		};
	}
}