#pragma once
#include <string>

namespace FRE
{
	class RenderEngine
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
		RenderEngine(const RenderEngine &);
		~RenderEngine();

		friend class REDeleter;
	};
}