/*
 * Copyright (c) 1999-2007 Apple Inc.  All Rights Reserved.
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

#ifndef _OBJC_MESSAGE_H
#define _OBJC_MESSAGE_H

#include <objc/objc.h>
#include <objc/runtime.h>


#ifndef OBJC_SUPER
#define OBJC_SUPER
struct objc_super {
    id receiver;
#if !defined(__cplusplus)  &&  !__OBJC2__
    Class class;  /* For compatibility with old objc-runtime.h header */
#else
    Class super_class;
#endif
    /* super_class is the first class to search */
};
#endif


/* Basic Messaging Primitives
 *
 * On some architectures, use objc_msgSend_stret for some struct return types.
 * On some architectures, use objc_msgSend_fpret for some float return types.
 * On some architectures, use objc_msgSend_fp2ret for some float return types.
 *
 * These functions must be cast to an appropriate function pointer type 
 * before being called. 
 */
OBJC_EXPORT id objc_msgSend(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
OBJC_EXPORT id objc_msgSendSuper(struct objc_super *super, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);


/* Struct-returning Messaging Primitives
 *
 * Use these functions to call methods that return structs on the stack. 
 * On some architectures, some structures are returned in registers. 
 * Consult your local function call ABI documentation for details.
 * 
 * These functions must be cast to an appropriate function pointer type 
 * before being called. 
 */
#if defined(__OBJC2__)
OBJC_EXPORT void objc_msgSend_stret(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
OBJC_EXPORT void objc_msgSendSuper_stret(struct objc_super *super, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
#elif defined(__cplusplus)
/* For compatibility with old objc-runtime.h header */
OBJC_EXPORT id objc_msgSend_stret(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
OBJC_EXPORT id objc_msgSendSuper_stret(struct objc_super *super, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
#else
/* For compatibility with old objc-runtime.h header */
OBJC_EXPORT void objc_msgSend_stret(void * stretAddr, id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
OBJC_EXPORT void objc_msgSendSuper_stret(void * stretAddr, struct objc_super *super, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
#endif


/* Floating-point-returning Messaging Primitives
 * 
 * Use these functions to call methods that return floating-point values 
 * on the stack. 
 * Consult your local function call ABI documentation for details.
 * 
 * arm:    objc_msgSend_fpret not used
 * i386:   objc_msgSend_fpret used for `float`, `double`, `long double`.
 * x86-64: objc_msgSend_fpret used for `long double`.
 *
 * arm:    objc_msgSend_fp2ret not used
 * i386:   objc_msgSend_fp2ret not used
 * x86-64: objc_msgSend_fp2ret used for `_Complex long double`.
 *
 * These functions must be cast to an appropriate function pointer type 
 * before being called. 
 */
#if defined(__i386__)

OBJC_EXPORT double objc_msgSend_fpret(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_2_0);

/* Use objc_msgSendSuper() for fp-returning messages to super. */
/* See also objc_msgSendv_fpret() below. */

#elif defined(__x86_64__)

OBJC_EXPORT long double objc_msgSend_fpret(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);

# if __STDC_VERSION__ >= 199901L
OBJC_EXPORT _Complex long double objc_msgSend_fp2ret(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);
# else
OBJC_EXPORT void objc_msgSend_fp2ret(id self, SEL op, ...)
    __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);
# endif

/* Use objc_msgSendSuper() for fp-returning messages to super. */
/* See also objc_msgSendv_fpret() below. */

#endif


/* Direct Method Invocation Primitives
 * Use these functions to call the implementation of a given Method.
 * This is faster than calling method_getImplementation() and method_getName().
 *
 * The receiver must not be nil.
 *
 * These functions must be cast to an appropriate function pointer type 
 * before being called. 
 */
OBJC_EXPORT id method_invoke(id receiver, Method m, ...) 
     __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);
OBJC_EXPORT void method_invoke_stret(id receiver, Method m, ...) 
     __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_2_0);


/* Message Forwarding Primitives
 * Use these functions to forward a message as if the receiver did not 
 * respond to it. 
 *
 * The receiver must not be nil.
 * 
 * class_getMethodImplementation() may return (IMP)_objc_msgForward.
 * class_getMethodImplementation_stret() may return (IMP)_objc_msgForward_stret
 * 
 * These functions must be cast to an appropriate function pointer type 
 * before being called. 
 *
 * Before Mac OS X 10.6, _objc_msgForward must not be called directly 
 * but may be compared to other IMP values.
 */
OBJC_EXPORT id _objc_msgForward(id receiver, SEL sel, ...) 
     __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_2_0);
OBJC_EXPORT void _objc_msgForward_stret(id receiver, SEL sel, ...) 
     __OSX_AVAILABLE_STARTING(__MAC_10_6, __IPHONE_3_0);


/* Variable-argument Messaging Primitives
 *
 * Use these functions to call methods with a list of arguments, such 
 * as the one passed to forward:: .
 *
 * The contents of the argument list are architecture-specific. 
 * Consult your local function call ABI documentation for details.
 * 
 * These functions must be cast to an appropriate function pointer type 
 * before being called, except for objc_msgSendv_stret() which must not 
 * be cast to a struct-returning type.
 */

typedef void* marg_list;

OBJC_EXPORT id objc_msgSendv(id self, SEL op, size_t arg_size, marg_list arg_frame) OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_msgSendv_stret(void *stretAddr, id self, SEL op, size_t arg_size, marg_list arg_frame) OBJC2_UNAVAILABLE;
/* Note that objc_msgSendv_stret() does not return a structure type, 
 * and should not be cast to do so. This is unlike objc_msgSend_stret() 
 * and objc_msgSendSuper_stret().
 */
#if defined(__i386__)
OBJC_EXPORT double objc_msgSendv_fpret(id self, SEL op, unsigned arg_size, marg_list arg_frame) OBJC2_UNAVAILABLE;
#endif


/* The following marg_list macros are of marginal utility. They
 * are included for compatibility with the old objc-class.h header. */

#if !__OBJC2__

#define marg_prearg_size	0

#define marg_malloc(margs, method) \
	do { \
		margs = (marg_list *)malloc (marg_prearg_size + ((7 + method_getSizeOfArguments(method)) & ~7)); \
	} while (0)

#define marg_free(margs) \
	do { \
		free(margs); \
	} while (0)
	
#define marg_adjustedOffset(method, offset) \
	(marg_prearg_size + offset)

#define marg_getRef(margs, offset, type) \
	( (type *)((char *)margs + marg_adjustedOffset(method,offset) ) )

#define marg_getValue(margs, offset, type) \
	( *marg_getRef(margs, offset, type) )

#define marg_setValue(margs, offset, type, value) \
	( marg_getValue(margs, offset, type) = (value) )

#endif

#endif
