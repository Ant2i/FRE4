#include "GLPlatform.h"

namespace FRE
{
	GLPlatform & GetCurrentPlatform()
	{
		static GLPlatform * platform = nullptr;
		if (!platform)
		{
			platform = InitPlatform();
			if (!platform)
			{
				static GLPlatform sEmptyPlatform;
				platform = &sEmptyPlatform;
			}
		}
		return *platform;
	}
}
