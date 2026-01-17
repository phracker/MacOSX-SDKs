/* This file is public domain.  */
/* GCC uses its own copy of this header */
#if defined(__GNUC__)
#include_next <varargs.h>
#elif defined(__MWERKS__)
#include "mw_varargs.h"
#else
#error "This header only supports __MWERKS__."
#endif
