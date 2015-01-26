#pragma once

#include "FPlatform.h"
#include "FMathDefs.h"
#include "FSmartPtr.h"
#include "FPixelFormats.h"

#include "RDEnums.h"

#include "FreRefCounterObject.h"

#include <vector>

#define DEFINE_DEVICE_TYPE(Type)\
	typedef Type * Type##P;\
	typedef ::Utils::IntrusivePtr<Type> Type##Ref;\
	inline void IntrusivePtr_lock(Type * p){ p->AddRef(); }\
	inline void IntrusivePtr_release(Type * p) { p->Release(); }

namespace FRE
{
	class RDResource : public RefCounterObject
	{
	protected:
		virtual void Destroy() override
		{
			delete this;
		}

		virtual ~RDResource() {}
	};
	
	//-----------------------------------------------------------------------

	class RDRenderOutput : public RDResource
	{
	public:
		virtual void SetSize(unsigned width, unsigned height) {}

	protected:
		virtual ~RDRenderOutput() {}
	};

	//-----------------------------------------------------------------------

	class RDVertexBuffer : public RDResource
	{
	public:
		RDVertexBuffer() {}
		RDVertexBuffer(uint32 size, uint32 usage) :
			Size(size),
			Usage(usage)
		{
		}

		const uint32 Size = 0;
		const uint32 Usage = 0;

	protected:
		virtual ~RDVertexBuffer() {}
	};

	//-----------------------------------------------------------------------

	class RDIndexBuffer : public RDResource
	{
	public:
		RDIndexBuffer(){}
		RDIndexBuffer(uint32 size, uint32 usage, uint32 stride) :
			Size(size),
			Usage(usage),
			Stride(stride)
		{
		}

		const uint32 Size = 0;
		const uint32 Usage = 0;
		const uint32 Stride = 0;

	protected:
		virtual ~RDIndexBuffer() {}
	};

	//-----------------------------------------------------------------------

	class RDStructureBuffer : public RDResource
	{
	public:
		RDStructureBuffer(){}
		RDStructureBuffer(uint32 size, uint32 usage, uint32 stride) :
			Size(size),
			Usage(usage),
			Stride(stride)
		{
		}

		const uint32 Size = 0;
		const uint32 Usage = 0;
		const uint32 Stride = 0;

	protected:
		virtual ~RDStructureBuffer() {}
	};

	//-----------------------------------------------------------------------

	class RDUniformBuffer : public RDResource
	{
	public:
		RDUniformBuffer(){}
		RDUniformBuffer(uint32 size) : 
			Size(size)
		{
		}

		const uint32 Size = 0;
	};

	//-----------------------------------------------------------------------

	class RDRenderQuery : public RDResource
	{
	public:
		RDRenderQuery(){}
		RDRenderQuery(ERenderQueryType type) :
			Type(type)
		{

		}

		const ERenderQueryType Type = ERenderQueryType::Unknown;

	protected:
		virtual ~RDRenderQuery() {}
	};

	//-----------------------------------------------------------------------

	class RDTexture : public RDResource
	{
	public:
		RDTexture(){}
		RDTexture(uint8 numMips, uint8 numSamples, EPixelFormat format, uint32 flags) : 
			NumMips(numMips), 
			NumSamples(numSamples), 
			Format(format),
			Flags(flags)
		{}

		const uint8 NumMips = 0;
		const uint8 NumSamples = 0;
		const EPixelFormat Format = EPixelFormat::Unknown;
		const uint32 Flags = 0;

		virtual ETextureType GetType() const { return ETextureType::Unknown; }
		
		virtual uint32 GetSizeX() const { return 0; }
		virtual uint32 GetSizeY() const { return 0; }
		virtual uint32 GetSizeZ() const { return 0; }

		bool IsMultisampled() const { return NumSamples > 1; }
	};

	//-----------------------------------------------------------------------

	class RDTexture2D : public RDTexture
	{
	public:
		RDTexture2D(){}
		RDTexture2D(uint32 sizeX, uint32 sizeY, uint32 numMips, uint32 numSamples, EPixelFormat format, uint32 flags) : 
			RDTexture(numMips, numSamples, format, flags), 
			SizeX(sizeX), 
			SizeY(sizeY)
		{}

		virtual ETextureType GetType() const override { return ETextureType::Tex2D; }

		virtual uint32 GetSizeX() const override { return SizeX; }
		virtual uint32 GetSizeY() const override { return SizeY; }

		const uint32 SizeX = 0;
		const uint32 SizeY = 0;
	};

	//-----------------------------------------------------------------------

	class RDTexture2DArray : public RDTexture
	{
	public:
		RDTexture2DArray(){}
		RDTexture2DArray(uint32 sizeX, uint32 sizeY, uint32 sizeArray, uint32 numMips, EPixelFormat format, uint32 flags) :
			RDTexture(numMips, 0, format, flags),
			SizeX(sizeX),
			SizeY(sizeY),
			SizeArray(sizeArray)
		{}

		virtual ETextureType GetType() const override { return ETextureType::Tex2DArray; }

		virtual uint32 GetSizeX() const override { return SizeX; }
		virtual uint32 GetSizeY() const override { return SizeY; }
		virtual uint32 GetSizeZ() const override { return SizeArray; }

