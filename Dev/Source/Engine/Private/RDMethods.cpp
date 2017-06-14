#include "RDMethods.h"
#include "RDInterfaces.h"

extern FRE::IRenderDevice * GlobalRD;

#define RD_FUNC_IMPL_DEFS(ReturnType, Name, DefParams, CallParams, DefReturn)\
ReturnType Name DefParams\
{\
	return GlobalRD-> Name CallParams;\
}

namespace FRE
{
	#include "RDMethodsDefs.inc"
    
    PixelFormatInfo RDGetPixelFormatInfo(EPixelFormat format)
    {
		static InitializePixelFormat init;
        return init.PixelFormats[(int)format];
    }
}

#undef RD_FUNC_IMPL_DEFS
