#pragma once

#include "FreIndexMemory.h"

#include <typeinfo>
#include <memory>

namespace FRE
{
	namespace Utils
	{
		struct StdTypeInfo
		{
			typedef const std::type_info & Info;
		
			template <typename T>
			static Info GetInfo() { return typeid(T); }
		};

		template<typename _TT>
		class AnyType
		{
			typedef typename ::Info TypeInfo;

		public:
			template<typename _Ty>
			AnyType(_Ty value) :
			{

			}

			AnyType(AnyType && other) : 
				_holder(std::move(other._holder))
			{

			}

			template <typename _Ty>
			bool CheckType() const
			{
				if (_holder)
					return _holder->Type() == _TT::GetInfo<_Ty>());
				return false;
			}

			template <typename _Ty>
			_Ty Get() const
			{
				if (_holder)
					return static_cast<AnyType::Holder<_Ty> *>(_holder)->Value;

				throw std::exception("Bad cast type.");
			}

		private:
			struct HolderBase
			{
				HolderBase(TypeInfo type) :
					_type(type)
				{

				}

				virtual ~HolderBase()
				{

				}

				TypeInfo Type() const { return _type; }

			private:
				TypeInfo _type;
			};

			template <typename _T>
			struct Holder : public HolderBase
			{
				Holder(_T value, TypeInfo type) :
					HolderBase(type),
					_value(value)
				{

				}

				virtual ~Holder()
				{

				}

			public:
				_T Value;
			};

			std::unique_ptr<HolderBase> _holder;
		};


		template <class _F, typename _I = unsigned>
		class AnyTypeArray
		{
			typedef AnyType<_F> AType;

		public:
			AnyTypeArray()
			{

			}

			~AnyTypeArray()
			{
				
			}

			template <typename _Ty>
			std::pair<bool, _Ty> Get(_I index) const
			{
				std::pair<bool, _Ty> ret;
				ret.first = false;

				const auto & value = _data[index];
				if (value->CheckType<_Ty>())
				{
					ret.first = true;
					ret.second = value->Get<_Ty>();
				}
                
				return ret;
			}

			template <typename _Ty>
			void Add(_Ty value)
			{
				std::unique_ptr<HolderBase> holder(new Holder<_Ty>(value, _F::template GetType<_Ty>()));
                return _data.emplace_back(std::move(holder));
			}

			void Remove(_I index)
			{
                _data.erase(_data.begin() + index);
			}

		private:
			AnyTypeArray(const AnyTypeArray & arr)
			{
			}

			AnyTypeArray & operator=(const AnyTypeArray &) 
			{
			}

		private:
			std::vector<std::unique_ptr<HolderBase>> _data;
		};
	}
}