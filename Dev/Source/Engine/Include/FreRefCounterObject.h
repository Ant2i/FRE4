#pragma once

#include "FreBase.h"
#include "FreAssert.h"

namespace FRE
{
	class RefCounterObject
	{
	public:
		RefCounterObject() :
			_refCount(0)
		{

		}

		uint32 AddRef()
		{
			return ++_refCount;
		}

		uint32 Release()
		{
			uint32 refs = --_refCount;
			if (refs == 0)
				Destroy();
			return refs;
		}

	protected:
		virtual void Destroy() = 0;
		~RefCounterObject() { FRE_ASSERT(!_refCount); }

	private:
		uint32 _refCount;
	};
}