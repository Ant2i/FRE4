#include "OpenGLResourceManager.h"
#include "OpenGLDevice.h"
#include "OpenGLResources.h"

namespace FRE
{
	void GLResourceManager::Destroy(GLVertexBuffer * buffer)
	{
		if (_device)
		{
			_device->GetSharedContext().FlushArrayBuffer(buffer->Name);
			_device->GetRenderContext().FlushArrayBuffer(buffer->Name);
		}
		delete buffer;
	}

	void GLResourceManager::Destroy(GLStructuredBuffer * buffer)
	{
		if (_device)
		{
			_device->GetSharedContext().FlushArrayBuffer(buffer->Name);
			_device->GetRenderContext().FlushArrayBuffer(buffer->Name);
		}
		delete buffer;
	}

	void GLResourceManager::Destroy(GLIndexBuffer * buffer)
	{
		if (_device)
		{
			_device->GetSharedContext().FlushElementArrayBuffer(buffer->Name);
			_device->GetRenderContext().FlushElementArrayBuffer(buffer->Name);
		}
		delete buffer;
	}
}