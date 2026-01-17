#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIFocusMovementHint.h>)
//
//  UIFocusMovementHint.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIFocus.h>
#import <UIKit/UIKitDefines.h>
#import <QuartzCore/CATransform3D.h>

/// Provides information about the current state of hinting for the focused item.
UIKIT_EXTERN API_AVAILABLE(ios(12.0)) @interface UIFocusMovementHint: NSObject <NSCopying>

/// Value between {-1.0, -1.0} and {1.0, 1.0} representing how close focus is to moving in a particular direction.
@property (nonatomic, readonly) CGVector movementDirection;

/// A 3D transform representing the perspective matrix that should be applied to match the system interaction hinting. Assumes a 0..1 near/far plane.
@property (nonatomic, readonly) CATransform3D perspectiveTransform;

/// A vector representing the X and Y axis rotation expressed in radians that should be applied to match the system interaction hinting.
@property (nonatomic, readonly) CGVector rotation;

/// A vector representing the X and Y axis translation expressed in points that should be applied to match the system interaction hinting.
@property (nonatomic, readonly) CGVector translation;

/// A 3D transform that contains the combined transformations of perspective, rotation and translation.
@property (nonatomic, readonly) CATransform3D interactionTransform;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

#else
#import <UIKitCore/UIFocusMovementHint.h>
#endif
