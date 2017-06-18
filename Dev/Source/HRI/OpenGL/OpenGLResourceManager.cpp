#include "OpenGLResourceManager.h"
#include "OpenGLDevice.h"
#include "OpenGLResources.h"

namespace FRE
{
	void GLResourceManager::DestroyArrayBuffer(GLBuffer * buffer)
	{
		if (_device)
		{
			_device->GetSharedContext().FlushArrayBuffer(buffer->Name);
			_device->GetRenderContext().FlushArrayBuffer(buffer->Name);
		}
		delete buffer;
	}

	void GLResourceManager::DestroyElementBuffer(GLBuffer * buffer)
	{
		if (_device)
		{
			_device->GetSharedContext().FlushElementArrayBuffer(buffer->Name);
			_device->GetRenderContext().FlushElementArrayBuffer(buffer->Name);
		}
		delete buffer;
	}
}
