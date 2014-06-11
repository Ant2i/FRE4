#pragma once

#include "GLPlatform.h"
#include "windows.h"
#include <vector>
#include <memory>

namespace FRE
{
	enum class GLTypeObject : uint32
	{
		Context = 1,
		Surface
	};

	class GLObject;
	typedef std::shared_ptr<GLObject> GLObjectPtr;
	
	class GLWinPlatform : public GLPlatform
	{
	public:
		virtual t_GLContext CreateContext() override;
		virtual t_GLRenderTarget CreateSurfaceTarget(t_GLContext context, const DarkParams & params) override;
		virtual void Destroy(int64 handle) override;

	private:
		static GLTypeObject GetType(uint64 handle);
		static uint32 GetIndex(uint64 handle);
		static uint64 FormHandle(GLTypeObject type, uint32 index);

		uint32 Push(const GLObjectPtr & object);
		void Erase(uint32 index);

		std::vector<GLObjectPtr> _objects;
	};
}