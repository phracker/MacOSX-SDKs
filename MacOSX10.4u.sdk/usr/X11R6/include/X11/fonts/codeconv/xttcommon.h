/* -*- Mode: C; tab-width:4; c-basic-offset: 4; -*- */
/*
   ===FileName: ===
   Copyright (c) 1998 Go Watanabe, All rights reserved.
   Copyright (c) 1998 Takuya SHIOZAKI, All rights reserved.
   Copyright (c) 1998 X-TrueType Server Project, All rights reserved.

===Notice
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
   SUCH DAMAGE.

   Major Release ID: X-TrueType Server Version 1.3 [Aoi MATSUBARA Release 3]

Notice===
*/
/* $XFree86: xc/extras/X-TrueType/xttcommon.h,v 1.8 2001/08/01 00:44:33 tsi Exp $ */

#ifndef _XTTCOMMON_H_
#define _XTTCOMMON_H_ (1)

/*******************************************************
 * Headers
 */

#ifndef FONTMODULE
/* for X11R6.[0-4], XFree86 3.3.x */

  /* ISO C and POSIX Headers */
# include <sys/types.h>
  /* # include <assert.h> */
# include <ctype.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <grp.h>
# include <limits.h>
  /* # include <locale.h> */
# ifdef _XOPEN_SOURCE
#   include <math.h>
# else
#   define _XOPEN_SOURCE   /* to get prototype for hypot on some systems */
#   include <math.h>
#   undef _XOPEN_SOURCE
# endif
# include <pwd.h>
  /* # include <setjmp.h> */
  /* # include <signal.h> */
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
  /* # include <sys/utsname.h> */
  /* # include <sys/wait.h> */
  /* # include <termios.h> */
# include <time.h>
# include <unistd.h>
  /* # include <utime.h> */

#else
/* for New Designed XFree86 */

# include <X11/X.h>
# include <X11/Xmd.h>
# include <X11/Xfuncproto.h>
# include "xf86Module.h"
# include "fontmisc.h"
# include "xf86_ansic.h"

#endif

#include <X11/Xdefs.h>

#include <freetype.h>
#include <ftxsbit.h>

/******************************************************
  Macros
 */

#if 0
#ifndef Bool
#define Bool int
#endif /* Bool */
#endif

#ifndef True
#define True (-1)
#endif /* True */
#ifndef False
#define False (0)
#endif /* False */

/******************************************************
  Prototypes
 */

/* compare strings with ignoring case */
Bool /* False == equal, True == not equal */
mystrcasecmp(char const *s1, char const *s2);

/* strdup clone */
char *
XttXstrdup(char const *str);
#undef xstrdup
#define xstrdup(s) XttXstrdup((char const*)s)

#endif

/* end of file */
