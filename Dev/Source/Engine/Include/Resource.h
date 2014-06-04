#pragma once

#include "Base.h"
#include "Types.h"
#include "ResourceManager.h"

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

	class RE_API Resource
	{
		friend class ResourceManager;

	protected:
		Resource() :
            _dynamic(false),
			_resourceIndex(0)
			
		{
			ResourceManager::GetInstance().AllocResource(*this);
		}

	public:
		static const ResourceType Type;

		~Resource()
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

	protected:
		bool _dynamic;

	private:
		unsigned _resourceIndex;
	};

#define TEXT(s) s

#define DECLARE_RESOURCE_TYPE(TypeName, SuperType) \
	typedef SuperType SuperResource; \
	static const ResourceType Type; \

#define IMPLEMENT_RESOURCE_TYPE(TypeName) \
	const ResourceType TypeName::Type(TEXT(#TypeName), &TypeName::SuperResource::Type);
}