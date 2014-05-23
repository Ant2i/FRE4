#pragma once

#include "FBase.h"
#include <string>

namespace FRE
{
	class RE_API RenderEngine
	{
	public:
		struct CreateParams
		{
			std::string renderDeviceName;
		};

	public:
		static RenderEngine * Create(const CreateParams & params);
		static void Destroy();

		static RenderEngine * GetInstance();

	private:
		RenderEngine();
		~RenderEngine();

		friend class REDeleter;
	};
}