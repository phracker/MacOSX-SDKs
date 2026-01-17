/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
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

#warning The API in this header is obsoleted by NSArray.

#ifndef _OBJC_LIST_H_
#define _OBJC_LIST_H_

#import <objc/Object.h>

@interface List : Object
{
@public
    id 		*dataPtr;	/* data of the List object */
    unsigned 	numElements;	/* Actual number of elements */
    unsigned 	maxElements;	/* Total allocated elements */
}

/* Creating, freeing */

- free;
- freeObjects;
- copyFromZone:(void *)z;
  
/* Initializing */

- init;
- initCount:(unsigned)numSlots;

/* Comparing two lists */

- (BOOL)isEqual: anObject;
  
/* Managing the storage capacity */

- (unsigned)capacity;
- setAvailableCapacity:(unsigned)numSlots;

/* Manipulating objects by index */

- (unsigned)count;
- objectAt:(unsigned)index;
- lastObject;
- addObject:anObject;
- insertObject:anObject at:(unsigned)index;
- removeObjectAt:(unsigned)index;
- removeLastObject;
- replaceObjectAt:(unsigned)index with:newObject;
- appendList: (List *)otherList;

/* Manipulating objects by id */

- (unsigned)indexOf:anObject;
- addObjectIfAbsent:anObject;
- removeObject:anObject;
- replaceObject:anObject with:newObject;

/* Emptying the list */

- empty;

/* Sending messages to elements of the list */

- makeObjectsPerform:(SEL)aSelector;
- makeObjectsPerform:(SEL)aSelector with:anObject;

/*
 * The following new... methods are now obsolete.  They remain in this 
 * interface file for backward compatibility only.  Use Object's alloc method 
 * and the init... methods defined in this class instead.
 */

+ new;
+ newCount:(unsigned)numSlots;

@end

typedef struct {
    @defs(List)
} NXListId;

#define NX_ADDRESS(x) (((NXListId *)(x))->dataPtr)

#define NX_NOT_IN_LIST	0xffffffff

#endif /* _OBJC_LIST_H_ */
