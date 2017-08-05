//
//  SFFoundation.h
//  SafariServices
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Availability.h>

#ifdef __cplusplus
#define SF_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define SF_EXTERN extern __attribute__((visibility ("default")))
#endif

#define SF_AVAILABLE_MAC_SAFARI(_safari) SF_AVAILABLE_MAC_SAFARI_##_safari
#define SF_CLASS_AVAILABLE_MAC_SAFARI(_safari) SF_CLASS_AVAILABLE_MAC_SAFARI_##_safari
#define SF_ENUM_AVAILABLE_MAC_SAFARI(_safari) SF_ENUM_AVAILABLE_MAC_SAFARI_##_safari

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200
#define SF_AVAILABLE_MAC_SAFARI_10_0 NS_AVAILABLE_MAC(10_12)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_10_0 NS_CLASS_AVAILABLE_MAC(10_12)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_10_0 NS_ENUM_AVAILABLE_MAC(10_12)
#else
#define SF_AVAILABLE_MAC_SAFARI_10_0 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_10_0 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_10_0
#endif
