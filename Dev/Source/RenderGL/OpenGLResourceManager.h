#pragma once

#include "OpenGLBase.h"
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

		void DestroyArrayBuffer(GLBuffer * buffer);
		void DestroyElementBuffer(GLBuffer * buffer);

	private:
		GLResourceManager(){};
		GLDevice * _device = nullptr;
	};
}