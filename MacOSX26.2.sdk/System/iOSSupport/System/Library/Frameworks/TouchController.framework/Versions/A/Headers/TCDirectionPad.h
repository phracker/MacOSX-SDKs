//
//  TCDirectionPad.h
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

/// An object that represents a direction pad.
///
/// You can configure this object to behave as either a composite direction pad (mirrored by a
/// `GCControllerDirectionPad` on the associated `GCController` instance) or as four separate
/// buttons.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCDirectionPad : NSObject<TCControl, TCControlLayout>

/// A composite control label.
///
/// If set, the control will behave as a `GCControllerDirectionPad`; otherwise, it behaves as separate buttons.
@property (nonatomic, strong, nullable) TCControlLabel *compositeLabel;
/// The label for the up button, if the control isn't a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *upLabel;
/// The label for the down button, if the control isn't a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *downLabel;
/// The label for the left button, if the control isn't a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *leftLabel;
/// The label for the right button, if the control isn't a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *rightLabel;

/// The contents for the up button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *upContents;

/// The contents for the down button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *downContents;

/// The contents for the left button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *leftContents;

/// The contents for the right button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *rightContents;

/// The collider shape for the direction pad.
@property (nonatomic, assign, readonly) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;


/// A Boolean value that indicates whether the control behaves as a swipeable radial button.
///
/// If `YES`, the control behaves as a swipable radial button, rather than a collection of 4 separate buttons.
@property (nonatomic, assign, getter=isRadial) BOOL radial;

/// A Boolean value that indicates whether the control behaves as a digital button.
///
/// If `YES`, dpad buttons will report 1 or 0. Ignored if radial is set, as button presses will always be digital.
@property (nonatomic, assign, getter=isDigital) BOOL digital;

/// A Boolean value that indicates whether the control has mutally exclusive input.
///
/// If `YES`, only one element of the direction pad can be pressed at a time.
@property (nonatomic, assign, getter=inputIsMutuallyExclusive) BOOL mutuallyExclusiveInput;

/// Not available. Create the control via a `TCTouchController`.
- (instancetype)init NS_UNAVAILABLE;

@end



/// A descriptor for configuring a directional pad.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCDirectionPadDescriptor : NSObject

/// A composite control label.
///
/// If set, the control will behave as a `GCControllerDirectionPad`. Otherwise, it will behave as separate buttons.
@property (nonatomic, strong, nullable) TCControlLabel *compositeLabel;
/// The label for the up button, if the control isn't a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *upLabel;
/// The label for the down button, if the control is not a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *downLabel;
/// The label for the left button, if the control is not a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *leftLabel;
/// The label for the right button, if the control is not a composite direction pad.
@property (nonatomic, strong, nullable) TCControlLabel *rightLabel;

/// The contents for the up button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *upContents;
/// The contents for the down button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *downContents;
/// The contents for the left button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *leftContents;
/// The contents for the right button.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *rightContents;

/// The anchor point that the direction pad's offset is relative to.
@property (nonatomic, assign) TCControlLayoutAnchor anchor;

/// The coordinate system for the control's anchor point.
@property (nonatomic, assign) TCControlLayoutAnchorCoordinateSystem anchorCoordinateSystem;
/// The control's offset from the anchor, which determines its position.
@property (nonatomic, assign) CGPoint offset;
/// The z-index of the direction pad. A lower z-index is drawn first.
@property (nonatomic, assign) NSInteger zIndex;
/// The size (width, height) of the direction pad in points.
@property (nonatomic, assign) CGSize size;

/// The shape of collider to use for the direction pad.
@property (nonatomic, assign) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// A Boolean value that indicates whether the control behaves as a swipeable radial button.
///
/// If `YES`, the control behaves as a swipable radial button, rather than a collection of 4 separate buttons.
@property (nonatomic, assign, getter=isRadial) BOOL radial;

/// A Boolean value that indicates whether the control behaves as a digital button.
///
/// If `YES`, dpad buttons will report 1 or 0. Ignored if radial is set, as button presses will always be digital.
@property (nonatomic, assign, getter=isDigital) BOOL digital;

/// A Boolean value that indicates whether the control has mutally exclusive input.
///
/// If `YES`, only one element of the direction pad can be pressed at a time.
@property (nonatomic, assign, getter=inputIsMutuallyExclusive) BOOL mutuallyExclusiveInput;

/// Creates a new instance with default values.
- (instancetype)init;

@end

NS_ASSUME_NONNULL_END
#endif
