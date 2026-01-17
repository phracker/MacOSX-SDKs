//
//  TCTouchpad.h
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

/// Represents a single on-screen touchpad that reports absolute coordinates or delta movements.
///
/// This is mirrored by a `GCControllerDirectionPad` on the associated `GCController` instance.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCTouchpad : NSObject<TCControl, TCControlLayout>

/// The contents for the touchpad. May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *contents;

/// The collider shape for the touchpad.
@property (nonatomic, assign, readonly) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// A Boolean value that represents the touchpad reports deltas.
///
/// If `YES`, the touchpad will report relative delta changes between frames as touch moves instead of absolute positions.
@property (nonatomic, assign) BOOL reportsRelativeValues;

/// Not available. Create the control via a `TCTouchController`.
- (instancetype)init NS_UNAVAILABLE;

@end



/// A descriptor for configuring a touchpad.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCTouchpadDescriptor : NSObject

/// The label associated with the touchpad.
@property (nonatomic, strong) TCControlLabel *label;

/// The contents for the touchpad.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *contents;

/// The anchor point that the touchpad's offset is relative to.
@property (nonatomic, assign) TCControlLayoutAnchor anchor;

/// The coordinate system for the control's anchor point.
@property (nonatomic, assign) TCControlLayoutAnchorCoordinateSystem anchorCoordinateSystem;
/// The control's offset from the anchor, which determines its position.
@property (nonatomic, assign) CGPoint offset;
/// The z-index of the touchpad. A lower z-index is drawn first.
@property (nonatomic, assign) NSInteger zIndex;

/// The size (width, height) of the touchpad in points.
@property (nonatomic, assign) CGSize size;

/// The shape of collider to use for the touchpad.
@property (nonatomic, assign) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// A Boolean value that represents the touchpad reports deltas.
///
/// If `YES`, the touchpad will report delta values as touch moves instead of absolute positions.
@property (nonatomic, assign) BOOL reportsRelativeValues;

/// Creates a new touchpad descriptor with default values.
- (instancetype)init;

@end


NS_ASSUME_NONNULL_END
#endif
