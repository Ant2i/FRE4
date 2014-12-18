#pragma once

#include "OpenGLForwardDecl.h"

namespace FRE
{
	class GLResourceManager
	{
	public:
		static GLResourceManager & GetInstance()
		{
			static GLResourceManager sResourceManager;
			return sResourceManager;
		}

		void Register(GLDevice * device)
		{
			_device = device;
		}

		void Unregister(GLDevice * device)
		{
			if (_device == device)
				_device = nullptr;
		}

		void Destroy(GLVertexBuffer * buffer);
		void Destroy(GLStructuredBuffer * buffer);
		void Destroy(GLIndexBuffer * buffer);

	private:
		GLResourceManager(){};

		GLDevice * _device = nullptr;
	};
}