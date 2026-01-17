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

#ifndef _OBJC_RUNTIME_H
#define _OBJC_RUNTIME_H

#import <objc/objc.h>

#import <sys/types.h>
#import <stdarg.h>
#import <stdint.h>
#import <stddef.h>
#import <AvailabilityMacros.h>


/* Types */

typedef struct objc_method *Method;
typedef struct objc_ivar *Ivar;
typedef struct objc_category *Category;
typedef struct objc_property *objc_property_t;

struct objc_class {
    Class isa;

#if !__OBJC2__
    Class super_class                                        OBJC2_UNAVAILABLE;
    const char *name                                         OBJC2_UNAVAILABLE;
    long version                                             OBJC2_UNAVAILABLE;
    long info                                                OBJC2_UNAVAILABLE;
    long instance_size                                       OBJC2_UNAVAILABLE;
    struct objc_ivar_list *ivars                             OBJC2_UNAVAILABLE;
    struct objc_method_list **methodLists                    OBJC2_UNAVAILABLE;
    struct objc_cache *cache                                 OBJC2_UNAVAILABLE;
    struct objc_protocol_list *protocols                     OBJC2_UNAVAILABLE;
#endif

} OBJC2_UNAVAILABLE;
/* Use `Class` instead of `struct objc_class *` */

#ifdef __OBJC__
@class Protocol;
#else
typedef struct objc_object Protocol;
#endif

struct objc_method_description {
	SEL name;
	char *types;
};
struct objc_method_description_list {
        int count;
        struct objc_method_description list[1];
};

struct objc_protocol_list {
    struct objc_protocol_list *next;
    long count;
    Protocol *list[1];
};


/* Functions */

OBJC_EXPORT id object_copy(id obj, size_t size);
OBJC_EXPORT id object_dispose(id obj);

