#pragma once

#include "FSmartPtr.h"

template <typename _Ty>
inline void IntrusivePtr_lock(_Ty * p){ p->AddRef(); }
template <typename _Ty>
inline void IntrusivePtr_release(_Ty * p) { p->Release(); }
