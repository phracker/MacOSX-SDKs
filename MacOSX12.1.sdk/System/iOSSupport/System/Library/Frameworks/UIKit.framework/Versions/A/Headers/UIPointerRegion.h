#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPointerRegion.h>)
//
//  UIPointerRegion.h
//  UIKit
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIGeometry.h>

NS_ASSUME_NONNULL_BEGIN

UIKIT_EXTERN API_AVAILABLE(ios(13.4)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPointerRegion : NSObject <NSCopying>

@property (nonatomic, readonly) CGRect rect;
@property (nonatomic, readonly, nullable) id<NSObject> identifier NS_REFINED_FOR_SWIFT;

/// Axes along which this region latches when the primary mouse button is pressed.
/// When set, the UIPointerStyle associated with this region will "lock in" and allow free-form movement along the specified axes.
@property (nonatomic) UIAxis latchingAxes;

/*!
 * @abstract Creates a UIPointerRegion with the supplied rect and optional identifier.
 *
 * @param rect        This region's rect. Must be in the pointer interaction's view's coordinate space.
 * @param identifier  Optional identifier that may be used to identify this region in subsequent pointer interaction delegate calls.
*/
+ (instancetype)regionWithRect:(CGRect)rect identifier:(nullable id<NSObject>)identifier NS_REFINED_FOR_SWIFT;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPointerRegion.h>
#endif
