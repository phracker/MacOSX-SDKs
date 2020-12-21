/*
 * Copyright (c) 2012 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

#ifndef opendirectoryd_odobject_h
#define opendirectoryd_odobject_h

#include <os/object.h>
#include <os/object_private.h>

#ifndef __ptrauth_objc_isa_pointer
#define __ptrauth_objc_isa_pointer
#endif

#if OS_OBJECT_USE_OBJC
#define OD_DECL_INTERNAL_SUBCLASS(name, super) OS_OBJECT_DECL_SUBCLASS(name, super)
#define OD_DECL_INTERNAL(name) OD_DECL_INTERNAL_SUBCLASS(name, od_object))
#define OD_DECL_SUBCLASS_INTERFACE(name, super) _OS_OBJECT_DECL_SUBCLASS_INTERFACE(name, super)
#else // !OS_OBJECT_USE_OBJC
#define OD_DECL_INTERNAL_SUBCLASS(name, super) OD_DECL(name)
#define OD_DECL_INTERNAL(name) OD_DECL(name)
#define OD_DECL_SUBCLASS_INTERFACE(name, super)
#endif // OS_OBJECT_USE_OBJC

#define OD_CONCAT(x,y) OD_CONCAT1(x,y)
#define OD_CONCAT1(x,y) x ## y

#if __BUILDING_ODMODULE__ && OS_OBJECT_USE_OBJC
#define OD_CLASS(name) OS_OBJECT_CLASS(odx_##name)
#else // !__BUILDING_ODMODULE__ || !OS_OBJECT_USE_OBJC
#define OD_CLASS(name) OS_OBJECT_CLASS(od_##name)
#endif // !__BUILDING_ODMODULE__ || !OS_OBJECT_USE_OBJC

// ObjC classes and dispatch vtables are co-located via linker order and alias
// files rdar://10640168
#define OD_VTABLE_SUBCLASS_INSTANCE(name, super, ...) \
  __attribute__((section("__DATA,__objc_data"), used)) \
  static const struct { \
    _OS_OBJECT_CLASS_HEADER(); \
    OD_VTABLE_HEADER(super); \
  } OD_CONCAT(_,OD_CLASS(name##_vtable)) = { \
    __VA_ARGS__ \
}

#if __BUILDING_ODMODULE__
#define OD_SUBCLASS_DECL(name, super) \
  OD_DECL_SUBCLASS_INTERFACE(odx_##name, super) struct od_##name##_s; \
  extern const struct odx_##name##_vtable_s { \
    _OS_OBJECT_CLASS_HEADER(); \
    OD_VTABLE_HEADER(name); \
  } _odx_##name##_vtable

#define OD_CLASS_DECL(name) OD_SUBCLASS_DECL(name, odx_object)

#define ODINTERNAL_SUBCLASS_DECL(name, super) \
OD_DECL_INTERNAL_SUBCLASS(odx_##name, odx_##super); \
OD_DECL_SUBCLASS_INTERFACE(odx_##name, odx_##super) \
extern const struct odx_##super##_vtable_s _odx_##name##_vtable

#else // !__BUILDING_ODMODULE_
#define OD_SUBCLASS_DECL(name, super) \
  OD_DECL_SUBCLASS_INTERFACE(od_##name, super) struct od_##name##_s; \
  extern const struct od_##name##_vtable_s { \
    _OS_OBJECT_CLASS_HEADER(); \
    OD_VTABLE_HEADER(name); \
  } _od_##name##_vtable

#define OD_CLASS_DECL(name) OD_SUBCLASS_DECL(name, od_object)

#define ODINTERNAL_SUBCLASS_DECL(name, super) \
OD_DECL_INTERNAL_SUBCLASS(od_##name, od_##super); \
OD_DECL_SUBCLASS_INTERFACE(od_##name, od_##super) \
extern const struct od_##super##_vtable_s _od_##name##_vtable
#endif // !__BUILDING_ODMODULE_

#define OD_VTABLE_INSTANCE(name, ...) OD_VTABLE_SUBCLASS_INSTANCE(name, name, __VA_ARGS__)

#define OD_VTABLE(name) &_od_##name##_vtable

#define OD_VTABLE_HEADER(x) \
  unsigned long const odo_type; \
  const char *const odo_kind; \
  size_t (*const odo_debug)(struct od_##x##_s *, char *, size_t); \
  void (*const odo_dispose)(struct od_##x##_s *)

#define OD_STRUCT_HEADER(x) \
  _OS_OBJECT_HEADER( const struct od_##x##_vtable_s *__ptrauth_objc_isa_pointer odo_vtable, \
      odo_ref_cnt, odo_xref_cnt); \
  void *odo_finalizer;

#define OD_OBJECT_GLOBAL_REFCNT		_OS_OBJECT_GLOBAL_REFCNT

#if OS_OBJECT_USE_OBJC
/*
 * By default, OD objects are declared as Objective-C types when building
 * with an Objective-C compiler. This allows them to participate in ARC, in RR
 * management by the Blocks runtime and in leaks checking by the static
 * analyzer, and enables them to be added to Cocoa collections.
 * See <os/object.h> for details.
 */
