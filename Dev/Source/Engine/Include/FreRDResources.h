#pragma once

#include "FreTypes.h"
#include "FreSmartPtr.h"

#define DEFINE_DEVICE_TYPE(Type)\
	typedef Type * Type##H;\
	typedef FRE::Utils::IntrusivePtr<Type> Type##Ref;\
	inline void IntrusivePtr_lock(Type * p){ p->AddRef(); }\
	inline void IntrusivePtr_release(Type * p) { p->Release(); }

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

	class RDResource : public RefCounterObject
	{
	protected:
		virtual void Destroy() const 
		{
			delete this;
		}

		virtual ~RDResource() {}
	};
	
	class RDRenderTarget : public RDResource
	{
	public:
		virtual void SetSize(unsigned width, unsigned height) {}

	protected:
		virtual ~RDRenderTarget() {}
	};

	class RDVertexBuffer : public RDResource
	{
	protected:
		virtual ~RDVertexBuffer() {}
	};

	//---------------

	enum class RendetQuetyType
	{

	};

	class RDRenderQuery : public RDResource
	{
	public:
		RDRenderQuery(RendetQuetyType type) :
		_type(type)
		{

		}

		RendetQuetyType GetType() const
		{
			return _type;
		}

	private:
		RendetQuetyType _type;

	protected:
		virtual ~RDRenderQuery() {}
	};

	DEFINE_DEVICE_TYPE(RDRenderTarget);
	DEFINE_DEVICE_TYPE(RDVertexBuffer);
    DEFINE_DEVICE_TYPE(RDRenderQuery);
    
	//-----------------------------------------------------------------------

	struct DarkParams
	{
		uint64 params[6];
	};
}



