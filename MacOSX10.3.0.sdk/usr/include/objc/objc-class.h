/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.1 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 *	objc-class.h
 *	Copyright 1988-1996, NeXT Software, Inc.
 */

#ifndef _OBJC_CLASS_H_
#define _OBJC_CLASS_H_

#import <objc/objc.h>
/* 
 *	Class Template
 */
struct objc_class {			
	struct objc_class *isa;	
	struct objc_class *super_class;	
	const char *name;		
	long version;
	long info;
	long instance_size;
	struct objc_ivar_list *ivars;

	struct objc_method_list **methodLists;

	struct objc_cache *cache;
 	struct objc_protocol_list *protocols;
};
#define CLS_GETINFO(cls,infomask)	((cls)->info & (infomask))
#define CLS_SETINFO(cls,infomask)	((cls)->info |= (infomask))

#define CLS_CLASS		0x1L
#define CLS_META		0x2L
#define CLS_INITIALIZED		0x4L
#define CLS_POSING		0x8L
#define CLS_MAPPED		0x10L
#define CLS_FLUSH_CACHE		0x20L
#define CLS_GROW_CACHE		0x40L
#define CLS_NEED_BIND		0x80L
#define CLS_METHOD_ARRAY        0x100L
// the JavaBridge constructs classes with these markers
#define CLS_JAVA_HYBRID		0x200L
#define CLS_JAVA_CLASS		0x400L
// thread-safe +initialize
#define CLS_INITIALIZING	0x800

/*
 * (true as of 2001-9-24)
 * Thread-safety note: changes to these flags are not atomic, so 
 * the only thing preventing lost updates is the timing of the changes.
 *
 * As long as the following are isolated from each other for any one class, 
 * nearly all flag updates will be safe:
 * - compile-time
 * - loading in one thread (not including +load) without messaging
 * - initializing in one thread with messaging from that thread only
 * - multi-threaded messaging with method caching
 *
 * The current code doesn't protect loading yet.
 *
 * Times when the flags may change:
 * CLS_CLASS: compile-time, hand-built classes
 * CLS_META: compile time, hand-built classes
 * CLS_INITIALIZED: initialize
 * CLS_POSING: unsafe, but posing has other thread-safety problems
 * CLS_MAPPED: compile-time
 * CLS_FLUSH_CACHE: messaging
 * CLS_GROW_CACHE: messaging
 *   FLUSH_CACHE and GROW_CACHE are protected from each other by the 
 *   cacheUpdateLock.
 * CLS_NEED_BIND: load, initialize
 * CLS_METHOD_ARRAY: load
 * CLS_JAVA_HYBRID: hand-built classes
 * CLS_JAVA_CLASS: hand-built classes, initialize
 * CLS_INITIALIZING: initialize
 *
 * The only unsafe updates are:
 * - posing (unsafe anyway)
 * - hand-built classes (including JavaBridge classes)
 *   There is a short time between objc_addClass inserts the new class 
 *   into the class_hash and the builder setting the right flags. 
 *   A thread looking at the class_hash could send a message to the class 
 *   and trigger initialization, and the changes to the initialization 
 *   flags and the hand-adjusted flags could collide. 
 *   Solution: don't do that. 
 */


/* 
 *	Category Template
 */
typedef struct objc_category *Category;

struct objc_category {
	char *category_name;
	char *class_name;
	struct objc_method_list *instance_methods;
	struct objc_method_list *class_methods;
 	struct objc_protocol_list *protocols;
};

/* 
 *	Instance Variable Template
 */
typedef struct objc_ivar *Ivar;

struct objc_ivar {
	char *ivar_name;
	char *ivar_type;
	int ivar_offset;
#ifdef __alpha__
	int space;
#endif
};

struct objc_ivar_list {
	int ivar_count;
#ifdef __alpha__
	int space;
#endif
	struct objc_ivar ivar_list[1];		/* variable length structure */
};

OBJC_EXPORT Ivar object_setInstanceVariable(id, const char *name, void *);
OBJC_EXPORT Ivar object_getInstanceVariable(id, const char *name, void **);

/* 
 *	Method Template
 */
typedef struct objc_method *Method;

struct objc_method {
	SEL method_name;
	char *method_types;
	IMP method_imp;
};

struct objc_method_list {
	struct objc_method_list *obsolete;

	int method_count;
#ifdef __alpha__
	int space;
#endif
	struct objc_method method_list[1];	/* variable length structure */
};

/* Protocol support */

@class Protocol;

struct objc_protocol_list {
	struct objc_protocol_list *next;
	int count;
	Protocol *list[1];
};

/* Definitions of filer types */

#define _C_ID		'@'
#define _C_CLASS	'#'
#define _C_SEL		':'
#define _C_CHR		'c'
#define _C_UCHR		'C'
#define _C_SHT		's'
#define _C_USHT		'S'
#define _C_INT		'i'
#define _C_UINT		'I'
#define _C_LNG		'l'
#define _C_ULNG		'L'
#define _C_FLT		'f'
#define _C_DBL		'd'
#define _C_BFLD		'b'
#define _C_VOID		'v'
#define _C_UNDEF	'?'
#define _C_PTR		'^'
#define _C_CHARPTR	'*'
#define _C_ARY_B	'['
#define _C_ARY_E	']'
#define _C_UNION_B	'('
#define _C_UNION_E	')'
#define _C_STRUCT_B	'{'
#define _C_STRUCT_E	'}'

/* Structure for method cache - allocated/sized at runtime */

typedef struct objc_cache *	Cache;

#define CACHE_BUCKET_NAME(B)  ((B)->method_name)
#define CACHE_BUCKET_IMP(B)   ((B)->method_imp)
#define CACHE_BUCKET_VALID(B) (B)
#define CACHE_HASH(sel, mask) (((uarith_t)(sel)>>2) & (mask))
struct objc_cache {
	unsigned int mask;            /* total = mask + 1 */
	unsigned int occupied;        
	Method buckets[1];
};

/* operations */
OBJC_EXPORT id class_createInstance(Class, unsigned idxIvars);
OBJC_EXPORT id class_createInstanceFromZone(Class, unsigned idxIvars, void *z);

OBJC_EXPORT void class_setVersion(Class, int);
OBJC_EXPORT int class_getVersion(Class);

OBJC_EXPORT Ivar class_getInstanceVariable(Class, const char *);
OBJC_EXPORT Method class_getInstanceMethod(Class, SEL);
OBJC_EXPORT Method class_getClassMethod(Class, SEL);

OBJC_EXPORT void class_addMethods(Class, struct objc_method_list *);
OBJC_EXPORT void class_removeMethods(Class, struct objc_method_list *);

OBJC_EXPORT Class class_poseAs(Class imposter, Class original);

OBJC_EXPORT unsigned method_getNumberOfArguments(Method);
OBJC_EXPORT unsigned method_getSizeOfArguments(Method);
OBJC_EXPORT unsigned method_getArgumentInfo(Method m, int arg, const char **type, int *offset);

// usage for nextMethodList
//
// void *iterator = 0;
// struct objc_method_list *mlist;
// while ( mlist = class_nextMethodList( cls, &iterator ) )
//    ;
#define OBJC_NEXT_METHOD_LIST 1
OBJC_EXPORT struct objc_method_list *class_nextMethodList(Class, void **);

typedef void *marg_list;

#if defined(__ppc__) || defined(ppc)
#define marg_prearg_size	128
#else
#define marg_prearg_size	0
#endif

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

/* Load categories and non-referenced classes from libraries. */

#endif /* _OBJC_CLASS_H_ */
