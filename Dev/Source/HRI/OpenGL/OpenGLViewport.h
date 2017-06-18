#pragma once

#include "RDResources.h"

namespace FRE
{
	class GLRenderSurface;

	class GLViewport : public RDViewport
	{
	public:
		GLViewport(int x, int y, unsigned width, unsigned height) :
			RDViewport(x, y, width, height)
		{

		}

		void SetSurface(GLRenderSurface * surface)
		{
			_surface = surface;
		}

		GLRenderSurface * GetSurface() const
		{
			return _surface;
		}

	private:
		typedef ::Utils::IntrusivePtr<GLRenderSurface> GLRenderSurfaceP;
		GLRenderSurfaceP _surface;
	};

}
