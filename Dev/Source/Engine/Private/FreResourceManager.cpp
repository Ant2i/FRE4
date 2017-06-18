#include "FreResourceManager.h"
#include "FreRenderResource.h"

namespace FRE
{
	ResourceManager & ResourceManager::GetInstance()
	{
		static ResourceManager resourceManager;
		return resourceManager;
	}

	void ResourceManager::AllocResource(RenderResource & resource)
	{

	}

	void ResourceManager::FreeResource(RenderResource & resource)
	{

	}

	void ResourceManager::UpdateResource(RenderResource & resource)
	{

	}

	void ResourceManager::RegisterClient(IClientResource * client)
	{

	}

	void ResourceManager::DeregisterClient(IClientResource * client)
	{

	}
}
