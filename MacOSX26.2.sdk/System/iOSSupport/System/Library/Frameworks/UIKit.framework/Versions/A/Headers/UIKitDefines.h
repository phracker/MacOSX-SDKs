#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIKitDefines.h>)
//
//  UIKitDefines.h
//  UIKit
//
//  Copyright (c) 2007-2018 Apple Inc. All rights reserved.
//

#import <Availability.h>
#import <UIUtilities/UIDefines.h>

#define UIKIT_AVAILABLE_IOS_ONLY(vers)      __IOS_AVAILABLE(vers) __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE
#define UIKIT_AVAILABLE_WATCHOS_ONLY(vers)  __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(vers) __TVOS_UNAVAILABLE
#define UIKIT_AVAILABLE_TVOS_ONLY(vers)     __IOS_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_AVAILABLE(vers)
#define UIKIT_AVAILABLE_IOS_TVOS(_ios, _tvos) __IOS_AVAILABLE(_ios) __WATCHOS_UNAVAILABLE __TVOS_AVAILABLE(_tvos)
#define UIKIT_AVAILABLE_IOS_WATCHOS_TVOS(_ios, _watchos, _tvos) __IOS_AVAILABLE(_ios) __WATCHOS_AVAILABLE(_watchos) __TVOS_AVAILABLE(_tvos)

#define UIKIT_CLASS_AVAILABLE_IOS_ONLY(vers) UIKIT_EXTERN __IOS_AVAILABLE(vers) __WATCHOS_UNAVAILABLE __TVOS_UNAVAILABLE
#define UIKIT_CLASS_AVAILABLE_WATCHOS_ONLY(vers) UIKIT_EXTERN __IOS_UNAVAILABLE __WATCHOS_AVAILABLE(vers) __TVOS_UNAVAILABLE
#define UIKIT_CLASS_AVAILABLE_TVOS_ONLY(vers) UIKIT_EXTERN __IOS_UNAVAILABLE __WATCHOS_UNAVAILABLE __TVOS_AVAILABLE(vers)
#define UIKIT_CLASS_AVAILABLE_IOS_TVOS(_ios, _tvos) UIKIT_EXTERN __IOS_AVAILABLE(_ios) __WATCHOS_UNAVAILABLE __TVOS_AVAILABLE(_tvos)
#define UIKIT_CLASS_AVAILABLE_IOS_WATCHOS_TVOS(_ios, _watchos, _tvos) UIKIT_EXTERN __IOS_AVAILABLE(_ios) __WATCHOS_AVAILABLE(_watchos) __TVOS_AVAILABLE(_tvos)

#if __swift__
#define UIKIT_SWIFT_FORWARD_DECLARE(DECLARATION) DECLARATION;
#else
#define UIKIT_SWIFT_FORWARD_DECLARE(DECLARATION)
#endif

#if !defined(UIKIT_HAS_UIFOUNDATION_SYMBOLS)
    #if defined(UIKIT_BUILDING_UIKITMACHELPER) || __has_feature(modules)
        #define UIKIT_HAS_UIFOUNDATION_SYMBOLS TARGET_OS_IPHONE
    #else
        #define UIKIT_HAS_UIFOUNDATION_SYMBOLS 1
    #endif // defined(UIKIT_BUILDING_UIKITMACHELPER)
#endif // !defined(UIKIT_HAS_UIFOUNDATION_SYMBOLS)

#ifndef UIKIT_FINAL
    #if defined(__has_attribute) && __has_attribute(objc_subclassing_restricted)
        #define UIKIT_FINAL __attribute__((objc_subclassing_restricted))
    #else
        #define UIKIT_FINAL
    #endif
#endif

#else
#import <UIKitCore/UIKitDefines.h>
#endif
