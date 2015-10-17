#pragma once

#include "FPlatform.h"
#include "FSmartPtr.h"
#include "FPixelFormats.h"

#include "RDEnums.h"

#include "RefCounterObject.h"

#include <vector>

#define DEFINE_DEVICE_TYPE(Type)\
	typedef Type * Type##P;\
	typedef ::Utils::IntrusivePtr<Type> Type##Ref;\
	inline void IntrusivePtr_lock(Type * p){ p->AddRef(); }\
	inline void IntrusivePtr_release(Type * p) { p->Release(); }

namespace FRE
{
	struct Color
	{
		Color() :
			R(0.0f), G(0.0f), B(0.0f), A(0.0f)
		{

		}

		Color(float r, float g, float b, float a) :
			R(r), G(g), B(b), A(a)
		{

		}

		float R, G, B, A;
	};
	
	//-----------------------------------------------------------------------

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
		RDVertexBuffer(uint32_t size, uint32_t usage) :
			Size(size),
			Usage(usage)
		{
		}

		const uint32_t Size = 0;
		const uint32_t Usage = 0;

	protected:
		virtual ~RDVertexBuffer() {}
	};

	//-----------------------------------------------------------------------

	class RDIndexBuffer : public RDResource
	{
	public:
		RDIndexBuffer(){}
		RDIndexBuffer(uint32_t size, uint32_t usage, uint32_t stride) :
			Size(size),
			Usage(usage),
			Stride(stride)
		{
		}

		const uint32_t Size = 0;
		const uint32_t Usage = 0;
		const uint32_t Stride = 0;

	protected:
		virtual ~RDIndexBuffer() {}
	};

	//-----------------------------------------------------------------------

	class RDStructureBuffer : public RDResource
	{
	public:
		RDStructureBuffer(){}
		RDStructureBuffer(uint32_t size, uint32_t usage, uint32_t stride) :
			Size(size),
			Usage(usage),
			Stride(stride)
		{
		}

		const uint32_t Size = 0;
		const uint32_t Usage = 0;
		const uint32_t Stride = 0;

	protected:
		virtual ~RDStructureBuffer() {}
	};

	//-----------------------------------------------------------------------

	class RDUniformBuffer : public RDResource
	{
	public:
		RDUniformBuffer(){}
		RDUniformBuffer(uint32_t size) : 
			Size(size)
		{
		}

		const uint32_t Size = 0;
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
		RDTexture(uint8_t numMips, uint8_t numSamples, EPixelFormat format, uint32_t flags) : 
			NumMips(numMips), 
			NumSamples(numSamples), 
			Format(format),
			Flags(flags)
		{}

		const uint8_t NumMips = 0;
		const uint8_t NumSamples = 0;
		const EPixelFormat Format = EPixelFormat::Unknown;
		const uint32_t Flags = 0;

		virtual ETextureType GetType() const { return ETextureType::Unknown; }
		
		virtual uint32_t GetSizeX() const { return 0; }
		virtual uint32_t GetSizeY() const { return 0; }
		virtual uint32_t GetSizeZ() const { return 0; }

		bool IsMultisampled() const { return NumSamples > 1; }
	};

	//-----------------------------------------------------------------------

	class RDTexture2D : public RDTexture
	{
	public:
		RDTexture2D(){}
		RDTexture2D(uint32_t sizeX, uint32_t sizeY, uint32_t numMips, uint32_t numSamples, EPixelFormat format, uint32_t flags) : 
			RDTexture(numMips, numSamples, format, flags), 
			SizeX(sizeX), 
			SizeY(sizeY)
		{}

		virtual ETextureType GetType() const override { return ETextureType::Tex2D; }

		virtual uint32_t GetSizeX() const override { return SizeX; }
		virtual uint32_t GetSizeY() const override { return SizeY; }

		const uint32_t SizeX = 0;
		const uint32_t SizeY = 0;
	};

	//-----------------------------------------------------------------------

	class RDTexture2DArray : public RDTexture
	{
	public:
		RDTexture2DArray(){}
		RDTexture2DArray(uint32_t sizeX, uint32_t sizeY, uint32_t sizeArray, uint32_t numMips, EPixelFormat format, uint32_t flags) :
			RDTexture(numMips, 0, format, flags),
			SizeX(sizeX),
			SizeY(sizeY),
			SizeArray(sizeArray)
		{}

		virtual ETextureType GetType() const override { return ETextureType::Tex2DArray; }

		virtual uint32_t GetSizeX() const override { return SizeX; }
		virtual uint32_t GetSizeY() const override { return SizeY; }
		virtual uint32_t GetSizeZ() const override { return SizeArray; }

		const uint32_t SizeX = 0;
		const uint32_t SizeY = 0;
		const uint32_t SizeArray = 0;
	};

	//-----------------------------------------------------------------------

	class RDTexture3D : public RDTexture
	{
	public:
		RDTexture3D(){}
		RDTexture3D(uint32_t sizeX, uint32_t sizeY, uint32_t sizeZ, uint32_t numMips, EPixelFormat format, uint32_t flags) :
			RDTexture(numMips, 0, format, flags),
			SizeX(sizeX),
			SizeY(sizeY),
			SizeZ(sizeZ)
		{}

		virtual ETextureType GetType() const override { return ETextureType::Tex3D; }

		virtual uint32_t GetSizeX() const override { return SizeX; }
		virtual uint32_t GetSizeY() const override { return SizeY; }
		virtual uint32_t GetSizeZ() const override { return SizeZ; }

		const uint32_t SizeX = 0;
		const uint32_t SizeY = 0;
		// The depth of the texture.
		const uint32_t SizeZ = 0;
	};

	//-----------------------------------------------------------------------

	class RDTextureCube : public RDTexture
	{
	public:
		RDTextureCube(){}
		RDTextureCube(uint32_t sizeXY, uint32_t numMips, EPixelFormat format, uint32_t flags) :
			RDTexture(numMips, 0, format, flags),
			SizeXY(sizeXY)
		{}

		virtual ETextureType GetType() const override { return ETextureType::TexCube; }

		virtual uint32_t GetSizeX() const override { return SizeXY; }
		virtual uint32_t GetSizeY() const override { return SizeXY; }
		
		const uint32_t SizeXY = 0;
	};

	//------------------------------------------------------------------

	class RDShader : public RDResource
	{
	public:
		virtual EShaderType GetType() const { return EShaderType::Unknown; }
		virtual uint8_t * GetSource() const { return nullptr; }
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

	class RDPipelineState : public RDResource 
	{
	};

	class RDViewport : public RDResource
	{
	public:
		RDViewport(){}
		RDViewport(int x, int y, unsigned width, unsigned height) :
			X(x), Y(y), Width(width), Height(height)
		{}

		const int X = 0;
		const int Y = 0; 
		const unsigned Width = 0;
		const unsigned Height = 0;
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
	DEFINE_DEVICE_TYPE(RDPipelineState);
	DEFINE_DEVICE_TYPE(RDVertexDeclaration);
	DEFINE_DEVICE_TYPE(RDViewport);
    
	//-----------------------------------------------------------------------

	struct DarkParams
	{
		uint64_t params[6]; //= {0, 0, 0, 0, 0, 0};
	};

	struct RDRenderTarget
	{
	public:
		RDTextureRef Texture;
		uint32_t MipIndex;

		RDRenderTarget(RDTextureRef texture = nullptr, uint32_t mipIndex = 0) :
			Texture(texture),
			MipIndex(mipIndex)
		{

		}
	};

	//-----------------------------------------------------------------------

	//Vertex element describes.
	struct VertexElementDeclarationDesc
	{
        uint8_t StreamIndex = 0;
		uint8_t Offset = 0;
        EVertexElementType Type = EVertexElementType::None;
		uint8_t AttributeIndex = 0;
		bool UseInstanceIndex = false;

		VertexElementDeclarationDesc()
		{
		}

		VertexElementDeclarationDesc(uint8_t streamIndex, uint8_t offset, EVertexElementType type, uint8_t attributeIndex, bool useInstanceIndex = false) :
			StreamIndex(streamIndex),
			Offset(offset),
			Type(type),
			AttributeIndex(attributeIndex),
			UseInstanceIndex(useInstanceIndex)
		{
		}
	};

	struct PipelineStateDesc
	{
		RDVertexDeclarationRef VertexDeclaration;
		RDVertexShaderRef VertexShader; 
		RDHullShaderRef HullShader;
		RDDomainShaderRef DomainShader;
		RDGeometryShaderRef GeometryShader;
		RDPixelShaderRef PixelShader;
	};

	//-----------------------------------------------------------------------
}



