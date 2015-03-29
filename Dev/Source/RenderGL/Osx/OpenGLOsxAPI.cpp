#include "OpenGLOsxAPI.h"

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