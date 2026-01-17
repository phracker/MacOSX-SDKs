//
//  PKCanvasView.h
//  PencilKit
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PencilKit/PKToolPicker.h>


NS_ASSUME_NONNULL_BEGIN

@class PKDrawing, PKTool, PKCanvasView;

/// The optional methods a delegate can receive from editing-related changes
/// to a PKCanvasView.
API_AVAILABLE(ios(13.0))
NS_SWIFT_UI_ACTOR
@protocol PKCanvasViewDelegate<NSObject, UIScrollViewDelegate>
@optional
/// Called after the drawing on the canvas did change.
///
/// This may be called some time after the `canvasViewDidEndUsingTool:` delegate method.
/// For example, when using the Apple Pencil, pressure data is delayed from touch data, this
/// means that the user can stop drawing (`canvasViewDidEndUsingTool:` is called), but the
/// canvas view is still waiting for final pressure values; only when the final pressure values
/// are received is the drawing updated and this delegate method called.
///
/// It is also possible that this method is not called, if the drawing interaction is cancelled.
///
/// @param canvasView The canvas view that changed.
- (void)canvasViewDrawingDidChange:(PKCanvasView *)canvasView;

/// Called after setting `drawing` when the entire drawing is rendered and visible.
///
/// This method lets you know when the canvas view finishes rendering all of the currently
/// visible content. This can be used to delay showing the canvas view until all content is visible.
///
/// This is called every time the canvasView transitions from partially rendered to fully rendered,
/// including after setting the drawing, and after zooming or scrolling.
///
/// @param canvasView The canvas view that finished rendering.
- (void)canvasViewDidFinishRendering:(PKCanvasView *)canvasView;

/// Called when the user starts using a tool, eg. selecting, drawing, or erasing.
///
/// This does not include moving the ruler.
///
/// @param canvasView The canvas view that the user started interacting with.
- (void)canvasViewDidBeginUsingTool:(PKCanvasView *)canvasView  NS_SWIFT_NAME(canvasViewDidBeginUsingTool(_:));

/// Called when the user stops using a tool, eg. selecting, drawing, or erasing.
///
/// @param canvasView The canvas view that the user ended interacting with.
- (void)canvasViewDidEndUsingTool:(PKCanvasView *)canvasView NS_SWIFT_NAME(canvasViewDidEndUsingTool(_:));
@end


typedef NS_ENUM(NSUInteger, PKCanvasViewDrawingPolicy) {
    /// Default is: if a `PKToolPicker` is visible, respect `UIPencilInteraction.prefersPencilOnlyDrawing`,
    /// otherwise only pencil touches draw.
    PKCanvasViewDrawingPolicyDefault,
    PKCanvasViewDrawingPolicyAnyInput,
    PKCanvasViewDrawingPolicyPencilOnly
};


/// The view for interactively drawing, and non-interactively showing PKDrawing contents.
API_AVAILABLE(ios(13.0))
@interface PKCanvasView : UIScrollView <PKToolPickerObserver>

/// The delegate for drawing operations.
@property (nonatomic, weak, nullable) id<PKCanvasViewDelegate> delegate;

/// The drawing shown on this view.
@property (nonatomic, copy) PKDrawing *drawing;

/// The tool used to interact with the canvas.
/// Default is `[[PKInkingTool alloc] initWithType:PKInkTypePen color:UIColor.blackColor]`
@property (nonatomic, copy) PKTool *tool NS_REFINED_FOR_SWIFT;

/// Is the ruler shown on the canvas.
@property (nonatomic, getter=isRulerActive) BOOL rulerActive;

/// The gesture recognizer used to draw in the canvas.
@property (nonatomic, readonly) UIGestureRecognizer *drawingGestureRecognizer;

/// Controls if drawing input is enabled on this canvas view. Defaults to true.
///
/// Note `toolPickerSelectedToolItemDidChange` may set this value
/// as some `PKToolPickerItem`s do not have a `PKTool`.
/// This will happen when the canvas is an observer of a `PKToolPicker`.
@property (nonatomic, assign, getter=isDrawingEnabled) BOOL drawingEnabled API_AVAILABLE(ios(18.0), visionos(2.0));

@property (nonatomic) BOOL allowsFingerDrawing API_DEPRECATED("Use 'drawingPolicy' property.", ios(13_0, 14_0));

/// The drawing policy that controls the types of touches that are allowed to draw in the canvas.
/// Defaults to `PKCanvasViewDrawingPolicyDefault`.
@property (nonatomic, assign) PKCanvasViewDrawingPolicy drawingPolicy API_AVAILABLE(ios(14.0));

/// The maximum supported PencilKit content version.
///
/// Setting this to less than `.latest` limits the edits that can be made so they are compatible with the
/// specified version. If setting this property, also set it on any `PKToolPicker` used.
///
/// Defaults to `.latest`.
@property (nonatomic, assign) PKContentVersion maximumSupportedContentVersion API_AVAILABLE(ios(17.0), macos(14.0));

@end

NS_ASSUME_NONNULL_END
