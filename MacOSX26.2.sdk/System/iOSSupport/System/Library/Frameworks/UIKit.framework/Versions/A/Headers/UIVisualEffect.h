#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIVisualEffect.h>)
//
//  UIVisualEffect.h
//  UIKit
//
//  Copyright © 2016-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIVisualEffect : NSObject <NSCopying, NSSecureCoding>

@end

@class UIColor;

/// A visual effect that applies a solid color background.
UIKIT_EXTERN API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UIColorEffect : UIVisualEffect

/// Creates a color effect with the specified color.
/// @param color The color to use for the background.
+ (instancetype)effectWithColor:(nullable UIColor *)color API_AVAILABLE(ios(26.1)) API_UNAVAILABLE(watchos);

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIVisualEffect.h>
#endif
