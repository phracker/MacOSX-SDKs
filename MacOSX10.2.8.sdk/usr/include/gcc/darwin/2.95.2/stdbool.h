/* stdbool.h for GNU.  */
#ifndef __STDBOOL_H__
#define __STDBOOL_H__	1

#ifndef __cplusplus
/* Do nothing if included from C++.  Or, should we force an error? */

/* The type `bool' must promote to `int' or `unsigned int'.  The constants
   `true' and `false' must have the value 0 and 1 respectively.  */
typedef int bool;

/* The names `true' and `false' must also be made available as macros.  */
#define false	0
#define true	1

/* Signal that all the definitions are present.  */
#define __bool_true_false_are_defined	1

#endif /* not used in C++ */

#endif	/* stdbool.h */
