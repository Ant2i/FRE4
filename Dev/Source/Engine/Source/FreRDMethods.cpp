#include "RDMethods.h"
#include "RDInterfaces.h"

extern FRE::IRenderDevice * GlobalRD;

#define RD_FUNC_IMPL_DEFS(ReturnType, Name, DefParams, CallParams, DefReturn)\
ReturnType Name DefParams\
{\
	return GlobalRD-> Name CallParams;\
}

#define DEFINE_PF(format, sizeX, sizeY, bytes, num) PFormats[(int)format] = {"format", sizeX, sizeY, bytes, num, 0};

namespace FRE
{
	#include "RDMethodsDefs.inc"
    
    class InitPixelFormat
    {
    public:
        InitPixelFormat()
        {
            DEFINE_PF(EPixelFormat::A8R8G8B8, 0, 0, 0, 0);
        }
        
        PixelFormatInfo PFormats[50];
    };
    
    PixelFormatInfo RDGetPixelFormatInfo(EPixelFormat format)
    {
        static InitPixelFormat init;
        return init.PFormats[(int)format];
    }
}

#undef RD_FUNC_IMPL_DEFS