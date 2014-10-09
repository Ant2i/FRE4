#pragma once

#include "FreTypes.h"
#include "FrePixelFormats.h"
#include "FreRefCounterObject.h"
#include "FreSmartPtr.h"
#include "FreMath.h"
#include "FreRDEnums.h"

#define DEFINE_DEVICE_TYPE(Type)\
	typedef Type * Type##P;\
	typedef FRE::Utils::IntrusivePtr<Type> Type##Ref;\
	inline void IntrusivePtr_lock(Type * p){ p->AddRef(); }\
	inline void IntrusivePtr_release(Type * p) { p->Release(); }

namespace FRE
{
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
	public:
		RDVertexBuffer(uint32 size, uint32 usage) :
			Size(size),
			Usage(usage)
		{
		}

		const uint32 Size;
		const uint32 Usage;

	protected:
		virtual ~RDVertexBuffer() {}
	};

	class RDIndexBuffer : public RDResource
	{
	public:
		RDIndexBuffer(uint32 size, uint32 usage, uint32 stride) :
			Size(size),
			Usage(usage),
			Stride(stride)
		{
		}

		const uint32 Size;
		const uint32 Usage;
		const uint32 Stride;

	protected:
		virtual ~RDIndexBuffer() {}
	};

	class RDStructureBuffer : public RDResource
	{
	public:
		RDStructureBuffer(uint32 size, uint32 usage, uint32 stride) :
			Size(size),
			Usage(usage),
			Stride(stride)
		{
		}

		const uint32 Size;
		const uint32 Usage;
		const uint32 Stride;

	protected:
		virtual ~RDStructureBuffer() {}
	};

	class RDRenderQuery : public RDResource
	{
	public:
		RDRenderQuery(RendetQuetyType type) :
			Type(type)
		{

		}

		const RendetQuetyType Type;

	protected:
		virtual ~RDRenderQuery() {}
	};

	class RDTexture : public RDResource
	{
	public:
		RDTexture(uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) : 
			NumMips(numMips), 
			NumSamples(numSamples), 
			Format(format),
			Flags(flags)
		{}

		const uint32 NumMips;
		const uint32 NumSamples;
		const EPixelFormat Format;
		const uint32 Flags;

		bool IsMultisampled() const { return NumSamples > 1; }
	};

	class RDTexture2D : public RDTexture
	{
	public:
		RDTexture2D(uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) : 
			RDTexture(numMips, numSamples, format, flags), 
			SizeX(sizeX), 
			SizeY(sizeY)
		{}

		const uint32 SizeX;
		const uint32 SizeY;
	};

	DEFINE_DEVICE_TYPE(RDRenderTarget);
	DEFINE_DEVICE_TYPE(RDVertexBuffer);
	DEFINE_DEVICE_TYPE(RDIndexBuffer);
	DEFINE_DEVICE_TYPE(RDStructureBuffer);
    DEFINE_DEVICE_TYPE(RDRenderQuery);
	DEFINE_DEVICE_TYPE(RDTexture2D);
    
	//-----------------------------------------------------------------------

	struct DarkParams
	{
		uint64 params[6];
	};
}



