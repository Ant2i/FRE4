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
	class GLWinContext;
	class GLWinSurfaceTarget;

	typedef std::shared_ptr<GLObject> GLObjectPtr;
	
	class GLWinPlatform : public GLPlatform
	{
	public:
		GLWinPlatform();
		~GLWinPlatform();

		virtual h_GLContext CreateContext(h_GLContext shared) override;
		virtual h_GLRenderTarget CreateSurfaceTarget(h_GLContext context, const DarkParams & params) override;

		virtual bool MakeCurrentContext(h_GLContext context) override;
		virtual bool MakeCurrentContext(h_GLContext context, h_GLRenderTarget target) override;
		virtual bool SwapContext(h_GLContext context, h_GLRenderTarget target) override;

		virtual void Destroy(int64 handle) override;

		void Init();

		template <typename T>
		T * GetTypedObject(uint64 handle)
		{
			GLObject * object = Get(GetIndex(handle));
			if (object && object->GetType() == T::Type)
				return static_cast<T*>(object);
			return nullptr;
		}

		HWND GetGlobalWindow() const { return _window; }

	private:
		static GLTypeObject GetType(uint64 handle);
		static uint32 GetIndex(uint64 handle);
		static uint64 FormHandle(GLTypeObject type, uint32 index);

		uint32 Push(const GLObjectPtr & object);
		void Erase(uint32 index);
		GLObject * Get(uint32 index) const;

		std::vector<GLObjectPtr> _objects;

		HWND _window;
	};
}