//
//  PKCanvasView.h
//  PencilKit
//
//  Copyright © 2019 Apple. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PencilKit/PKToolPicker.h>


NS_ASSUME_NONNULL_BEGIN

@class PKDrawing, PKTool, PKCanvasView;

#if !TARGET_OS_MACCATALYST
/// The optional methods a delegate can receive from editing-related changes
/// to a PKCanvasView.
API_AVAILABLE(ios(13.0))
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

/// Is the finger allowed to draw in the canvas.
/// If false, only styluses will draw. If true, two-fingers are used to scroll.
/// Defaults to YES.
@property (nonatomic) BOOL allowsFingerDrawing;

@end

#else // TARGET_OS_MACCATALYST
API_AVAILABLE(ios(13.0))
@interface PKCanvasView : UIScrollView

/// The drawing shown on this view.
@property (nonatomic, copy) PKDrawing *drawing;

@end
#endif

NS_ASSUME_NONNULL_END
