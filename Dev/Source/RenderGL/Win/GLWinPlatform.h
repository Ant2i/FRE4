#pragma once

#include "GLPlatform.h"
#include "windows.h"

#include "FTypeArray.h"

#include <vector>
#include <memory>

namespace FRE
{
	enum class GLTypeObject : uint32
	{
		Context = 1,
		Surface
	};

	
	struct ObjectTypeGetter
	{
		typedef int Type;

		template <typename T>
		static Type GetType() { return T::element_type::Type; }
	};


	class GLWinPlatform
	{
	public:
		GLWinPlatform();
		~GLWinPlatform();

		h_GLContext CreateContext(h_GLContext shared);
		h_GLRenderTarget CreateSurfaceTarget(h_GLContext context, const DarkParams & params);

		bool MakeCurrentContext(h_GLContext context);
		bool MakeCurrentContext(h_GLContext context, h_GLRenderTarget target);
		bool SwapContext(h_GLContext context, h_GLRenderTarget target);

		void Destroy(int64 handle);

		bool Init();

		HWND GlobalHwnd() const { return _hwnd; }
		HDC	GlobalHdc() const { return _hdc; }

	private:
		static GLTypeObject GetType(uint64 handle);
		static uint32 GetIndex(uint64 handle);
		static uint64 FormHandle(GLTypeObject type, uint32 index);

		template <typename T>
		T * GetTypedObject(uint64 handle)
		{
			auto res = _objects.Get<std::shared_ptr<T>>(GetIndex(handle));
			if (res.first)
				return res.second.get();
			return nullptr;
		}

		Utils::FTypedArray<ObjectTypeGetter, uint32> _objects;

		HWND _hwnd;
		HDC _hdc;
		bool _initialize;
	};
}