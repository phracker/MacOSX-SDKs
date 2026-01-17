/*
 * Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 2004 Apple Computer, Inc.  All Rights Reserved.
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
/*
 *	objc-auto.h
 *	Copyright 2004 Apple Computer, Inc.
 */

#ifndef _OBJC_AUTO_H_
#define _OBJC_AUTO_H_

#import <objc/objc.h>
#include <sys/types.h>

/* Collection utilities */

enum {
    OBJC_GENERATIONAL = (1 << 0)
};

OBJC_EXPORT void objc_collect_if_needed(unsigned long options);
OBJC_EXPORT unsigned int objc_numberAllocated(void);
OBJC_EXPORT BOOL objc_collecting_enabled(void);

/* Memory management */
OBJC_EXPORT id objc_allocate_object(Class cls, int extra);

/* Write barriers */
OBJC_EXPORT id objc_assign_strongCast(id val, id *dest);
OBJC_EXPORT id objc_assign_global(id val, id *dest);
OBJC_EXPORT id objc_assign_ivar(id value, id dest, unsigned int offset);
OBJC_EXPORT void *objc_memmove_collectable(void *dst, const void *src, size_t size);

/* Testing tools */
OBJC_EXPORT BOOL objc_is_finalized(void *ptr);


#endif
