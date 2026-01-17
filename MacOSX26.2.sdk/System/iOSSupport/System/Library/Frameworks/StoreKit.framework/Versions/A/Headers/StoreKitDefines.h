//
//  StoreKitDefines.h
//  StoreKit
//
//  Copyright 2009 Apple, Inc. All rights reserved.
//

#ifdef __cplusplus
#define SK_EXTERN   extern "C" __attribute__((visibility ("default")))
#else
#define SK_EXTERN   extern __attribute__((visibility ("default")))
#endif

#define	SK_EXTERN_CLASS	__attribute__((visibility("default")))
#define SK_EXTERN_CLASS_AVAILABLE(_mac, _ios) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE(_mac, _ios)
#define SK_EXTERN_CLASS_AVAILABLE_MAC(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE_MAC(version)
#define SK_EXTERN_CLASS_AVAILABLE_IOS(version) __attribute__((visibility("default"))) NS_CLASS_AVAILABLE_IOS(version)
#define SK_CLASS_FINAL __attribute__((objc_subclassing_restricted))

#ifdef DEBUG
// Allow for the framework to be deployed in alternate locations.
#define StoreKitBundle [NSBundle bundleWithIdentifier:@"com.apple.StoreKit"]
#else
// Slightly more direct way to retrieve bundle.
#define StoreKitBundle [NSBundle bundleWithPath:@"/System/Library/Frameworks/StoreKit.framework"]
#endif

#define SKLocalizedString(x) NSLocalizedStringFromTableInBundle(x, nil, StoreKitBundle, @"")
