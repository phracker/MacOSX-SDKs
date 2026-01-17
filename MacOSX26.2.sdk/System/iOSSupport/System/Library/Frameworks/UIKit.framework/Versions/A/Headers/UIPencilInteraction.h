#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPencilInteraction.h>)
//
//  UIPencilInteraction.h
//  UIKit
//
//  Copyright © 2018 Apple Inc. All rights reserved.
//

#import <UIKit/UIInteraction.h>
#import <UIKit/UIKitDefines.h>

@class UIPencilHoverPose, UIPencilInteractionTap, UIPencilInteractionSqueeze;
@protocol UIPencilInteractionDelegate;

#pragma mark - Defines

NS_HEADER_AUDIT_BEGIN(nullability, sendability)

/// Preferred actions available to the user in Settings.
typedef NS_ENUM(NSInteger, UIPencilPreferredAction) {

    /// No action, or the user has disabled pencil interactions in Accessibility settings
    UIPencilPreferredActionIgnore = 0,
    
    /// Switch between the current tool and eraser
    UIPencilPreferredActionSwitchEraser,
    
    /// Switch between the current tool and the previously used tool
    UIPencilPreferredActionSwitchPrevious,
    
    /// Show and hide the color palette
    UIPencilPreferredActionShowColorPalette,
    
    /// Show the ink attributes palette
    UIPencilPreferredActionShowInkAttributes API_AVAILABLE(ios(16.0), visionos(26.2)),

    /// Show a contextual palette of markup tools, or undo/redo options if tools are not available
    UIPencilPreferredActionShowContextualPalette API_AVAILABLE(ios(17.5), visionos(26.2)),

    /// The user has selected a system shortcut to run
    UIPencilPreferredActionRunSystemShortcut API_AVAILABLE(ios(17.5), visionos(26.2)),

} API_AVAILABLE(ios(12.1), visionos(26.2)) API_UNAVAILABLE(watchos, tvos);

