#include "RenderEngine.h"
#include <memory>

namespace FRE
{
	class REDeleter
	{
	public:
		void operator()(RenderEngine * engine) const
		{
			delete engine;
		}
	};

	std::unique_ptr<RenderEngine, REDeleter> s_renderEngine;

	RenderEngine * RenderEngine::Create(const CreateParams & params)
	{
		if (!s_renderEngine)
			s_renderEngine.reset(new RenderEngine);
		return s_renderEngine.get();
	}

	void RenderEngine::Destroy()
	{
		s_renderEngine.reset(nullptr);
	}

	RenderEngine * RenderEngine::GetInstance()
	{
		return s_renderEngine.get();
	}

	//----------------------------------------------------------------------------

	RenderEngine::RenderEngine()
	{

	}

	RenderEngine::RenderEngine(const RenderEngine &)
	{

	}

	RenderEngine::~RenderEngine()
	{

	}
}