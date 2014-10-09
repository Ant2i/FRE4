#pragma once

#include "FreBase.h"

namespace FRE
{
	class RefCounterObject
	{
	public:
		RefCounterObject() :
			_refCount(0)
		{

		}

		uint32 AddRef() const
		{
			return ++_refCount;
		}

		uint32 Release() const
		{
			uint32 refs = --_refCount;
			if (refs == 0)
				Destroy();
			return refs;
		}

	protected:
		virtual void Destroy() const = 0;
		~RefCounterObject() { /*check(!_numRefs);*/ }

	private:
		mutable uint32 _refCount;
	};
}