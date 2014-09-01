#pragma once

#include "FreTypes.h"
#include "FreSmartPtr.h"


#define DEFINE_DEVICE_TYPE(Type)\
	typedef RD_##Type * Type##H;\
	typedef FRE::Utils::IntrusivePtr<RD_##Type> Type##Ref;\
	inline void IntrusivePtr_lock(RD_##Type * p){ p->AddRef(); }\
	inline void IntrusivePtr_release(RD_##Type * p) { p->Release();}

namespace FRE
{
	class RefCounterObject
	{
	public:
		RefCounterObject(): 
			_refCount(0) 
		{

		}

		uint32 AddRef() const
		{
			return ++_refCount;
		}

		uint32 Release() const
		{
			uint32 Refs = --_refCount;
			if (Refs == 0)
				Destroy();
			return Refs;
		}

	protected:
		virtual void Destroy() const = 0;
		~RefCounterObject() { /*check(!_numRefs);*/ }

	private:
		mutable uint32 _refCount;
	};

	class RD_Resource : public RefCounterObject
	{
	protected:
		virtual void Destroy() const 
		{
			delete this;
		}

		virtual ~RD_Resource() {}
	};
	
	class RD_RenderTarget : public RD_Resource
	{
	public:
		virtual void SetSize(unsigned width, unsigned height) = 0;

	protected:
		virtual ~RD_RenderTarget() {}
	};

	class RD_VertexBuffer : public RD_Resource
	{
	protected:
		virtual ~RD_VertexBuffer() {}
	};

	class RD_RenderQuery : public RD_Resource
	{
	protected:
		virtual ~RD_RenderQuery() {}
	};

	DEFINE_DEVICE_TYPE(RenderTarget);
	DEFINE_DEVICE_TYPE(VertexBuffer);

	//-----------------------------------------------------------------------

	struct DarkParams
	{
		uint64 params[6];
	};
}



