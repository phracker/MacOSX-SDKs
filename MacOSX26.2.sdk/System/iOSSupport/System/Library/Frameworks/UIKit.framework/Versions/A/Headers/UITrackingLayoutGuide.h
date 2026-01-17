#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UITrackingLayoutGuide.h>)
//
//  UITrackingLayoutGuide.h
//  UIKit
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIGeometry.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UILayoutGuide.h>

@class NSLayoutConstraint, UILayoutGuide;

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

UIKIT_EXTERN API_AVAILABLE(ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos) NS_SWIFT_UI_ACTOR
@interface UITrackingLayoutGuide : UILayoutGuide

/// Set up constraints to be activated and deactivated depending on which edge the guide is close to. Different tracking guides may respond to different edges, and if a guide never gets to an edge, those constraints will not be activated automatically.

/// @param trackingConstraints Constraints to activate when the guide is close to the specified edge, and deactivate when it moves away. Sending nil will deactivate any currently active constraints associated with this edge and remove them from tracking.
/// @param edge When the tracking layout guide is close to this edge, specified constraints will change

- (void)setConstraints:(NSArray <NSLayoutConstraint *>*)trackingConstraints
    activeWhenNearEdge:(NSDirectionalRectEdge)edge NS_SWIFT_NAME(setConstraints(_:activeWhenNearEdge:));
- (NSArray <NSLayoutConstraint *>*)constraintsActiveWhenNearEdge:(NSDirectionalRectEdge)edge NS_SWIFT_NAME(constraints(activeWhenNearEdge:));

/// @param trackingConstraints Constraints to deactivate when the guide is close to the specified edge, and activate when it moves away. Sending nil will remove the constraints associated with this edge from tracking.
/// @param edge When the tracking layout guide is close to this edge, specified constraints will change

- (void)setConstraints:(NSArray <NSLayoutConstraint *>*)trackingConstraints
activeWhenAwayFromEdge:(NSDirectionalRectEdge)edge NS_SWIFT_NAME(setConstraints(_:activeWhenAwayFrom:));
- (NSArray <NSLayoutConstraint *>*)constraintsActiveWhenAwayFromEdge:(NSDirectionalRectEdge)edge NS_SWIFT_NAME(constraints(activeWhenAwayFrom:));

/// Manually remove all constraints from this guide's tracking. 
- (void)removeAllTrackedConstraints;

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UITrackingLayoutGuide.h>
#endif
