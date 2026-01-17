/* This file is public domain.  */
/* stdbool.h has moved to avoid accidental use with a non-GCC
   compiler.  Only GCC should have used stdbool.h due to licensing
   restrictions.  */
#ifdef __MWERKS__
#include "mw_stdbool.h"
#else
#error "This header only supports __MWERKS__."
#endif

