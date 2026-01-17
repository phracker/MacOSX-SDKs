//
//  TCThumbstick.h
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

/// Represents a single on-screen thumbstick.
///
/// This is mirrored by a `GCControllerDirectionPad` on the associated `GCController` instance.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCThumbstick : NSObject<TCControl, TCControlLayout>

/// The contents for the background of the thumbstick.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *backgroundContents;

/// The contents for the thumbstick itself.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *stickContents;

/// A Boolean value that indicates whether to hide the thumbstick when it is not being pressed.
@property (nonatomic, assign) BOOL hidesWhenNotPressed;

/// The size (width, height) of the thumbstick stick itself in points.
@property (nonatomic, assign) CGSize stickSize;

/// The collider shape for the thumbstick.
@property (nonatomic, assign, readonly) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// Not available. Create the control via a `TCTouchController`.
- (instancetype)init NS_UNAVAILABLE;

@end



/// A descriptor for configuring a thumbstick.
__attribute__((visibility ("default")))
API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(macCatalyst, visionos)
@interface TCThumbstickDescriptor : NSObject

/// The label associated with the thumbstick.
@property (nonatomic, strong) TCControlLabel *label;

/// The contents for the background of the thumbstick.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *backgroundContents;

/// The contents for the thumbstick itself.
///
/// May be `nil`.
@property (nonatomic, strong, nullable) TCControlContents *stickContents;

/// Whether to hide the thumbstick when it is not being pressed.
@property (nonatomic, assign) BOOL hidesWhenNotPressed;

/// The size (width, height) of the thumbstick stick itself in points.
@property (nonatomic, assign) CGSize stickSize;
/// The size (width, height) of the thumbstick in points.
@property (nonatomic, assign) CGSize size;

/// The anchor point that the thumbstick's offset is relative to.
@property (nonatomic, assign) TCControlLayoutAnchor anchor;

/// The coordinate system for the control's anchor point.
@property (nonatomic, assign) TCControlLayoutAnchorCoordinateSystem anchorCoordinateSystem;
/// The control's offset from the anchor, which determines its position.
@property (nonatomic, assign) CGPoint offset;
/// The z-index of the thumbstick. A lower z-index is drawn first.
@property (nonatomic, assign) NSInteger zIndex;

/// The shape of collider to use for the thumbstick.
@property (nonatomic, assign) TCColliderShape colliderShape;

/// The time it takes for a highlight to fade away, in seconds.
@property (nonatomic, assign) NSTimeInterval highlightDuration;

/// Creates a new thumbstick descriptor with default values.
- (instancetype)init;

@end


NS_ASSUME_NONNULL_END
#endif
