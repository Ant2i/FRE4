#pragma once

#include "FreBase.h"

namespace FRE
{
	class IRenderDevice;

	class CORE_EXPORT Engine
	{
	public:
		struct CreateParams
		{
			sPath renderDeviceName;
		};

	public:
		static Engine * Create(const CreateParams & params);
		static void Destroy();
		static Engine * GetInstance();
		static IRenderDevice & GetActiveRenderDevice();

		IRenderDevice & ActiveRenderDevice() const;

	private:
		Engine();
		~Engine();

		friend class REDeleter;
	};
}