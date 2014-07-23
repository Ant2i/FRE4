#pragma once

#include "FreBase.h"
#include "FreTypes.h"
#include "FreResourceManager.h"

namespace FRE
{
	class RE_API ResourceType
	{
	public:
		ResourceType(const char * name, const ResourceType * super);

		inline bool IsA(const ResourceType & type) const
		{
			const ResourceType * current = this;
			while (current)
			{
				if (current == &type)
					return true;
				current = current->SuperType;
			};
			return false;
		}

		const ResourceType * const SuperType;
		const unsigned Index;
		const char * Name;

		static unsigned NumTypes();
	};

	//-----------------------------------------------------------------------

	class RE_API RenderResource
	{
		friend class ResourceManager;

	protected:
		RenderResource() :
            _dynamic(false),
			_resourceIndex(0)
			
		{
			ResourceManager::GetInstance().AllocResource(*this);
		}

	public:
		static const ResourceType Type;

		~RenderResource()
		{
			ResourceManager::GetInstance().FreeResource(*this);
		}

		void Update()
		{
			ResourceManager::GetInstance().UpdateResource(*this);
		}

		inline unsigned GetResourceIndex() const 
		{
			return _resourceIndex;
		}

		inline bool IsDynamic() const
		{
			return _dynamic;
		}

		inline const ResourceType * GetType() const
		{
			return _type;
		}

	protected:
		const ResourceType * _type;
		bool _dynamic;

	private:
		unsigned _resourceIndex;
	};

#define DECLARE_RESOURCE_TYPE(TypeName, SuperType) \
	typedef SuperType SuperResource; \
	static const ResourceType Type; \

#define IMPLEMENT_RESOURCE_TYPE(TypeName) \
	const ResourceType TypeName::Type(#TypeName, &TypeName::SuperResource::Type);

#define CONSTRUCTOR_RESOURCE_TYPE() \
	_type = &Type;
}