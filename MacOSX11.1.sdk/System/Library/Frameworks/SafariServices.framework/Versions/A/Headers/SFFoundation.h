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
#define SF_DEPRECATED_MAC_SAFARI(_safariIntroduced, _safariDeprecated, ...) SF_DEPRECATED_MAC_SAFARI_##_safariIntroduced##_##_safariDeprecated(__VA_ARGS__)

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000
#define SF_AVAILABLE_MAC_SAFARI_14_0 NS_AVAILABLE_MAC(11_0)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_14_0 NS_CLASS_AVAILABLE_MAC(11_0)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_14_0 NS_ENUM_AVAILABLE_MAC(11_0)
#else
#define SF_AVAILABLE_MAC_SAFARI_14_0 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_14_0 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_14_0
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500
#define SF_AVAILABLE_MAC_SAFARI_13_0 NS_AVAILABLE_MAC(10_15)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_13_0 NS_CLASS_AVAILABLE_MAC(10_15)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_13_0 NS_ENUM_AVAILABLE_MAC(10_15)
#else
#define SF_AVAILABLE_MAC_SAFARI_13_0 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_13_0 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_13_0
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101404
#define SF_AVAILABLE_MAC_SAFARI_12_1 NS_AVAILABLE_MAC(10_14_4)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_12_1 NS_CLASS_AVAILABLE_MAC(10_14_4)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_12_1 NS_ENUM_AVAILABLE_MAC(10_14_4)
#else
#define SF_AVAILABLE_MAC_SAFARI_12_1 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_12_1 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_12_1
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101400
#define SF_AVAILABLE_MAC_SAFARI_12_0 NS_AVAILABLE_MAC(10_14)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_12_0 NS_CLASS_AVAILABLE_MAC(10_14)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_12_0 NS_ENUM_AVAILABLE_MAC(10_14)
#else
#define SF_AVAILABLE_MAC_SAFARI_12_0 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_12_0 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_12_0
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101304
#define SF_AVAILABLE_MAC_SAFARI_11_1 NS_AVAILABLE_MAC(10_13_4)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_11_1 NS_CLASS_AVAILABLE_MAC(10_13_4)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_11_1 NS_ENUM_AVAILABLE_MAC(10_13_4)
#else
#define SF_AVAILABLE_MAC_SAFARI_11_1 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_11_1 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_11_1
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101300
#define SF_DEPRECATED_MAC_SAFARI_10_0_11_0(_message) NS_DEPRECATED_MAC(10_12, 10_13, _message)
#define SF_AVAILABLE_MAC_SAFARI_11_0 NS_AVAILABLE_MAC(10_13)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_11_0 NS_CLASS_AVAILABLE_MAC(10_13)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_11_0 NS_ENUM_AVAILABLE_MAC(10_13)
#else
#define SF_DEPRECATED_MAC_SAFARI_10_0_11_0(_message)
#define SF_AVAILABLE_MAC_SAFARI_11_0 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_11_0 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_11_0
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101204
#define SF_AVAILABLE_MAC_SAFARI_10_1 NS_AVAILABLE_MAC(10_12_4)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_10_1 NS_CLASS_AVAILABLE_MAC(10_12_4)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_10_1 NS_ENUM_AVAILABLE_MAC(10_12_4)
#else
#define SF_AVAILABLE_MAC_SAFARI_10_1 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_10_1 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_10_1
#endif

#if __MAC_OS_X_VERSION_MIN_REQUIRED >= 101200
#define SF_AVAILABLE_MAC_SAFARI_10_0 NS_AVAILABLE_MAC(10_12)
#define SF_CLASS_AVAILABLE_MAC_SAFARI_10_0 NS_CLASS_AVAILABLE_MAC(10_12)
#define SF_ENUM_AVAILABLE_MAC_SAFARI_10_0 NS_ENUM_AVAILABLE_MAC(10_12)
#else
#define SF_AVAILABLE_MAC_SAFARI_10_0 __attribute__((weak_import))
#define SF_CLASS_AVAILABLE_MAC_SAFARI_10_0 __attribute__((visibility("default"))) __attribute__((weak_import))
#define SF_ENUM_AVAILABLE_MAC_SAFARI_10_0
#endif
