/*
 * Copyright (c) 2002-2003, 2006-2007 Apple Inc.  All Rights Reserved.
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

#ifndef __OBJC_EXCEPTION_H_
#define __OBJC_EXCEPTION_H_

#include <objc/objc.h>
#include <stdint.h>

#if !__OBJC2__

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


// !__OBJC2__
#else
// __OBJC2__

typedef id (*objc_exception_preprocessor)(id exception);
typedef int (*objc_exception_matcher)(Class catch_type, id exception);
typedef void (*objc_uncaught_exception_handler)(id exception);
typedef void (*objc_exception_handler)(id unused, void *context);

OBJC_EXPORT void objc_exception_throw(id exception);
OBJC_EXPORT void objc_exception_rethrow(void);
OBJC_EXPORT id objc_begin_catch(void *exc_buf);
OBJC_EXPORT void objc_end_catch(void);

OBJC_EXPORT objc_exception_preprocessor objc_setExceptionPreprocessor(objc_exception_preprocessor fn);
OBJC_EXPORT objc_exception_matcher objc_setExceptionMatcher(objc_exception_matcher fn);
OBJC_EXPORT objc_uncaught_exception_handler objc_setUncaughtExceptionHandler(objc_uncaught_exception_handler fn);

#ifndef __arm__
OBJC_EXPORT uintptr_t objc_addExceptionHandler(objc_exception_handler fn, void *context);
OBJC_EXPORT void objc_removeExceptionHandler(uintptr_t token);
#endif

// __OBJC2__
#endif

#endif  // __OBJC_EXCEPTION_H_

