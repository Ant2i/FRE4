#pragma once

#include "FreTypes.h"

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

	class RI_Resource : public RefCounterObject
	{
	protected:
		virtual void Destroy() const 
		{
			delete this;
		}

		virtual ~RI_Resource() {}
	};
	
	class RI_RenderTarget : public RI_Resource
	{
	public:
		virtual void SetSize(unsigned width, unsigned height) = 0;

	protected:
		virtual ~RI_RenderTarget() {}
	};

	class RI_VertexBuffer : public RI_Resource
	{
	public:
	};

	struct DarkParams
	{
		uint64 params[6];
	};

	typedef class RI_RenderTarget * RenderTargetH;
	typedef class RI_VertexBuffer * VertexBufferH;
}