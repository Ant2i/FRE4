#pragma once

#include "FOpenGLPlatform.h"
#include "FreAnyTypeArray.h"

#include "windows.h"

#include <vector>
#include <memory>

namespace FRE
{
	//enum class GLTypeObject : unsigned int
	//{
	//	Context = 1,
	//	Surface
	//};

	struct GLWinObj
	{
		virtual ~GLWinObj(){}
	};

	struct GLWinSurfaceTarget : public GLWinObj
	{
		//enum
		//{
		//	Type = GLTypeObject::Surface
		//};

		GLWinSurfaceTarget(HWND hwnd, HDC hdc);
		~GLWinSurfaceTarget();

		bool Swap() const;
		void Resize(unsigned width, unsigned height);

		HWND Hwnd;
		HDC Hdc;
	};

	struct GLWinContext : public GLWinObj
	{
		//enum
		//{
		//	Type = GLTypeObject::Context
		//};

		GLWinContext(HGLRC hrc);
		~GLWinContext();
		HGLRC Hglrc;
	};

	//class ObjectContainer
	//{
	//public:
	//	template <typename T>
	//	T * Get(uint64 handle)
	//	{
	//		auto res = _objects.Get<std::shared_ptr<T>>(GetIndex(handle));
	//		if (res.first)
	//			return res.second.get();
	//		return nullptr;
	//	}

	//	template <typename T>
	//	uint64 Add(T * handle)
	//	{
	//		if (handle)
	//		{
	//			const uint32 index = _objects.Add(std::shared_ptr<T>(handle));
	//			return FormHandle((GLTypeObject)T::Type, index);
	//		}
	//		return 0;
	//	}

	//	void Remove(uint64 handle)
	//	{
	//		_objects.Remove(GetIndex(handle));
	//	}

	//	static uint32 GetIndex(uint64 handle);
	//	static uint64 FormHandle(GLTypeObject type, uint32 index);

	//private:
	//	struct ObjectTypeGetter
	//	{
	//		typedef uint32 Type;

	//		template <typename T>
	//		static Type GetType() { return T::element_type::Type; }
	//	};

	//	FRE::Utils::FAnyTypeArray<ObjectTypeGetter, uint32> _objects;
	//};

	//----------------

	GLWinContext * CreateContext(HDC hdc, unsigned major, unsigned minor, GLWinContext * shared = nullptr, bool debug = false);
	GLWinSurfaceTarget * CreateTarget(int pixelFormat, HWND parent);

	bool WGLCheckCapabilities(HDC hdc, unsigned major, unsigned minor);
	HGLRC WGLCreateContext(HDC hdc, unsigned major, unsigned minor, HGLRC shareHrc, bool debug);
	PIXELFORMATDESCRIPTOR WGLGetDefaultPixelFormatDesc();

	HWND WinCreateWindow(const char * name, unsigned width, unsigned height, HWND parent);
	void WinDestroyWindow(HWND hwnd);
	DWORD WinGetLastError(const char ** msg);
}