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

#if !__OBJC2__

#import <objc/Object.h>
#import <Availability.h>

AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED
@interface List : Object
{
@public
    id 		*dataPtr  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;	/* data of the List object */
    unsigned 	numElements  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;	/* Actual number of elements */
    unsigned 	maxElements  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;	/* Total allocated elements */
}

/* Creating, freeing */

- free  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- freeObjects  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- copyFromZone:(void *)z  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
  
/* Initializing */

- init  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- initCount:(unsigned)numSlots  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

/* Comparing two lists */

- (BOOL)isEqual: anObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
  
/* Managing the storage capacity */

- (unsigned)capacity  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- setAvailableCapacity:(unsigned)numSlots  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

/* Manipulating objects by index */

- (unsigned)count  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- objectAt:(unsigned)index  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- lastObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- addObject:anObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- insertObject:anObject at:(unsigned)index  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- removeObjectAt:(unsigned)index  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- removeLastObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- replaceObjectAt:(unsigned)index with:newObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- appendList: (List *)otherList  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

/* Manipulating objects by id */

- (unsigned)indexOf:anObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- addObjectIfAbsent:anObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- removeObject:anObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- replaceObject:anObject with:newObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

/* Emptying the list */

- empty  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

/* Sending messages to elements of the list */

- makeObjectsPerform:(SEL)aSelector  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
- makeObjectsPerform:(SEL)aSelector with:anObject  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

/*
 * The following new... methods are now obsolete.  They remain in this 
 * interface file for backward compatibility only.  Use Object's alloc method 
 * and the init... methods defined in this class instead.
 */

+ new  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;
+ newCount:(unsigned)numSlots  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

@end

typedef struct {
    @defs(List)
} NXListId  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER_BUT_DEPRECATED;

#define NX_ADDRESS(x) (((NXListId *)(x))->dataPtr)

#define NX_NOT_IN_LIST	0xffffffff

#endif

#endif /* _OBJC_LIST_H_ */
