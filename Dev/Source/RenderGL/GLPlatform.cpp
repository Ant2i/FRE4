#include "GLPlatform.h"



namespace FRE
{
	GLPlatform & GetCurrentPlatform()
	{
		GLPlatform * platform = GetPlatform();
		if (platform)
			return *platform;

		static GLPlatform sEmptyPlatform;
		return sEmptyPlatform;
	}
}