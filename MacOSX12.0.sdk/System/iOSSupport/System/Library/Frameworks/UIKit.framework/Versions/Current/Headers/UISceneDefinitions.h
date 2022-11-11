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
} API_AVAILABLE(ios(13.0));

#pragma mark - UISceneSessionRole
typedef NSString * UISceneSessionRole NS_TYPED_ENUM API_AVAILABLE(ios(13.0));

#pragma mark - NSErrorDomain
UIKIT_EXTERN NSErrorDomain const UISceneErrorDomain API_AVAILABLE(ios(15.0));
typedef NS_ERROR_ENUM(UISceneErrorDomain, UISceneErrorCode) {
    UISceneErrorCodeMultipleScenesNotSupported,
    UISceneErrorCodeRequestDenied
} API_AVAILABLE(ios(13.0));

#else
#import <UIKitCore/UISceneDefinitions.h>
#endif
