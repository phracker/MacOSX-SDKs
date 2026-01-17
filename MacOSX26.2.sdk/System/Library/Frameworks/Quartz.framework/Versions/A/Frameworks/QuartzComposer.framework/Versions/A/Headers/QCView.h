/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <AppKit/AppKit.h>

#import <QuartzComposer/QCRenderer.h>

/* HIGH-LEVEL NOTES:
- A QCView is a custom NSView that plays Quartz compositions.
- When archived, a QCView saves its current composition.
- V-sync is always enabled in the QCView.
- If "autoStart" is set to YES, the QCView automatically starts rendering when it is put on screen (default setting is NO).
- The QCView automatically stops rendering when it is put off screen.
- When the QCView is not rendering, it is filled with the erase color.
- Use the methods from the <QCCompositionRenderer> protocol to communicate with the composition.
- The input and output ports of the root patch of the composition are also accessible with KVC through the "patch" property e.g. "patch.inputFoo.value".
*/

/* Notification names */
extern NSString* const QCViewDidStartRenderingNotification QC_DEPRECATED_MAC(10_15);
extern NSString* const QCViewDidStopRenderingNotification QC_DEPRECATED_MAC(10_15);

/* Quartz Composer Composition View */
QC_CLASS_DEPRECATED_MAC(10_15)
@interface QCView : NSView <QCCompositionRenderer>
{
@private
	void*				_QCViewPrivate;
}

/*
Loads a Quartz composition file on the view.
*/
- (BOOL) loadCompositionFromFile:(NSString*)path;

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/*
Loads a QCComposition object.
*/
- (BOOL) loadComposition:(QCComposition*)composition;

/*
Returns the QCComposition from the QCView or nil if none is currently loaded.
*/
- (QCComposition*) loadedComposition;

/* 
Unloads the compositon from the view. Indirectly calls -stopRendering if necessary 
*/
- (void) unloadComposition;

#endif


/*
Sets / Checks if the view automatically starts rendering when put on screen.
*/
- (void) setAutostartsRendering:(BOOL)flag;
- (BOOL) autostartsRendering;

/*
Sets / Retrieves the color to be used by -erase.
*/
- (void) setEraseColor:(NSColor*)color;
- (NSColor*) eraseColor;

/*
Set / Retrieves the mask used to filter which types of events are forwarded from the view to the composition when rendering.
The events which may be filtered are:
	NSLeftMouseDown
	NSLeftMouseDragged
	NSLeftMouseUp
	NSRightMouseDown
	NSRightMouseDragged
	NSRightMouseUp
	NSOtherMouseDown
	NSOtherMouseDragged
	NSOtherMouseUp	
	NSMouseMoved
	NSScrollWheel
	NSKeyDown
	NSKeyUp
	NSFlagsChanged
The mask should be a combination of the masks corresponding to the above events or be "NSAnyEventMask".
*/
- (void) setEventForwardingMask:(NSUInteger)mask;
- (NSUInteger) eventForwardingMask;


/*
Sets / Retrieves the maximum rendering framerate (pass 0.0 to specify no limit).
*/
- (void) setMaxRenderingFrameRate:(float)maxFPS;
- (float) maxRenderingFrameRate;

/*
Clears the view with the current erase color.
*/
- (void) erase;

/*
Starts rendering and returns NO on failure.
*/
- (BOOL) startRendering;

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/*
Allow subclassers to do additional operations or OpenGL rendering before and after the composition is rendered.
Do not call this method directly.
If the return value of super is NO, or if your custom rendering failed, return NO, otherwise, return YES.

Use the OpenGL context of the QCView to do drawing. You can retrieve it by calling [self openGLContext].
Note that this context won't be necessarily set as the current OpenGL context.
For efficiency, it is recommended you use <OpenGL/CGLMacro.h> instead of setting this context as current:
	CGLContextObj cgl_ctx = [[self openGLContext] CGLContextObj];
	//OpenGL commands go here
Make sure you save / restore all OpenGL states you change (except states defined in GL_CURRENT_BIT).
Do not flush the context, since that is handled by the QCView.
*/
- (BOOL) renderAtTime:(NSTimeInterval)time arguments:(NSDictionary*)arguments;

/*
Pauses rendering in the view (calls to that method can be nested).
*/
- (void) pauseRendering;

/*
Returns YES if the view rendering is currently paused.
*/
- (BOOL) isPausedRendering;

/*
Resumes rendering in the view if previously paused (calls to that method can be nested).
*/
- (void) resumeRendering;

#endif

/*
Stops rendering in the view.
*/
- (void) stopRendering;

/*
Returns YES if the view is currently rendering.
*/
- (BOOL) isRendering;


#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/*
Returns a snapshot of the current image in the QCView.
*/
- (NSImage*) snapshotImage;

/*
Returns a snapshot of the current image in the QCView as a specific image type.
The following image types are supported: NSBitmapImageRep, NSImage, CIImage, CGImage, CVOpenGLBuffer, CVPixelBuffer or QCImage (optimized abstract image object only to be used with -setValue:forInputKey: of a <QCCompositionRenderer>).
The caller is responsible for releasing the returned object.
*/
- (id) createSnapshotImageOfType:(NSString*)type NS_RETURNS_RETAINED;

/*
Returns the OpenGL context used by the QCView.
Consider this context as a read-only object and do not attempt to change any of its settings.
*/
- (NSOpenGLContext*) openGLContext;

/*
Returns the OpenGL pixel format used by the QCView.
Consider this pixel format as a read-only object and do not attempt to change any of its settings.
*/
- (NSOpenGLPixelFormat*) openGLPixelFormat;

#endif


@end


@interface QCView (IBExtensions)

/*
IBAction equivalent of -startRendering.
*/
- (IBAction) start:(id)sender;

/*
IBAction equivalent of -stopRendering.
*/
- (IBAction) stop:(id)sender;

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/*
IBAction that starts rendering if not already rendering, pauses if already rendering or resumes rendering if paused
*/
- (IBAction) play:(id)sender;

#endif

@end

