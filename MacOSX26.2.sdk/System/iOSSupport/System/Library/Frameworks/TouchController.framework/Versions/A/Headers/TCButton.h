//
//  TCButton.h
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

/// A control that represents a single on-screen button.
///
/// This is mirrored by a <doc://com.apple.documentation/documentation/gamecontroller/gccontrollerbuttoninput>
/// on the associated <doc://com.apple.documentation/documentation/gamecontroller/gccontroller>.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCButton : NSObject<TCControl, TCControlLayout>

/// The contents for the button in its normal state.
///
/// This value can be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *contents;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// The collider shape for the button.
@property (nonatomic, assign, readonly) TCColliderShape colliderShape;

/// Not available.  Create the control via a `TCTouchController`.
- (instancetype)init NS_UNAVAILABLE;

@end



/// A descriptor for configuring a button.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCButtonDescriptor : NSObject

/// The label you associate with the button.
@property (nonatomic, strong) TCControlLabel *label;

/// The contents for the button in its normal state.
///
/// This value can be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *contents;

/// The anchor point that the button's offset is relative to.
@property (nonatomic, assign) TCControlLayoutAnchor anchor;

/// The coordinate system for the control's anchor point.
@property (nonatomic, assign) TCControlLayoutAnchorCoordinateSystem anchorCoordinateSystem;

/// The control's offset from the anchor, which determines its position.
@property (nonatomic, assign) CGPoint offset;

/// The z-index of the button. A lower z-index is drawn first.
@property (nonatomic, assign) NSInteger zIndex;

/// The size (width, height) of the button in points.
@property (nonatomic, assign) CGSize size;

/// The shape of collider to use for the button.
@property (nonatomic, assign) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// Creates a new button descriptor with default values.
- (instancetype)init;

@end

NS_ASSUME_NONNULL_END
#endif
