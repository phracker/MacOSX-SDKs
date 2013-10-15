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
 
//  objc_exception.h
//  Support for Objective-C language Exceptions
//
//  Created by Blaine Garst on Fri Nov 01 2002.
//  Copyright (c) 2002-3 Apple Computer, Inc. All rights reserved.
//

#ifndef __OBJC_EXCEPTION_H_
#define __OBJC_EXCEPTION_H_

#import "objc/objc-class.h"

// compiler reserves a setjmp buffer + 4 words as localExceptionData

OBJC_EXPORT void objc_exception_throw(id exception);
OBJC_EXPORT void objc_exception_try_enter(void *localExceptionData);
OBJC_EXPORT void objc_exception_try_exit(void *localExceptionData);
OBJC_EXPORT id objc_exception_extract(void *localExceptionData);
OBJC_EXPORT int objc_exception_match(Class exceptionClass, id exception);


typedef struct {
    int version;
    void (*throw_exc)(id);		// version 0
    void (*try_enter)(void *);	// version 0
    void (*try_exit)(void *);	// version 0
    id	 (*extract)(void *);	// version 0
    int	(*match)(Class, id);	// version 0
}
    objc_exception_functions_t;

// get table; version tells how many
OBJC_EXPORT void objc_exception_get_functions(objc_exception_functions_t *table);

// set table
OBJC_EXPORT void objc_exception_set_functions(objc_exception_functions_t *table);

#endif  // __OBJC_EXCEPTION_H_

