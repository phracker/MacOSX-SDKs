//
//  TCControl.h
//  TouchController
//

#if !TARGET_OS_OSX
#import <Foundation/Foundation.h>

#import <TouchController/TCControlLayout.h>
#import <TouchController/TCColliderShape.h>
#import <TouchController/TCControlLabel.h>

NS_ASSUME_NONNULL_BEGIN

/// A protocol that defines the base properties and methods for all touch controls.
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@protocol TCControl <NSObject, TCControlLayout>

@required

/// The label associated with the control.
@property (nonatomic, strong, readonly) TCControlLabel *label;

/// The collider shape for the control.
@property (nonatomic, assign, readonly) TCColliderShape colliderShape;

/// Indicates whether the control is currently pressed.
@property (nonatomic, assign, readonly, getter=isPressed) BOOL pressed;

/// A Boolean value that indicates whether the control is enabled.
///
/// If disabled, it won't respond to touches.
@property (nonatomic, assign, getter=isEnabled) BOOL enabled;

/// Handles a touch began event at the specified point.
///
/// - Parameters:
///   - point: The point where the touch began.
- (void)handleTouchBeganAtPoint:(CGPoint)point;

/// Handles a touch moved event at the specified point.
///
/// - Parameters:
///   - point: The point where the touch moved to.
- (void)handleTouchMovedAtPoint:(CGPoint)point;

/// Handles a touch ended event at the specified point.
///
/// - Parameters:
///   - point: The point where the touch ended.
- (void)handleTouchEndedAtPoint:(CGPoint)point;

@optional

/// The duration of the highlight animation.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

@end

NS_ASSUME_NONNULL_END
#endif
