#pragma once

#include "FBase.h"
#include "Types.h"

namespace FRE
{
	class IRenderDevice;

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

		IRenderDevice * GetActiveRenderDevice() const;

	private:
		RenderEngine();
		~RenderEngine();

		friend class REDeleter;
	};
}