		const uint32 SizeX = 0;
		const uint32 SizeY = 0;
		const uint32 SizeArray = 0;
	};

	//-----------------------------------------------------------------------

	class RDTexture3D : public RDTexture
	{
	public:
		RDTexture3D(){}
		RDTexture3D(uint32 sizeX, uint32 sizeY, uint32 sizeZ, uint32 numMips, EPixelFormat format, uint32 flags) :
			RDTexture(numMips, 0, format, flags),
			SizeX(sizeX),
			SizeY(sizeY),
			SizeZ(sizeZ)
		{}

		virtual ETextureType GetType() const override { return ETextureType::Tex3D; }

		virtual uint32 GetSizeX() const override { return SizeX; }
		virtual uint32 GetSizeY() const override { return SizeY; }
		virtual uint32 GetSizeZ() const override { return SizeZ; }

		const uint32 SizeX = 0;
		const uint32 SizeY = 0;
		// The depth of the texture.
		const uint32 SizeZ = 0;
	};

	//-----------------------------------------------------------------------

	class RDTextureCube : public RDTexture
	{
	public:
		RDTextureCube(){}
		RDTextureCube(uint32 sizeXY, uint32 numMips, EPixelFormat format, uint32 flags) :
			RDTexture(numMips, 0, format, flags),
			SizeXY(sizeXY)
		{}

		virtual ETextureType GetType() const override { return ETextureType::TexCube; }

		virtual uint32 GetSizeX() const override { return SizeXY; }
		virtual uint32 GetSizeY() const override { return SizeXY; }
		
		const uint32 SizeXY = 0;
	};

	//------------------------------------------------------------------

	class RDShader : public RDResource
	{
	public:
		virtual EShaderType GetType() const { return EShaderType::Unknown; }
		virtual uint8 * GetSource() const { return nullptr; }
	};

	class RDVertexShader : public RDShader
	{
	public:
		virtual EShaderType GetType() const override { return EShaderType::Vertex; }
	};

	class RDHullShader : public RDShader
	{
	public:
		virtual EShaderType GetType() const override { return EShaderType::Hull; }
	};

	class RDDomainShader : public RDShader
	{
	public:
		virtual EShaderType GetType() const override { return EShaderType::Domain; }
	};

	class RDPixelShader : public RDShader
	{
	public:
		virtual EShaderType GetType() const override { return EShaderType::Pixel; }
	};

	class RDGeometryShader : public RDShader
	{
	public:
		virtual EShaderType GetType() const override { return EShaderType::Geometry; }
	};

	class RDComputeShader : public RDShader
	{
	public:
		virtual EShaderType GetType() const override { return EShaderType::Compute; }
	};

	class RDBoundShaderState : public RDResource 
	{
	};

	//-----------------------------------------------------------------------

	class RDVertexDeclaration : public RDResource 
	{
	};

	//-----------------------------------------------------------------------

	DEFINE_DEVICE_TYPE(RDRenderOutput);
	DEFINE_DEVICE_TYPE(RDVertexBuffer);
	DEFINE_DEVICE_TYPE(RDIndexBuffer);
	DEFINE_DEVICE_TYPE(RDStructureBuffer);
	DEFINE_DEVICE_TYPE(RDUniformBuffer);
    DEFINE_DEVICE_TYPE(RDRenderQuery);
	DEFINE_DEVICE_TYPE(RDTexture);
	DEFINE_DEVICE_TYPE(RDTexture2D);
	DEFINE_DEVICE_TYPE(RDTexture2DArray);
	DEFINE_DEVICE_TYPE(RDTexture3D);
	DEFINE_DEVICE_TYPE(RDTextureCube);
	DEFINE_DEVICE_TYPE(RDVertexShader);
	DEFINE_DEVICE_TYPE(RDHullShader);
	DEFINE_DEVICE_TYPE(RDDomainShader);
	DEFINE_DEVICE_TYPE(RDPixelShader);
	DEFINE_DEVICE_TYPE(RDGeometryShader);
	DEFINE_DEVICE_TYPE(RDComputeShader);
	DEFINE_DEVICE_TYPE(RDBoundShaderState);
	DEFINE_DEVICE_TYPE(RDVertexDeclaration);
    
	//-----------------------------------------------------------------------

	struct DarkParams
	{
		uint64 params[6]; //= {0, 0, 0, 0, 0, 0};
	};

	struct RDRenderTarget
	{
	public:
		RDTextureRef Texture;
		uint32 MipIndex;

		RDRenderTarget(RDTextureRef texture = nullptr, uint32 mipIndex = 0) :
			Texture(texture),
			MipIndex(mipIndex)
		{

		}
	};

	//-----------------------------------------------------------------------

	struct VertexElement
	{
		uint8 StreamIndex;
		uint8 Offset;
		EVertexElementType Type;
		uint8 AttributeIndex;
		bool UseInstanceIndex;

		VertexElement() {}
		VertexElement(uint8 streamIndex, uint8 offset, EVertexElementType type, uint8 attributeIndex, bool useInstanceIndex = false) :
			StreamIndex(streamIndex),
			Offset(offset),
			Type(type),
			AttributeIndex(attributeIndex),
			UseInstanceIndex(useInstanceIndex)
		{}
	};

	typedef std::vector<VertexElement> VertexDeclarationElementList;

	//-----------------------------------------------------------------------
}



