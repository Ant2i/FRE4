#pragma once

namespace FRE
{
	class RefCounterObject
	{
	public:
		RefCounterObject() :
			_refCount(0)
		{

		}

		void AddRef()
		{
			++_refCount;
		}

		void Release()
		{
			if (_refCount > 1)
				--_refCount;
			else	
				Destroy();
		}

	protected:
		virtual void Destroy() = 0;
		~RefCounterObject() { }

	private:
		uint32_t _refCount;
	};
}