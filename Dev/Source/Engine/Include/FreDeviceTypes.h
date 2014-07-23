#pragma once

#include "FreTypes.h"

namespace FRE
{
	//typedef struct RI_RenderTarget * RHRenderTarget;
	//typedef struct RI_VertexBuffer * RHVertexBuffer;

	template <typename _T>
	class RefCounter
	{
	private:
		typedef _T BaseType;

	public:
		RefCounter(): _numRefs(0) {}
		virtual ~RefCounter() { /*check(!_numRefs);*/ }

		uint32 AddRef() const
		{
			return ++_numRefs;
		}

		uint32 Release() const
		{
			uint32 Refs = --_numRefs;
			if (Refs == 0)
				_FreeObject(static_cast<BaseType *>(this));
			return Refs;
		}
		
	private:
		mutable uint32 _numRefs;
	};

	//template <typename _T>
	//class RefCounterObj : public RefCounter
	//{
	//public:
	//	RefCounterObj

	//protected:
	//	void Destroy() const
	//	{
	//		;
	//	}
	//};

	class RI_Resource //: public RefCounter<RI_Resource>
	{
	public:
		RI_Resource() //: RefCounter<RI_Resource>(*this)
		{
		}

	public:
		virtual void Destroy() = 0;
	};
	
	//void _FreeObject(RI_Resource * resource)
	//{
	//	resource->Destroy();
	//}

	class RI_RenderTarget : public RI_Resource
	{
	public:
		virtual void SetSize(unsigned width, unsigned height) = 0;
	};

	class RI_VertexBuffer : public RI_Resource
	{
	
	};

	struct DarkParams
	{
		uint64 params[6];
	};

	typedef class RI_RenderTarget * RenderTargetH;
	typedef class RI_VertexBuffer * VertexBufferH;
}