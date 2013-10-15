/* This file is public domain.  */
/* This file exists soley to keep Metrowerks' compilers happy.  The version
   used by GCC 3.4 and later can be found in /usr/lib/gcc, although it's
   not very informative.  */
#ifdef __MWERKS__
#include "mw_float.h"
#else
#error "This header only supports __MWERKS__."
#endif
