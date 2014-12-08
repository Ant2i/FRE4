#include "FreRDMethods.h"
#include "FreRDInterfaces.h"

extern FRE::IRenderDevice * GlobalRD;

#define RD_FUNC_IMPL_DEFS(ReturnType, Name, DefParams, CallParams, DefReturn)\
ReturnType Name##DefParams\
{\
	return GlobalRD->##Name##CallParams;\
}

namespace FRE
{
	#include "FreRDMethodsDefs.inc"
}

#undef RD_FUNC_IMPL_DEFS