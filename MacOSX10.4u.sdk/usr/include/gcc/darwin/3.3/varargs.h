/* APPLE LOCAL begin MW compatibility */
#ifdef __MWERKS__
#include "mw_varargs.h"
#else
/* APPLE LOCAL end MW compatibility */

#ifndef _VARARGS_H
#define _VARARGS_H

#error "GCC no longer implements <varargs.h>."
#error "Revise your code to use <stdarg.h>."

#endif
/* APPLE LOCAL MW compatibility */
#endif /* __MWERKS__ */
