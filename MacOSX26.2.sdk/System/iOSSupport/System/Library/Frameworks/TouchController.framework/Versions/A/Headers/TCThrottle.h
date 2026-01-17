//
//  TCThrottle.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <Metal/Metal.h>

#import <TouchController/TCControlLayout.h>
#import <TouchController/TCControl.h>
#import <TouchController/TCControlContents.h>

@class TCTouchController;

NS_ASSUME_NONNULL_BEGIN

/// Defines the orientation of the throttle.
typedef NS_ENUM(NSInteger, TCThrottleOrientation) {
    /// A vertical throttle.
    TCThrottleOrientationVertical,
    /// A horizontal throttle.
    TCThrottleOrientationHorizontal,
} NS_SWIFT_NAME(TCThrottle.Orientation) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos);

/// Represents a single on-screen throttle - a one axis input.
///
/// This is mirrored by a `GCControllerButtonInput` on the associated `GCController` instance.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCThrottle : NSObject<TCControl, TCControlLayout>

/// The contents for the background of the throttle.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *backgroundContents;
/// The contents for the indicator of the throttle.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *indicatorContents;

/// The orientation of the throttle.
@property (nonatomic, assign, readonly) TCThrottleOrientation orientation;

/// A Boolean value that indicates whether the control reverts to it's base value.
///
/// If `YES`, the control's value will revert to its base value when no longer pressed.
@property (nonatomic, assign) BOOL snapsToBaseValue;

/// The initial value of this control.
@property (nonatomic, assign) CGFloat baseValue;

/// The size (width, height) of the indicator itself in points.
@property (nonatomic, assign) CGSize indicatorSize;

/// The size (width, height) of the throttle itself, providing boundaries for the indicator, in points.
@property (nonatomic, assign) CGSize throttleSize;

/// The collider shape for the throttle.
@property (nonatomic, assign, readonly) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// Not available. Create the control via a `TCTouchController`.
- (instancetype)init NS_UNAVAILABLE;

@end



/// A descriptor for configuring a throttle.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCThrottleDescriptor : NSObject

/// The label associated with the throttle.
@property (nonatomic, strong) TCControlLabel *label;

/// The contents for the background of the throttle.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *backgroundContents;
/// The contents for the indicator of the throttle.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *indicatorContents;

/// The size (width, height) of the throttle in points.
@property (nonatomic, assign) CGSize size;
/// The size (width, height) of the indicator itself in points.
@property (nonatomic, assign) CGSize indicatorSize;
/// The size (width, height) of the throttle itself, providing boundaries for the indicator, in points.
@property (nonatomic, assign) CGSize throttleSize;

/// The orientation of the throttle.
@property (nonatomic, assign) TCThrottleOrientation orientation;
/// A Boolean value that indicates whether the control reverts to it's base value.
///
/// If `YES`, the control's value will revert to its base value when no longer pressed.
@property (nonatomic, assign) BOOL snapsToBaseValue;
/// The initial value of this control.
@property (nonatomic, assign) CGFloat baseValue;

/// The anchor point that the throttle's offset is relative to.
@property (nonatomic, assign) TCControlLayoutAnchor anchor;

/// The coordinate system for the control's anchor point.
@property (nonatomic, assign) TCControlLayoutAnchorCoordinateSystem anchorCoordinateSystem;
/// The control's offset from the anchor, which determines its position.
@property (nonatomic, assign) CGPoint offset;
/// The z-index of the throttle. A lower z-index is drawn first.
@property (nonatomic, assign) NSInteger zIndex;

/// The shape of collider to use for the throttle.
@property (nonatomic, assign) TCColliderShape colliderShape;
/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// Creates a new throttle descriptor with default values.
- (instancetype)init;

@end


NS_ASSUME_NONNULL_END
#endif
