#pragma once

#include "FreBase.h"

namespace FRE
{
	class RenderResource;
	
	class IClientResource
	{
	public:
		virtual void FreeResource(const RenderResource & Resource) = 0;
		virtual void UpdateResource(const RenderResource & Resource) = 0;

	protected:
		~IClientResource() {}
	};

	class RE_API ResourceManager
	{
	public:
		static ResourceManager & GetInstance();

		void AllocResource(RenderResource & resource);
		void FreeResource(RenderResource & resource);
		void UpdateResource(RenderResource & resource);

		void RegisterClient(IClientResource * client);
		void DeregisterClient(IClientResource * client);

	private:

	};
}