/// The phase of an interaction gesture performed on the pencil.
///
/// If the gesture is discrete, the phase will be ``UIPencilInteractionPhaseEnded``
typedef NS_ENUM(NSUInteger, UIPencilInteractionPhase) {

    /// A continuous gesture on the pencil began
    UIPencilInteractionPhaseBegan,

    /// A continuous gesture on the pencil changed
    UIPencilInteractionPhaseChanged,

    /// A continuous gesture on the pencil ended, or a discrete gesture on the pencil recognized
    UIPencilInteractionPhaseEnded,

    /// A continuous gesture on the pencil was cancelled
    UIPencilInteractionPhaseCancelled,

} API_AVAILABLE(ios(17.5), visionos(26.2)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(UIPencilInteraction.Phase);

#pragma mark - Interaction

UIKIT_EXTERN API_AVAILABLE(ios(12.1), visionos(26.2)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPencilInteraction : NSObject <UIInteraction>

/// The user’s preferred double-tap action as set in Settings app
@property (class, nonatomic, readonly) UIPencilPreferredAction preferredTapAction;

/// The user’s preferred squeeze action as set in Settings app
@property (class, nonatomic, readonly) UIPencilPreferredAction preferredSqueezeAction API_AVAILABLE(ios(17.5), visionos(26.2));

/// The user's preference for drawing with pencil only as set in Settings app or the system tool picker
@property (class, nonatomic, readonly) BOOL prefersPencilOnlyDrawing;

/// The user's preference for if hovering with pencil should show a preview of the current drawing tool as set in Settings app
@property (class, nonatomic, readonly) BOOL prefersHoverToolPreview API_AVAILABLE(ios(17.5), visionos(26.2));

/// Initialize an interaction and set the provided delegate
- (instancetype)initWithDelegate:(id<UIPencilInteractionDelegate>)delegate API_AVAILABLE(ios(17.5), visionos(26.2));

/// The interaction's delegate
@property (nonatomic, weak, nullable) id<UIPencilInteractionDelegate> delegate;

/// Whether the interaction is enabled or not
@property (nonatomic, getter=isEnabled) BOOL enabled;

@end

#pragma mark - External Gestures

/// An object that describes the hover pose of the pencil while performing a gesture on the pencil
UIKIT_EXTERN API_AVAILABLE(ios(17.5), visionos(26.2)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@interface UIPencilHoverPose : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The hover location of the pencil in the interaction's view while performing the associated action. If the pencil is removed from hover range during a continuous interaction,
/// this will be the last reported location.
@property (nonatomic, readonly, assign) CGPoint location;

/// The normalized distance from the screen of the hovering pencil. This value will be 1 at the maximum distance from the screen and will approach 0 as the pencil gets
/// closer to the screen.
@property (nonatomic, readonly, assign) CGFloat zOffset;

/// The azimuth angle in radians of the pencil in the interaction's view while performing the associated action. Zero radians points along the positive X axis.
@property (nonatomic, readonly, assign) CGFloat azimuthAngle;

/// The azimuth unit vector of the pencil in the interaction's view while performing the associated action. The unit vector points in the direction of the azimuth angle.
@property (nonatomic, readonly, assign) CGVector azimuthUnitVector;

/// The altitude angle in radians of the pencil while performing the associated action. Zero radians indicates that the stylus is parallel to the screen surface, while `M_PI/2`
/// radians indicates that it is normal to the screen surface.
@property (nonatomic, readonly, assign) CGFloat altitudeAngle;

/// The roll angle in radians of the pencil while performing the associated action. For pencils that don't support roll, this value will be 0.
@property (nonatomic, readonly, assign) CGFloat rollAngle;

@end

/// An object that describes a tap performed on the pencil
UIKIT_EXTERN API_AVAILABLE(ios(17.5), visionos(26.2)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(UIPencilInteraction.Tap) NS_SWIFT_UI_ACTOR
@interface UIPencilInteractionTap : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The time in seconds from system start up when this tap occured
@property (nonatomic, readonly, assign) NSTimeInterval timestamp;

/// The hover pose of the pencil while performing a tap. Returns `nil` if the pencil was not in hover range or if hover is not supported on the device.
@property (nonatomic, readonly, strong, nullable) UIPencilHoverPose *hoverPose;

@end

/// An object that describes a squeeze performed on the pencil
UIKIT_EXTERN API_AVAILABLE(ios(17.5), visionos(26.2)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_NAME(UIPencilInteraction.Squeeze) NS_SWIFT_UI_ACTOR
@interface UIPencilInteractionSqueeze : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// The time in seconds from system start up when this squeeze occured
@property (nonatomic, readonly, assign) NSTimeInterval timestamp;

/// The phase of the squeeze
@property (nonatomic, readonly, assign) UIPencilInteractionPhase phase;

/// The hover pose of the pencil while performing a squeeze. Returns `nil` if the pencil was not in hover range or if hover is not supported on the device.
@property (nonatomic, readonly, strong, nullable) UIPencilHoverPose *hoverPose;

@end

#pragma mark - Interaction Delegate

UIKIT_EXTERN API_AVAILABLE(ios(12.1), visionos(26.2)) API_UNAVAILABLE(watchos, tvos) NS_SWIFT_UI_ACTOR
@protocol UIPencilInteractionDelegate <NSObject>

@optional

/// Called when the user taps on the side of the pencil if the interaction's view is in a visible view hierarchy.
///
/// The delegate may do anything in this method.  To perform the user's preferred tap action (as set in Settings), consult the ``preferredTapAction`` class property
/// of ``UIPencilInteraction``.
///
/// - Note: If ``pencilInteraction(_:didReceiveTap:)`` is implemented, this method will not be called.
- (void)pencilInteractionDidTap:(UIPencilInteraction *)interaction API_DEPRECATED("Use pencilInteraction(_:didReceiveTap:) instead", ios(12.1, 17.5), visionos(1.0, 1.2));

/// Called when the user taps on the side of the pencil if the interaction's view is in a visible view hierarchy.
///
/// The delegate may do anything in this method.  To perform the user's preferred tap action (as set in Settings), consult the ``preferredTapAction`` class property
/// of ``UIPencilInteraction``.
///
/// - Note: If both this method and the deprecated ``pencilInteractionDidTap(_:)`` are implemented, then only this method will be called.
- (void)pencilInteraction:(UIPencilInteraction *)interaction didReceiveTap:(UIPencilInteractionTap *)tap API_AVAILABLE(ios(17.5), visionos(26.2)) NS_SWIFT_NAME(pencilInteraction(_:didReceiveTap:));

/// Called when the user squeezes side of the pencil if the interaction's view is in a visible view hierarchy.
///
/// The delegate may do anything in this method.  To perform the user's preferred squeeze action (as set in Settings), consult the ``preferredSqueezeAction`` class
/// property of ``UIPencilInteraction``.
- (void)pencilInteraction:(UIPencilInteraction *)interaction didReceiveSqueeze:(UIPencilInteractionSqueeze *)squeeze API_AVAILABLE(ios(17.5), visionos(26.2)) NS_SWIFT_NAME(pencilInteraction(_:didReceiveSqueeze:));

@end

NS_HEADER_AUDIT_END(nullability, sendability)

#else
#import <UIKitCore/UIPencilInteraction.h>
#endif
