#include "X11GLAPI.h"
#include "FPlatform.h"

#ifdef PLATFORM_LINUX

namespace FRE
{
    bool PlatformInitOpenGL()
    {
        bool isInit = glewInit() == GLEW_OK;
        if (isInit)
            FOpenGL::Init(FOpenGL::GetExtensionString());

#ifdef _DEBUG
        auto capaility = FOpenGL::GetCapability();
#endif

        return isInit;
    }
}


#endif