//
//  PKResponderState.h
//  PencilKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class PKToolPicker;

/// The visibility state of a tool picker.
API_AVAILABLE(ios(26.0), visionos(26.0))
NS_SWIFT_SENDABLE
typedef NS_ENUM(NSInteger, PKToolPickerVisibility) {
    /// Inherit the tool picker visibility from the next responder.
    PKToolPickerVisibilityInherited NS_REFINED_FOR_SWIFT,
    /// No active tool picker.
    PKToolPickerVisibilityInactive,
    /// Tool picker is active but offscreen, and can appear temporarily in response to user actions.
    PKToolPickerVisibilityHidden,
    /// Tool picker is active and onscreen.
    PKToolPickerVisibilityVisible
};

/// The state of PencilKit behavior related to a `UIResponder`.
///
/// Control the behavior of responders via the `UIResponder.pencilKitResponderState` property.
/// ```swift
/// view.pencilKitResponderState.activeToolPicker = PKToolPicker()
/// view.pencilKitResponderState.toolPickerVisibility = .visible
/// ```
API_AVAILABLE(ios(26.0), visionos(26.0))
@interface PKResponderState : NSObject

/// The visibility state of the tool picker.
///
/// This controls the state of the tool picker that is provided by the `activeToolPicker` property.
///
/// If `PKToolPickerVisibilityInherited` tool picker visibility is based on the next responder. If no responder provides a visibility, the default is `PKToolPickerVisibilityVisible`.
@property (nonatomic, assign) PKToolPickerVisibility toolPickerVisibility NS_REFINED_FOR_SWIFT;

/// The current tool picker.
///
/// Control tool picker visibility with the `toolPickerVisibility` property.
///
/// If `nil` the active tool picker is based on the next responder.
@property (nonatomic, strong, nullable) PKToolPicker *activeToolPicker;

@end


API_AVAILABLE(ios(26.0), visionos(26.0))
@interface UIResponder (PKResponderState)

/// The PencilKit state associated with the responder object.
///
/// The state controls PencilKit behavior related to this responder.
@property (nonatomic, readonly, nonnull) PKResponderState *pencilKitResponderState;

@end

NS_ASSUME_NONNULL_END
