/*
 * Copyright (c) 1999-2006 Apple Inc.  All Rights Reserved.
 * 
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
// Copyright 1988-1996 NeXT Software, Inc.

#ifndef _OBJC_OBJC_API_H_
#define _OBJC_OBJC_API_H_

#include <AvailabilityMacros.h>

/*
 * OBJC_API_VERSION 0 or undef: Tiger and earlier API only
 * OBJC_API_VERSION 2: Leopard and later API available
 */
#if !defined(OBJC_API_VERSION)
#   if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
#       define OBJC_API_VERSION 0
#   else
#       define OBJC_API_VERSION 2
#   endif
#endif

/* OBJC2_UNAVAILABLE: unavailable in objc 2.0, deprecated in Leopard */
#if !defined(OBJC2_UNAVAILABLE)
#   if __OBJC2__
#       define OBJC2_UNAVAILABLE UNAVAILABLE_ATTRIBUTE
#   else
#       define OBJC2_UNAVAILABLE DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER
#   endif
#endif

#if !defined(OBJC_EXPORT)
#   if defined(__cplusplus)
#       define OBJC_EXPORT extern "C" 
#   else
#       define OBJC_EXPORT extern
#   endif
#endif

#if !defined(OBJC_IMPORT)
#   define OBJC_IMPORT extern
#endif

#endif
