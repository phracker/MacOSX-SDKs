#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UISceneDefinitions.h>)
//
//  UISceneDefinitions.h
//  UIKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

typedef NS_ENUM(NSInteger, UISceneActivationState) {
    UISceneActivationStateUnattached = -1,
    UISceneActivationStateForegroundActive,
    UISceneActivationStateForegroundInactive,
    UISceneActivationStateBackground
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

typedef NS_ENUM(NSInteger, UISceneCaptureState) {
    UISceneCaptureStateUnspecified = -1,
    UISceneCaptureStateInactive = 0,
    UISceneCaptureStateActive = 1
} API_AVAILABLE(ios(17.0), tvos(17.0), visionos(1.0)) API_UNAVAILABLE(watchos);

#pragma mark - UISceneSessionRole
typedef NSString * UISceneSessionRole NS_TYPED_ENUM API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

#pragma mark - NSErrorDomain
UIKIT_EXTERN NSErrorDomain const UISceneErrorDomain API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos);
typedef NS_ERROR_ENUM(UISceneErrorDomain, UISceneErrorCode) {
    UISceneErrorCodeMultipleScenesNotSupported,
    UISceneErrorCodeRequestDenied,
    
    // UIWindowSceneGeometryRequest error codes
    UISceneErrorCodeGeometryRequestUnsupported API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos) = 100,
    UISceneErrorCodeGeometryRequestDenied API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos)
} API_AVAILABLE(ios(13.0)) API_UNAVAILABLE(watchos);

#else
#import <UIKitCore/UISceneDefinitions.h>
#endif
