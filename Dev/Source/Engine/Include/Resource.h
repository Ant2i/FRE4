#pragma once

#include "FBase.h"
#include "Types.h"
#include "ResourceManager.h"

namespace FRE
{
	class RE_API Resource
	{
		friend class ResourceManager;

	protected:
		Resource() : 
			_resourceIndex(0), 
			_dynamic(false)
		{
			ResourceManager::GetInstance().AllocResource(*this);
		}

	public:
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
}