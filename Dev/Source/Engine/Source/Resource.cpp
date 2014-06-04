#include "Resource.h"

namespace FRE
{
	static unsigned int sResourceIndexType = 0;

	ResourceType::ResourceType(const char * name, const ResourceType * super) :
		SuperType(super),
		Index(sResourceIndexType++),
        Name(name)
	{

	}

	unsigned ResourceType::NumTypes()
	{
		return sResourceIndexType;
	}

	//-----------------------------------------------------------------------

	const ResourceType Resource::Type("Resource", nullptr);
}