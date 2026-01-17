/*
 * Copyright (c) 1999-2002, 2005-2007 Apple Inc.  All Rights Reserved.
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
/*
    List.h
    Copyright 1988-1996 NeXT Software, Inc.

    DEFINED AS:	A common class
    HEADER FILES:	objc/List.h

*/

#ifndef _OBJC_LIST_H_
#define _OBJC_LIST_H_

#if defined(__OBJC2__)

#warning class List unavailable

#else

#warning The API in this header is obsoleted by NSArray.

#import <objc/Object.h>
#import <AvailabilityMacros.h>

DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER 
@interface List : Object
{
@public
    id 		*dataPtr  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER ;	/* data of the List object */
    unsigned 	numElements  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER ;	/* Actual number of elements */
    unsigned 	maxElements  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER ;	/* Total allocated elements */
}

/* Creating, freeing */

- free  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- freeObjects  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- copyFromZone:(void *)z  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
  
/* Initializing */

- init  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- initCount:(unsigned)numSlots  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Comparing two lists */

- (BOOL)isEqual: anObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
  
/* Managing the storage capacity */

- (unsigned)capacity  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- setAvailableCapacity:(unsigned)numSlots  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Manipulating objects by index */

- (unsigned)count  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- objectAt:(unsigned)index  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- lastObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- addObject:anObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- insertObject:anObject at:(unsigned)index  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- removeObjectAt:(unsigned)index  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- removeLastObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- replaceObjectAt:(unsigned)index with:newObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- appendList: (List *)otherList  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Manipulating objects by id */

- (unsigned)indexOf:anObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- addObjectIfAbsent:anObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- removeObject:anObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- replaceObject:anObject with:newObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Emptying the list */

- empty  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Sending messages to elements of the list */

- makeObjectsPerform:(SEL)aSelector  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- makeObjectsPerform:(SEL)aSelector with:anObject  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 * The following new... methods are now obsolete.  They remain in this 
 * interface file for backward compatibility only.  Use Object's alloc method 
 * and the init... methods defined in this class instead.
 */

+ new  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
+ newCount:(unsigned)numSlots  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

typedef struct {
    @defs(List)
} NXListId  DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

#define NX_ADDRESS(x) (((NXListId *)(x))->dataPtr)

#define NX_NOT_IN_LIST	0xffffffff

#endif

#endif /* _OBJC_LIST_H_ */