OBJC_EXPORT Class object_getClass(id obj) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Class object_setClass(id obj, Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char *object_getClassName(id obj);
OBJC_EXPORT void *object_getIndexedIvars(id obj);

OBJC_EXPORT id object_getIvar(id obj, Ivar ivar) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void object_setIvar(id obj, Ivar ivar, id value) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT Ivar object_setInstanceVariable(id obj, const char *name, void *value);
OBJC_EXPORT Ivar object_getInstanceVariable(id obj, const char *name, void **outValue);

OBJC_EXPORT id objc_getClass(const char *name);
OBJC_EXPORT id objc_getMetaClass(const char *name);
OBJC_EXPORT id objc_lookUpClass(const char *name);
OBJC_EXPORT id objc_getRequiredClass(const char *name);
OBJC_EXPORT Class objc_getFutureClass(const char *name) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void objc_setFutureClass(Class cls, const char *name) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT int objc_getClassList(Class *buffer, int bufferCount);

OBJC_EXPORT Protocol *objc_getProtocol(const char *name)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Protocol **objc_copyProtocolList(unsigned int *outCount)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char *class_getName(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT BOOL class_isMetaClass(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Class class_getSuperclass(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Class class_setSuperclass(Class cls, Class newSuper) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER OBJC2_UNAVAILABLE;

OBJC_EXPORT int class_getVersion(Class cls);
OBJC_EXPORT void class_setVersion(Class cls, int version);

OBJC_EXPORT size_t class_getInstanceSize(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT Ivar class_getInstanceVariable(Class cls, const char *name);
OBJC_EXPORT Ivar class_getClassVariable(Class cls, const char *name) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Ivar *class_copyIvarList(Class cls, unsigned int *outCount) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT Method class_getInstanceMethod(Class cls, SEL name);
OBJC_EXPORT Method class_getClassMethod(Class cls, SEL name);
OBJC_EXPORT IMP class_getMethodImplementation(Class cls, SEL name) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT IMP class_getMethodImplementation_stret(Class cls, SEL name) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT BOOL class_respondsToSelector(Class cls, SEL sel) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Method *class_copyMethodList(Class cls, unsigned int *outCount) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT BOOL class_conformsToProtocol(Class cls, Protocol *protocol) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Protocol **class_copyProtocolList(Class cls, unsigned int *outCount)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT objc_property_t class_getProperty(Class cls, const char *name)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT objc_property_t *class_copyPropertyList(Class cls, unsigned int *outCount)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char *class_getIvarLayout(Class cls)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char *class_getWeakIvarLayout(Class cls)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT id class_createInstance(Class cls, size_t extraBytes);

OBJC_EXPORT Class objc_allocateClassPair(Class superclass, const char *name, 
                                         size_t extraBytes) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void objc_registerClassPair(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Class objc_duplicateClass(Class original, const char *name, 
                                      size_t extraBytes) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void objc_disposeClassPair(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT BOOL class_addMethod(Class cls, SEL name, IMP imp, 
                                 const char *types) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT IMP class_replaceMethod(Class cls, SEL name, IMP imp, 
                                    const char *types) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT BOOL class_addIvar(Class cls, const char *name, size_t size, 
                               uint8_t alignment, const char *types) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT BOOL class_addProtocol(Class cls, Protocol *protocol) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void class_setIvarLayout(Class cls, const char *layout)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void class_setWeakIvarLayout(Class cls, const char *layout)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


OBJC_EXPORT SEL method_getName(Method m) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT IMP method_getImplementation(Method m) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char *method_getTypeEncoding(Method m) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT unsigned int method_getNumberOfArguments(Method m);
OBJC_EXPORT char *method_copyReturnType(Method m) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT char *method_copyArgumentType(Method m, unsigned int index) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void method_getReturnType(Method m, char *dst, size_t dst_len) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void method_getArgumentType(Method m, unsigned int index, 
                                        char *dst, size_t dst_len) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT struct objc_method_description *method_getDescription(Method m) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT IMP method_setImplementation(Method m, IMP imp) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void method_exchangeImplementations(Method m1, Method m2) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char *ivar_getName(Ivar v) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char *ivar_getTypeEncoding(Ivar v) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT ptrdiff_t ivar_getOffset(Ivar v) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char *property_getName(objc_property_t property) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char *property_getAttributes(objc_property_t property) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT BOOL protocol_conformsToProtocol(Protocol *proto, Protocol *other)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT BOOL protocol_isEqual(Protocol *proto, Protocol *other)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char *protocol_getName(Protocol *p)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT struct objc_method_description protocol_getMethodDescription(Protocol *p, SEL aSel, BOOL isRequiredMethod, BOOL isInstanceMethod)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT struct objc_method_description *protocol_copyMethodDescriptionList(Protocol *p, BOOL isRequiredMethod, BOOL isInstanceMethod, unsigned int *outCount)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT objc_property_t protocol_getProperty(Protocol *proto, const char *name, BOOL isRequiredProperty, BOOL isInstanceProperty)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT objc_property_t *protocol_copyPropertyList(Protocol *proto, unsigned int *outCount)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT Protocol **protocol_copyProtocolList(Protocol *proto, unsigned int *outCount)
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char **objc_copyImageNames(unsigned int *outCount) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char *class_getImageName(Class cls) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT const char **objc_copyClassNamesForImage(const char *image, 
                                                     unsigned int *outCount) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT const char *sel_getName(SEL sel);
OBJC_EXPORT SEL sel_getUid(const char *str);
OBJC_EXPORT SEL sel_registerName(const char *str);
OBJC_EXPORT BOOL sel_isEqual(SEL lhs, SEL rhs) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT void objc_enumerationMutation(id) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
OBJC_EXPORT void objc_setEnumerationMutationHandler(void (*handler)(id)) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

OBJC_EXPORT void objc_setForwardHandler(void *fwd, void *fwd_stret) 
     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#define _C_ID       '@'
#define _C_CLASS    '#'
#define _C_SEL      ':'
#define _C_CHR      'c'
#define _C_UCHR     'C'
#define _C_SHT      's'
#define _C_USHT     'S'
#define _C_INT      'i'
#define _C_UINT     'I'
#define _C_LNG      'l'
#define _C_ULNG     'L'
#define _C_LNG_LNG  'q'
#define _C_ULNG_LNG 'Q'
#define _C_FLT      'f'
#define _C_DBL      'd'
#define _C_BFLD     'b'
#define _C_BOOL     'B'
#define _C_VOID     'v'
#define _C_UNDEF    '?'
#define _C_PTR      '^'
#define _C_CHARPTR  '*'
#define _C_ATOM     '%'
#define _C_ARY_B    '['
#define _C_ARY_E    ']'
#define _C_UNION_B  '('
#define _C_UNION_E  ')'
#define _C_STRUCT_B '{'
#define _C_STRUCT_E '}'
#define _C_VECTOR   '!'
#define _C_CONST    'r'


/* Obsolete types */

#if !__OBJC2__

#define CLS_GETINFO(cls,infomask)        ((cls)->info & (infomask))
#define CLS_SETINFO(cls,infomask)        ((cls)->info |= (infomask))

// class is not a metaclass
#define CLS_CLASS               0x1
// class is a metaclass
#define CLS_META                0x2
// class's +initialize method has completed
#define CLS_INITIALIZED         0x4
// class is posing
#define CLS_POSING              0x8
// unused
#define CLS_MAPPED              0x10
// class and subclasses need cache flush during image loading
#define CLS_FLUSH_CACHE         0x20
// method cache should grow when full
#define CLS_GROW_CACHE          0x40
// unused
#define CLS_NEED_BIND           0x80
// methodLists is array of method lists
#define CLS_METHOD_ARRAY        0x100
// the JavaBridge constructs classes with these markers
#define CLS_JAVA_HYBRID         0x200
#define CLS_JAVA_CLASS          0x400
// thread-safe +initialize
#define CLS_INITIALIZING        0x800
// bundle unloading
#define CLS_FROM_BUNDLE         0x1000
// C++ ivar support
#define CLS_HAS_CXX_STRUCTORS   0x2000
// Lazy method list arrays
#define CLS_NO_METHOD_ARRAY     0x4000
// +load implementation
#define CLS_HAS_LOAD_METHOD     0x8000
// objc_allocateClassPair API
#define CLS_CONSTRUCTING        0x10000
// class compiled with bigger class structure
#define CLS_EXT                 0x20000


struct objc_category {
    char *category_name                                      OBJC2_UNAVAILABLE;
    char *class_name                                         OBJC2_UNAVAILABLE;
    struct objc_method_list *instance_methods                OBJC2_UNAVAILABLE;
    struct objc_method_list *class_methods                   OBJC2_UNAVAILABLE;
    struct objc_protocol_list *protocols                     OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


struct objc_ivar {
    char *ivar_name                                          OBJC2_UNAVAILABLE;
    char *ivar_type                                          OBJC2_UNAVAILABLE;
    int ivar_offset                                          OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
}                                                            OBJC2_UNAVAILABLE;

struct objc_ivar_list {
    int ivar_count                                           OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
    /* variable length structure */
    struct objc_ivar ivar_list[1]                            OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


struct objc_method {
    SEL method_name                                          OBJC2_UNAVAILABLE;
    char *method_types                                       OBJC2_UNAVAILABLE;
    IMP method_imp                                           OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;

struct objc_method_list {
    struct objc_method_list *obsolete                        OBJC2_UNAVAILABLE;

    int method_count                                         OBJC2_UNAVAILABLE;
#ifdef __LP64__
    int space                                                OBJC2_UNAVAILABLE;
#endif
    /* variable length structure */
    struct objc_method method_list[1]                        OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


typedef struct objc_symtab *Symtab                           OBJC2_UNAVAILABLE;

struct objc_symtab {
    unsigned long sel_ref_cnt                                OBJC2_UNAVAILABLE;
    SEL *refs                                                OBJC2_UNAVAILABLE;
    unsigned short cls_def_cnt                               OBJC2_UNAVAILABLE;
    unsigned short cat_def_cnt                               OBJC2_UNAVAILABLE;
    void *defs[1] /* variable size */                        OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;


typedef struct objc_cache *Cache                             OBJC2_UNAVAILABLE;

#define CACHE_BUCKET_NAME(B)  ((B)->method_name)
#define CACHE_BUCKET_IMP(B)   ((B)->method_imp)
#define CACHE_BUCKET_VALID(B) (B)
#ifndef __LP64__
#define CACHE_HASH(sel, mask) (((uintptr_t)(sel)>>2) & (mask))
#else
#define CACHE_HASH(sel, mask) (((unsigned int)((uintptr_t)(sel)>>3)) & (mask))
#endif
struct objc_cache {
    unsigned int mask /* total = mask + 1 */                 OBJC2_UNAVAILABLE;
    unsigned int occupied                                    OBJC2_UNAVAILABLE;
    Method buckets[1]                                        OBJC2_UNAVAILABLE;
} /* GrP fixme should be OBJC2_UNAVAILABLE, but isn't because of spurious warnings in [super ...] calls */;


typedef struct objc_module *Module                           OBJC2_UNAVAILABLE;

struct objc_module {
    unsigned long version                                    OBJC2_UNAVAILABLE;
    unsigned long size                                       OBJC2_UNAVAILABLE;
    const char *name                                         OBJC2_UNAVAILABLE;
    Symtab symtab                                            OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;

#else

struct objc_method_list;

#endif


/* Obsolete functions */

OBJC_EXPORT BOOL sel_isMapped(SEL sel)                       OBJC2_UNAVAILABLE;

OBJC_EXPORT id object_copyFromZone(id anObject, size_t nBytes, void *z) OBJC2_UNAVAILABLE;
OBJC_EXPORT id object_realloc(id anObject, size_t nBytes)    OBJC2_UNAVAILABLE;
OBJC_EXPORT id object_reallocFromZone(id anObject, size_t nBytes, void *z) OBJC2_UNAVAILABLE;

#define OBSOLETE_OBJC_GETCLASSES 1
OBJC_EXPORT void *objc_getClasses(void)                      OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_addClass(Class myClass)                OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_setClassHandler(int (*)(const char *)) OBJC2_UNAVAILABLE;
OBJC_EXPORT void objc_setMultithreaded (BOOL flag)           OBJC2_UNAVAILABLE;

OBJC_EXPORT id class_createInstanceFromZone(Class, size_t idxIvars, void *z) OBJC2_UNAVAILABLE;

OBJC_EXPORT void class_addMethods(Class, struct objc_method_list *) OBJC2_UNAVAILABLE;
OBJC_EXPORT void class_removeMethods(Class, struct objc_method_list *) OBJC2_UNAVAILABLE;

OBJC_EXPORT Class class_poseAs(Class imposter, Class original) OBJC2_UNAVAILABLE;

OBJC_EXPORT unsigned int method_getSizeOfArguments(Method m) OBJC2_UNAVAILABLE;
OBJC_EXPORT unsigned method_getArgumentInfo(struct objc_method *m, int arg, const char **type, int *offset) OBJC2_UNAVAILABLE;

OBJC_EXPORT BOOL class_respondsToMethod(Class, SEL)          OBJC2_UNAVAILABLE;
OBJC_EXPORT IMP class_lookupMethod(Class, SEL)               OBJC2_UNAVAILABLE;
OBJC_EXPORT Class objc_getOrigClass(const char *name)        OBJC2_UNAVAILABLE;
#define OBJC_NEXT_METHOD_LIST 1
OBJC_EXPORT struct objc_method_list *class_nextMethodList(Class, void **) OBJC2_UNAVAILABLE;
// usage for nextMethodList
//
// void *iterator = 0;
// struct objc_method_list *mlist;
// while ( mlist = class_nextMethodList( cls, &iterator ) )
//    ;

OBJC_EXPORT id (*_alloc)(Class, size_t)                      OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_copy)(id, size_t)                          OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_realloc)(id, size_t)                       OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_dealloc)(id)                               OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_zoneAlloc)(Class, size_t, void *)          OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_zoneRealloc)(id, size_t, void *)           OBJC2_UNAVAILABLE;
OBJC_EXPORT id (*_zoneCopy)(id, size_t, void *)              OBJC2_UNAVAILABLE;
OBJC_EXPORT void (*_error)(id, const char *, va_list)        OBJC2_UNAVAILABLE;

#endif
