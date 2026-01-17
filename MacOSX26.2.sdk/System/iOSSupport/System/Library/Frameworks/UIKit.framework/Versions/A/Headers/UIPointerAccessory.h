#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPointerAccessory.h>)
//
//  UIPointerAccessory.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <CoreGraphics/CoreGraphics.h>

@class UIPointerShape;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

typedef struct NS_SWIFT_SENDABLE API_UNAVAILABLE(watchos) {
    /// Offset from the primary pointer shape. Only allows positive values.
    CGFloat offset;
    
    /// Clock-wise angle from top in radians.
    CGFloat angle;
} UIPointerAccessoryPosition API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;

UIKIT_STATIC_INLINE UIPointerAccessoryPosition UIPointerAccessoryPositionMake(CGFloat offset, CGFloat angle) API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) {
    UIPointerAccessoryPosition position = { offset, angle };
    return position;
}

UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionTop            API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionTopRight       API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionRight          API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionBottomRight    API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionBottom         API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionBottomLeft     API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionLeft           API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;
UIKIT_EXTERN const UIPointerAccessoryPosition UIPointerAccessoryPositionTopLeft        API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_REFINED_FOR_SWIFT;


UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPointerAccessory : NSObject <NSCopying>

/// This accessory's shape.
@property (nonatomic, copy, readonly) UIPointerShape *shape;

/// This accessory shape's position relative to the pointer.
@property (nonatomic, readonly) UIPointerAccessoryPosition position;

/// Indicates whether the accessory is rotated to match its angle.
/// This is false by default for custom accessories, but varies for system vended ones.
@property (nonatomic) BOOL orientationMatchesAngle;

/*!
 * @abstract Creates an accessory with the given pointer shape and position.
 *
 * @param shape     The desired accessory shape.
 * @param position  The desired accessory position.
 */
+ (instancetype)accessoryWithShape:(UIPointerShape *)shape position:(UIPointerAccessoryPosition)position;

/// Returns an arrow shaped accessory with the given position.
+ (instancetype)arrowAccessoryWithPosition:(UIPointerAccessoryPosition)position;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPointerAccessory.h>
#endif
