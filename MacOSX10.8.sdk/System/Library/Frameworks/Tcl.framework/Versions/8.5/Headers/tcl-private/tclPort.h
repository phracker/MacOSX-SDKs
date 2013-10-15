/*
 * tclPort.h --
 *
 *	This header file handles porting issues that occur because
 *	of differences between systems.  It reads in platform specific
 *	portability files.
 *
 * Copyright (c) 1994-1995 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: tclPort.h,v 1.15.10.3 2010/01/31 23:51:36 nijtmans Exp $
 */

#ifndef _TCLPORT
#define _TCLPORT

#ifdef HAVE_TCL_CONFIG_H
#include "tclConfig.h"
#endif
#if defined(_WIN32)
#   include "tclWinPort.h"
#endif
#include "tcl.h"
#if !defined(_WIN32)
#   include "tclUnixPort.h"
#endif

#if defined(__CYGWIN__)
#   define USE_PUTENV 1
#   define USE_PUTENV_FOR_UNSET 1
/* On Cygwin, the environment is imported from the Cygwin DLL. */
    DLLIMPORT extern char **__cygwin_environ;
    DLLIMPORT extern int cygwin_conv_to_win32_path(const char *, char *);
#   define environ __cygwin_environ
#   define timezone _timezone
#endif

#if !defined(LLONG_MIN)
#   ifdef TCL_WIDE_INT_IS_LONG
#      define LLONG_MIN LONG_MIN
#   else
#      ifdef LLONG_BIT
#         define LLONG_MIN ((Tcl_WideInt)(Tcl_LongAsWide(1)<<(LLONG_BIT-1)))
#      else
/* Assume we're on a system with a 64-bit 'long long' type */
#         define LLONG_MIN ((Tcl_WideInt)(Tcl_LongAsWide(1)<<63))
#      endif
#   endif
/* Assume that if LLONG_MIN is undefined, then so is LLONG_MAX */
#   define LLONG_MAX (~LLONG_MIN)
#endif


#endif /* _TCLPORT */