#if __BUILDING_ODMODULE__ 
OS_OBJECT_DECL(odx_object);
#define OD_DECL(name) OS_OBJECT_DECL_SUBCLASS(name, odx_object)

#ifndef __od_object_t__
#define __od_object_t__ 1
typedef odx_object_t od_object_t;
#endif // __od_object_t__

#else // !__BUILDING_ODMODULE__
OS_OBJECT_DECL(od_object);
#define OD_DECL(name) OS_OBJECT_DECL_SUBCLASS(name, od_object)
#endif // !__BUILDING_ODMODULE__
#define OD_GLOBAL_OBJECT(type, object) ((OS_OBJECT_BRIDGE type)&(object))

#define OD_RETURNS_RETAINED OS_OBJECT_RETURNS_RETAINED

#if defined(__has_attribute) && __has_attribute(ns_returns_not_retained)
#define OD_RETURNS_NOT_RETAINED __attribute__((__ns_returns_not_retained__))
#endif

DISPATCH_INLINE DISPATCH_ALWAYS_INLINE DISPATCH_NONNULL_ALL DISPATCH_NOTHROW
void
_od_object_validate(od_object_t object) {
    void *isa = *(void* volatile*)(OS_OBJECT_BRIDGE void*)object;
    (void)isa;
}
#else // C

#ifndef __od_object_t__
#define __od_object_t__ 1

typedef union {
    struct _os_object_s         *_os_obj;
    struct od_object_s          *_object;
    struct od_attributemap_s    *_attributemap;
    struct od_connection_s      *_connection;
    struct od_context_s         *_context;
    struct od_credential_s      *_credential;
    struct od_mappings_s        *_mappings;
    struct od_module_s          *_module;
    struct od_moduleconfig_s    *_moduleconfig;
    struct od_node_s            *_node;
    struct od_nodeconfig_s      *_nodeconfig;
    struct od_pidinfo_s         *_pidinfo;
    struct od_recordmap_s       *_recordmap;
    struct od_request_s         *_request;
    struct od_requesttype_s     *_requesttype;
    struct od_response_s        *_response;
    struct od_session_s         *_session;
    struct od_trigger_s         *_trigger;
} od_object_t __attribute__((transparent_union));

#endif // __od_object_t__

/*! @parseOnly */
#define OD_DECL(name) typedef struct name##_s *name##_t
/*! @parseOnly */
#define OD_GLOBAL_OBJECT(t, x) (&(x))
/*! @parseOnly */
#undef OD_RETURNS_RETAINED
#define OD_RETURNS_RETAINED
#undef OD_RETURNS_NOT_RETAINED
#define OD_RETURNS_NOT_RETAINED

#endif // C

od_object_t _od_object_alloc(const void *vtable, size_t size);
void _od_object_dispose(od_object_t obj);
void _od_release(od_object_t obj);

#endif // opendirectoryd_odobject_h

