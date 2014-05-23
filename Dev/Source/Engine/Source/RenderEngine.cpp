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

	std::unique_ptr<RenderEngine, REDeleter> s_engine;

	RenderEngine * RenderEngine::Create(const CreateParams & params)
	{
		if (!s_engine)
			s_engine.reset(new RenderEngine);
		return s_engine.get();
	}

	void RenderEngine::Destroy()
	{
		s_engine = nullptr;
	}

	RenderEngine * RenderEngine::GetInstance()
	{
		return s_engine.get();
	}

	//----------------------------------------------------------------------------

	RenderEngine::RenderEngine()
	{

	}

	RenderEngine::~RenderEngine()
	{

	}
}