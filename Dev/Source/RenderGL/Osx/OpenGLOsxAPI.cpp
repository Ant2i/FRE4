#include "OpenGLOsxAPI.h"

namespace FRE
{

bool PlatformInitOpenGL()
{
    FOpenGL::Init(FOpenGL::GetExtensionString());
    
#ifdef _DEBUG
    auto capaility = FOpenGL::GetCapability();
#endif
    
    return true;
}

}