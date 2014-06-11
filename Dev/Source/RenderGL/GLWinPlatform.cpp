#include "GLWinPlatform.h"

namespace FRE
{
    class GLObject
    {
    public:
        GLObject(GLTypeObject type) :
            Type(type)
        {

        }

        const GLTypeObject Type;
    };

    class GLWinContext : public GLObject
    {
    public:
        GLWinContext() : GLObject(GLTypeObject::Context)
        {

        }
    };

    class GLWinSurfaceTarget : public GLObject
    {
    public:
        GLWinSurfaceTarget() : GLObject(GLTypeObject::Surface)
        {

        }
    };

	//-----------------------------------------------------------------------

    GLTypeObject GLWinPlatform::GetType(uint64 handle)
    {
        return (GLTypeObject)(handle >> 32);
    }

    uint32 GLWinPlatform::GetIndex(uint64 handle)
    {
        return (uint32)handle;
    }

    uint64 GLWinPlatform::FormHandle(GLTypeObject type, uint32 index)
    {
        return (uint64)((uint32)type << 32 | index);
    }

	//-----------------------------------------------------------------------

    t_GLContext GLWinPlatform::CreateContext()
    {
		GLObjectPtr object(new GLWinContext());
		const uint32 index = Push(object);
        return FormHandle(object->Type, index);
    }

    t_GLRenderTarget GLWinPlatform::CreateSurfaceTarget(t_GLContext context, const DarkParams & params)
    {
        return 0;
    }

	void GLWinPlatform::Destroy(int64 handle)
	{
		Erase(GetIndex(handle));
	}

	uint32 GLWinPlatform::Push(const GLObjectPtr & object)
	{
		size_t index = 0;
		for (; index < _objects.size(); ++index)
		{
			if (_objects[index] == nullptr)
			{
				_objects[index] = object;
				return index;
			}
		}

		_objects.push_back(object);
		return index;
	}

	void GLWinPlatform::Erase(uint32 index)
	{
		if (index < _objects.size())
			_objects[index].reset();
	}
}