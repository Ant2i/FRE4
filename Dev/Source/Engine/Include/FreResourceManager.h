#pragma once

#include "FreBase.h"

namespace FRE
{
	class Resource;
	
	class IClientResource
	{
	public:
		virtual void FreeResource(const Resource & Resource) = 0;
		virtual void UpdateResource(const Resource & Resource) = 0;

	protected:
		~IClientResource() {}
	};

	class RE_API ResourceManager
	{
	public:
		static ResourceManager & GetInstance();

		void AllocResource(Resource & resource);
		void FreeResource(Resource & resource);
		void UpdateResource(Resource & resource);

		void RegisterClient(IClientResource * client);
		void DeregisterClient(IClientResource * client);

	private:

	};
}