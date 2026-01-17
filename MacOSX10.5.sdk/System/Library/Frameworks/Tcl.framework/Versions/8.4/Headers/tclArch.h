/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 2004 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __TCLARCH_H__
#define __TCLARCH_H__

#include <sys/cdefs.h>

#ifdef __BIG_ENDIAN__
#define WORDS_BIGENDIAN 1
#else /* !__BIG_ENDIAN__ */
/* #undef WORDS_BIGENDIAN */
#endif /* __BIG_ENDIAN__ */

#ifdef __LP64__
#define TCL_WIDE_INT_IS_LONG 1
#else /* !__LP64__ */
#define TCL_WIDE_INT_TYPE long long
#endif /* __LP64__ */

#ifdef __DARWIN_UNIX03
#define USE_TERMIOS 1
#else /* !__DARWIN_UNIX03 */
#define HAVE_PUTENV_THAT_COPIES 1
#endif /* __DARWIN_UNIX03 */

#endif /* __TCLARCH_H__ */
