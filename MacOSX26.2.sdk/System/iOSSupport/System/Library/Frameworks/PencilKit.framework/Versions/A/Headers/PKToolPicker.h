//
//  PKToolPicker.h
//  PencilKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <PencilKit/PKContentVersion.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class PKTool, PKToolPicker, PKToolPickerItem;

API_AVAILABLE(ios(13.0))
NS_SWIFT_UI_ACTOR
@protocol PKToolPickerObserver <NSObject>

@optional
/// Tells the delegate that the selected tool was changed by the user.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerSelectedToolDidChange:(PKToolPicker *)toolPicker API_DEPRECATED("Use toolPickerSelectedToolItemDidChange instead.", ios(13_0, 18_0), visionos(1_0, 2_0));

/// Tells the delegate that the selected tool item was changed by the user.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerSelectedToolItemDidChange:(PKToolPicker *)toolPicker API_AVAILABLE(ios(18.0), visionos(2.0));

/// Tells the delegate that the ruler active state was changed by the user.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerIsRulerActiveDidChange:(PKToolPicker *)toolPicker;

/// Tells the delegate that the tool picker UI changed visibility.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerVisibilityDidChange:(PKToolPicker *)toolPicker;

/// Tells the delegate that the frames the tool picker obscures changed.
/// Note, the obscured frames for a view can also change when that view
/// changes, not just when this delegate method is called.
///
/// @param toolPicker  The tool picker that changed.
- (void)toolPickerFramesObscuredDidChange:(PKToolPicker *)toolPicker;

@end

API_AVAILABLE(ios(18.0), visionos(2.0))
NS_SWIFT_UI_ACTOR
NS_SWIFT_NAME(PKToolPicker.Delegate)
@protocol PKToolPickerDelegate <NSObject>

@optional

/// This is called when the user dismisses the tool picker using a built-in control.
/// This is **not** called when the tool picker hides from a responder change or other programatic request.
/// By default, using the dismissal control on the tool picker causes the tool picker to resign the first responder.
/// The delegate may override that default behavior, taking responsibility for the dismissal of the picker, by returning true from this method.
- (BOOL)toolPickerWillDismiss:(PKToolPicker *)toolPicker API_AVAILABLE(visionos(2.0)) API_UNAVAILABLE(ios);

@end

/// A user interface for selecting a PKTool.
API_AVAILABLE(ios(13.0))
@interface PKToolPicker : NSObject

/// Add an observer for a tool picker changes.
///
/// Adding a `PKCanvasView` as an observer, will also set its initial state.
/// Observers are held weakly.
- (void)addObserver:(id<PKToolPickerObserver>)observer NS_SWIFT_NAME(addObserver(_:));

/// Remove an observer for a tool picker changes.
- (void)removeObserver:(id<PKToolPickerObserver>)observer NS_SWIFT_NAME(removeObserver(_:));

/// Sets when this tool picker should be visible.
///
/// @param visible  The visible state of this tool picker.
/// @param responder  The first responder for which this visible state applies.
- (void)setVisible:(BOOL)visible forFirstResponder:(UIResponder *)responder;

/// The delegate for the tool picker.
@property (nonatomic, weak, nullable) id<PKToolPickerDelegate> delegate API_AVAILABLE(ios(18.0), visionos(2.0));

/// The currently selected tool.
@property (nonatomic, strong) PKTool *selectedTool API_DEPRECATED("Use selectedToolItem instead.", ios(13_0, 18_0), visionos(1_0, 2_0)) NS_REFINED_FOR_SWIFT;

/// The currently selected tool item.
/// Updating this property will select the tool with the matching identifier without altering the item.
@property (nonatomic, strong) PKToolPickerItem *selectedToolItem API_AVAILABLE(ios(18.0), visionos(2.0));

/// The identifier of the selected tool item.
/// Setting it to an identifier without a matching item in this picker has no effect.
@property (nonatomic, copy) NSString *selectedToolItemIdentifier API_AVAILABLE(ios(18.0), visionos(2.0));

/// All tool items within the picker.
@property (nonatomic, readonly) NSArray<PKToolPickerItem *> *toolItems API_AVAILABLE(ios(18.0), visionos(2.0));

