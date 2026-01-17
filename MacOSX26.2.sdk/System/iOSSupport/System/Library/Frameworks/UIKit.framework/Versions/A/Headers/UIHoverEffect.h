#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIHoverEffect.h>)
//
//  UIHoverEffect.h
//  UIKit
//
//  Copyright © 2023 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// A hover effect that can be applied to a `UIView` via a `UIHoverStyle`.
/// You don't conform to this protocol directly. Instead, you use a built-in
/// `UIHoverEffect` like `UIHoverAutomaticEffect`.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos)
NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@protocol UIHoverEffect <NSObject, NSCopying>
@end

/// An effect that applies a highlight to the view on hover.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos)
NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@interface UIHoverHighlightEffect : NSObject <UIHoverEffect>

+ (instancetype)effect;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// An effect that can visually lift the view on hover where appropriate.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos)
NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@interface UIHoverLiftEffect : NSObject <UIHoverEffect>

+ (instancetype)effect;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

/// A system-default hover effect that automatically selects the appropriate
/// effect based on the view to which it is applied.
UIKIT_EXTERN API_AVAILABLE(ios(17.0), visionos(1.0)) API_UNAVAILABLE(watchos, tvos)
NS_REFINED_FOR_SWIFT NS_SWIFT_UI_ACTOR
@interface UIHoverAutomaticEffect : NSObject <UIHoverEffect>

+ (instancetype)effect;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIHoverEffect.h>
#endif
