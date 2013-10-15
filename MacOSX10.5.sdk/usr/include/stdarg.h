/* This file is public domain.  */
/* GCC uses its own copy of this header */
#if defined(__GNUC__)
#include_next <stdarg.h>
#elif defined(__MWERKS__)
#include "mw_stdarg.h"
#else
#error "This header only supports __MWERKS__."
#endif