/// The default tool items for new tool pickers.
///
/// These items are used when creating a new `PKToolPicker`.
@property (class, nonatomic, nonnull, readonly) NSArray<PKToolPickerItem *> *defaultToolItems API_AVAILABLE(ios(26.0), visionos(26.0));

/// Is the ruler toggled such that it should be active on canvases.
@property (nonatomic, getter=isRulerActive) BOOL rulerActive;

/// Is the tool picker visible.
@property (nonatomic, readonly) BOOL isVisible;

/// The name used to automatically save the tool picker's state in the defaults system.
/// As of iOS 18.0 and visionOS 2.0, setting the value to nil disables auto-save.
@property (nonatomic, copy, nullable) NSString *stateAutosaveName API_AVAILABLE(ios(14.0));

/// The maximum supported PencilKit content version.
///
/// Setting this to less than `.latest` limits the tools that are available to select so that they are compatible with the
/// specified version. If setting this property, also set it on `PKCanvasView`.
///
/// Defaults to `.latest`.
@property (nonatomic, assign) PKContentVersion maximumSupportedContentVersion API_AVAILABLE(ios(17.0), macos(14.0));

/// The frame within a specific view that the tool picker covers.
///
/// @param view The view in which to return the frame to avoid.
/// @return The rect in `view` that the tool picker obscures. Will return
/// `CGRectNull` if no rect is obscured, or the tool picker is movable.
- (CGRect)frameObscuredInView:(UIView *)view;

/// Set `overrideUserInterfaceStyle` to cause this tool picker UI to have a specific user interface style.
/// Consider if you need to set `colorUserInterfaceStyle` if you set this property.
///
/// By default this is `UIUserInterfaceStyleUnspecified`.
@property (nonatomic) UIUserInterfaceStyle overrideUserInterfaceStyle;

/// Set `colorUserInterfaceStyle` to cause this tool picker to create colors for a canvas view of the
/// specified user interface style. If this tool picker is used for selecting tools for canvas views that
/// have different user interface styles, `colorUserInterfaceStyle` should be set to the canvas's user
/// interface style.
///
/// By default this is `UIUserInterfaceStyleUnspecified`.
@property (nonatomic) UIUserInterfaceStyle colorUserInterfaceStyle;

/// If this is true the tool picker will show UI that allows the default drawing policy to be changed.
///
/// By default this is true.
@property (nonatomic) BOOL showsDrawingPolicyControls API_AVAILABLE(ios(14.0));

/// If this is true the tool picker may show UI that allows dismissing it.
/// If this is false the tool picker will not show this UI.
/// By default this resigns first responder, but is customizable by `PKToolPickerDelegate`'s `toolPickerWillDismiss...` method.
///
/// By default this is true.
@property (nonatomic) BOOL prefersDismissControlVisible API_AVAILABLE(visionos(2.0)) API_UNAVAILABLE(ios);

/// If this is non-nil, the tool picker will display this item when the tool picker is displayed in supported expanded configurations.
@property (nonatomic, strong, nullable) UIBarButtonItem *accessoryItem API_AVAILABLE(ios(18.0), visionos(2.0));

/// Returns the shared `PKToolPicker` instance for a window.
/// The returned tool picker object is typically shared between windows in the same UIWindowScene.
+ (nullable PKToolPicker *)sharedToolPickerForWindow:(UIWindow *)window NS_SWIFT_NAME(shared(for:)) API_DEPRECATED("Create individual instances instead.", ios(13_0, 14_0));

/// Returns a new `PKToolPicker` instance.
///
/// If two tool pickers are visible for the same first responder, or the same tool picker is visible in two windows
/// the result is deterministic, but undefined.
- (instancetype)init API_AVAILABLE(ios(14.0));

/// Returns a new `PKToolPicker` instance with the given picker items.
/// @param items the items in desired order that are used to set up the picker.  At least one item is required.
///        If `items` contains tools with the same identifier, only the first item is used to create the picker.
- (instancetype)initWithToolItems:(NSArray<PKToolPickerItem *> *)items API_AVAILABLE(ios(18.0), visionos(2.0));

/// Maximum linear exposure for the color picker used by the tool picker. Can be used to enable picking HDR colors.
///
/// Default value is 1.0 which means only SDR colors can be picked.
@property (nonatomic, assign) CGFloat colorMaximumLinearExposure API_AVAILABLE(ios(26.0), visionos(26.0));

@end
NS_ASSUME_NONNULL_END
