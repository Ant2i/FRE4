#pragma once

#include <algorithm>

#ifndef INTRUSIVE_PTR_LOCK
#define INTRUSIVE_PTR_LOCK(a)\
	if (a) IntrusivePtr_lock(a);
#endif

#ifndef INTRUSIVE_PTR_RELEASE
#define INTRUSIVE_PTR_RELEASE(a)\
	if (a) IntrusivePtr_release(a);
#endif

namespace Utils
{
	template<typename T>
	class IntrusivePtr
	{
	public:
		typedef T* Pointer;

	public:
		IntrusivePtr() :
			_ref(nullptr)
		{
		}

		IntrusivePtr(T * p) :
			_ref(p)
		{
			INTRUSIVE_PTR_LOCK(_ref);
		}

		IntrusivePtr(const IntrusivePtr & ptr) :
			_ref(ptr._ref)
		{
			INTRUSIVE_PTR_LOCK(_ref);
		}

		virtual ~IntrusivePtr()
		{
			INTRUSIVE_PTR_RELEASE(_ref);
		}

		IntrusivePtr & operator=(const IntrusivePtr & ptr)
		{
			IntrusivePtr tmp(ptr);
			Swap(*this, tmp);
			return *this;
		}

		inline T & operator*() const
		{
			//assert(_ref);
			return *_ref;
		}

		inline T * operator->() const
		{
			//assert(_ref);
			return _ref;
		}

		T * Get() const
		{
			return _ref;
		}

		void Reset(T * p = nullptr)
		{
			IntrusivePtr tmp(p);
			Swap(*this, tmp);
		}

		operator Pointer() const
		{
			return _ref;
		}

	private:
		T * _ref;

		void Swap(IntrusivePtr & a, IntrusivePtr & b)
		{
			std::swap(a._ref, b._ref);
		}
	};
}
