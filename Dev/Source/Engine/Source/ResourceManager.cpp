#include "ResourceManager.h"

#include "Resource.h"

namespace FRE
{
	ResourceManager & ResourceManager::GetInstance()
	{
		static ResourceManager resourceManager;
		return resourceManager;
	}

	void ResourceManager::AllocResource(Resource & resource)
	{

	}

	void ResourceManager::FreeResource(Resource & resource)
	{

	}

	void ResourceManager::UpdateResource(Resource & resource)
	{

	}

	void ResourceManager::RegisterClient(IClientResource * client)
	{

	}

	void ResourceManager::DeregisterClient(IClientResource * client)
	{

	}
}