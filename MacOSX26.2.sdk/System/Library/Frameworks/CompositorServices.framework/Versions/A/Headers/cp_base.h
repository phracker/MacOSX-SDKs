//
//  cp_base.h
//  CompositorServices
//
//  Copyright © 2023 Apple. All rights reserved.
//

#ifndef cp_base_h
#define cp_base_h

#ifdef __cplusplus
    #define CP_EXTERN extern "C"
#else
    #define CP_EXTERN extern
#endif

#ifdef __cplusplus
    #define CP_EXTERN_C_BEGIN extern "C" {
    #define CP_EXTERN_C_END   }
#else
    #define CP_EXTERN_C_BEGIN
    #define CP_EXTERN_C_END
#endif

#ifdef __cplusplus
    #define CP_NONNULL_EXTERN_C_BEGIN CF_ASSUME_NONNULL_BEGIN extern "C" {
    #define CP_NONNULL_EXTERN_C_END   } CF_ASSUME_NONNULL_END
#else
    #define CP_NONNULL_EXTERN_C_BEGIN CF_ASSUME_NONNULL_BEGIN
    #define CP_NONNULL_EXTERN_C_END CF_ASSUME_NONNULL_END
#endif

#if __has_attribute(objc_subclassing_restricted)
    #define CP_FINAL_CLASS __attribute__((objc_subclassing_restricted))
#else
    #define CP_FINAL_CLASS
#endif

#define CP_EXPORT __attribute__((visibility("default")))

#define CP_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))

/// CP_STRUCT_REF
#define CP_STRUCT_REF_BASE(object, api_availability) \
    typedef struct object *object ## _t api_availability

#define CP_STRUCT_REF_2(object, api_availability, ...) \
    CP_STRUCT_REF_BASE(object, api_availability)
#define CP_STRUCT_REF_1(object, ...) \
    CP_STRUCT_REF_BASE(object, )

#ifdef __swift__
    #define CP_STRUCT_REF_BASE_SWIFT_COMPATIBLE(object, swift_define, api_availability) \
        typedef struct object ## _t { struct object _Nullable *opaque_pointer CF_REFINED_FOR_SWIFT; } swift_define api_availability object ## _t
    #define CP_STRUCT_REF_3(object, swift_name, api_availability) \
        CP_STRUCT_REF_BASE_SWIFT_COMPATIBLE(object, CF_SWIFT_NAME(swift_name), api_availability)
    #define CP_NULLABLE_STRUCT_REF
#else
    #define CP_STRUCT_REF_3(object, swift_name, api_availability) \
        CP_STRUCT_REF_BASE(object, api_availability)
    #define CP_NULLABLE_STRUCT_REF _Nullable
#endif

#define CP_STRUCT_REF_(object, swift_name_or_api_availability, api_availability, n, ...) \
    CP_STRUCT_REF_##n(object, swift_name_or_api_availability, api_availability)

#define CP_STRUCT_REF(object, ...) CP_STRUCT_REF_(object, ##__VA_ARGS__, 3, 2, 1)

/// CP_OBJECT_DECL
#ifdef __OBJC__
    #define CP_OBJECT_NAME(object) CP_OBJECT_ ## object
    #define CP_OBJECT_DECL_BASE(object, swift_define, api_availability) \
        CP_EXPORT\
        swift_define\
        api_availability\
        CP_FINAL_CLASS\
        @interface CP_OBJECT_NAME(object): NSObject \
        - (instancetype)init NS_UNAVAILABLE; \
        + (instancetype)new NS_UNAVAILABLE; \
        @end \
        typedef CP_OBJECT_NAME(object) *object ## _t CF_REFINED_FOR_SWIFT api_availability

#else
    #define CP_OBJECT_DECL_BASE(object, swift_define, api_availability) \
        typedef struct object ## _s  *object ## _t api_availability
#endif

#define CP_OBJECT_DECL_3(object, swift_name, api_availability) \
    CP_OBJECT_DECL_BASE(object, CF_SWIFT_NAME(swift_name), api_availability)
#define CP_OBJECT_DECL_2(object, api_availability, ...) \
    CP_OBJECT_DECL_BASE(object, CF_REFINED_FOR_SWIFT, api_availability)
#define CP_OBJECT_DECL_1(object, ...) \
    CP_OBJECT_DECL_BASE(object, CF_REFINED_FOR_SWIFT, )

#define CP_OBJECT_DECL_(object, swift_name_or_api_availability, api_availability, n, ...)\
    CP_OBJECT_DECL_##n(object, swift_name_or_api_availability, api_availability)

#define CP_OBJECT_DECL(object, ...)\
    CP_OBJECT_DECL_(object, ##__VA_ARGS__, 3, 2, 1)

#if !OS_OBJECT_USE_OBJC_RETAIN_RELEASE
CP_EXTERN_C_BEGIN

///Increments the reference count of the specified object.
///
///- Parameters:
///   - obj: The object to retain. If this parameter is an Objective-C object,
///   the function is equivalent to calling the `retain` method of that object.
/// - Returns: The retained object.
///
/// Don’t call this function in Swift code or on types you manage using
/// automatic reference counting (ARC).
void *cp_retain(void *obj)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macosx(26.0));

/// Decrement the reference count of the specified object.
///
/// - Parameters:
///   - obj: The object to release. If this parameter is an Objective-C object,
///   the function is equivalent to calling the `release` method of that object.
///
/// Don’t call this function in Swift code or on types you manage using
/// automatic reference counting (ARC).
void cp_release(void *obj)
CF_REFINED_FOR_SWIFT
API_AVAILABLE(visionos(1.0), macosx(26.0));

CP_EXTERN_C_END
#else // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE
#undef cp_retain
#undef cp_release
#define cp_retain(object) [(object) retain]
#define cp_release(object) [(object) release]
#endif // !OS_OBJECT_USE_OBJC_RETAIN_RELEASE

#endif /* cp_base_h */
