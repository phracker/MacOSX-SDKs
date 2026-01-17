//
//  CKDefines.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

#ifndef CK_EXTERN
#ifdef __cplusplus
#define CK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define CK_EXTERN   extern __attribute__((visibility ("default")))
#endif
#endif

#ifndef CK_HIDDEN
#define CK_HIDDEN   __attribute__((visibility("hidden")))
#endif

#ifndef CK_EXTERN_HIDDEN
#ifdef __cplusplus
#define CK_EXTERN_HIDDEN   extern "C" __attribute__((visibility ("hidden")))
#else
#define CK_EXTERN_HIDDEN   extern __attribute__((visibility ("hidden")))
#endif
#endif

#ifndef CK_SWIFT_AVAILABILITY
    #if defined(__swift__) && !defined(CK_BUILDING_CK)
        #define CK_SWIFT_AVAILABILITY(...) API_AVAILABLE(__VA_ARGS__)
        #define CK_SWIFT_DEPRECATED(...) API_DEPRECATED(__VA_ARGS__)
    #else
        #define CK_SWIFT_AVAILABILITY(...)
        #define CK_SWIFT_DEPRECATED(...)
    #endif
#endif

#ifndef CK_SUBCLASSING_RESTRICTED
    #define CK_SUBCLASSING_RESTRICTED __attribute__((__objc_subclassing_restricted__))
#endif

#ifndef CK_SUBCLASSING_EXTERNALLY_RESTRICTED
    #if defined(CK_BUILDING_CK)
        #define CK_SUBCLASSING_EXTERNALLY_RESTRICTED
    #else
        #define CK_SUBCLASSING_EXTERNALLY_RESTRICTED __attribute__((__objc_subclassing_restricted__))
    #endif
#endif


#ifndef CK_SUBCLASSING_DEPRECATED
    #define CK_SUBCLASSING_DEPRECATED // we can't actually emit a warning, but heed this annotation anyway!
#endif // CK_SUBCLASSING_DEPRECATED


#ifndef CK_UNAVAILABLE
    #define CK_UNAVAILABLE(msg) __attribute__((unavailable(msg)))
#endif

#ifndef CK_NEWLY_UNAVAILABLE
    #if (!defined(CK_BUILDING_CK) || !CK_BUILDING_CK)
        #define CK_NEWLY_UNAVAILABLE(msg) __attribute__((unavailable(msg)))
    #else
        #define CK_NEWLY_UNAVAILABLE(msg) CK_EXTERN
    #endif
#endif


NS_HEADER_AUDIT_END(nullability, sendability)
