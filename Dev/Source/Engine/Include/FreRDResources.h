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

	enum EPixelFormat
	{
		PF_Unknown = 0,
		PF_A32B32G32R32F = 1,
		PF_B8G8R8A8 = 2,
		PF_G8 = 3,
		PF_G16 = 4,
		PF_DXT1 = 5,
		PF_DXT3 = 6,
		PF_DXT5 = 7,
		PF_UYVY = 8,
		PF_FloatRGB = 9,
		PF_FloatRGBA = 10,
		PF_DepthStencil = 11,
		PF_ShadowDepth = 12,
		PF_R32_FLOAT = 13,
		PF_G16R16 = 14,
		PF_G16R16F = 15,
		PF_G16R16F_FILTER = 16,
		PF_G32R32F = 17,
		PF_A2B10G10R10 = 18,
		PF_A16B16G16R16 = 19,
		PF_D24 = 20,
		PF_R16F = 21,
		PF_R16F_FILTER = 22,
		PF_BC5 = 23,
		PF_V8U8 = 24,
		PF_A1 = 25,
		PF_FloatR11G11B10 = 26,
		PF_A8 = 27,
		PF_R32_UINT = 28,
		PF_R32_SINT = 29,
		PF_PVRTC2 = 30,
		PF_PVRTC4 = 31,
		PF_R16_UINT = 32,
		PF_R16_SINT = 33,
		PF_R16G16B16A16_UINT = 34,
		PF_R16G16B16A16_SINT = 35,
		PF_R5G6B5_UNORM = 36,
		PF_R8G8B8A8 = 37,
		PF_A8R8G8B8 = 38,			
		PF_BC4 = 39,
		PF_R8G8 = 40,
		PF_ATC_RGB = 41,
		PF_ATC_RGBA_E = 42,
		PF_ATC_RGBA_I = 43,
		PF_X24_G8 = 44,		
		PF_ETC1 = 45,
		PF_ETC2_RGB = 46,
		PF_ETC2_RGBA = 47,
		PF_MAX = 48,
	};

	class RDTexture : public RDResource
	{
	public:
		RDTexture(uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) : 
			_numMips(numMips), 
			_numSamples(numSamples), 
			_format(format),
			_flags(flags)
		{}

		uint32 GetNumMips() const { return _numMips; }

		EPixelFormat GetFormat() const { return _format; }

		uint32 GetFlags() const { return _flags; }

		uint32 GetNumSamples() const { return _numSamples; }

		bool IsMultisampled() const { return _numSamples > 1; }

	private:
		uint32 _numMips;
		uint32 _numSamples;
		EPixelFormat _format;
		uint32 _flags;
	};

	class RDTexture2D : public RDTexture
	{
	public:
		RDTexture2D(uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) : 
			RDTexture(numMips, numSamples, format, flags), 
			_sizeX(sizeX), 
			_sizeY(sizeY)
		{}

		uint32 GetSizeX() const { return _sizeX; }

		uint32 GetSizeY() const { return _sizeY; }

	private:
		uint32 _sizeX;
		uint32 _sizeY;
	};

	DEFINE_DEVICE_TYPE(RDRenderTarget);
	DEFINE_DEVICE_TYPE(RDVertexBuffer);
    DEFINE_DEVICE_TYPE(RDRenderQuery);
	DEFINE_DEVICE_TYPE(RDTexture2D);
    
	//-----------------------------------------------------------------------

	struct DarkParams
	{
		uint64 params[6];
	};
}



