/*
	Copyright:	(c) 2003-2004 by Apple Computer, Inc., all rights reserved.
*/

#import <AppKit/AppKit.h>
#import <QuartzComposer/QCRenderer.h>

/* HIGH-LEVEL NOTES:
- A QCView is a custom NSView that plays QuartzComposer compositions.
- When archived, a QCView saves its current composition.
- V-sync is always enabled in the QCView.
- If "autoStart" is set to YES, the QCView automatically starts rendering when it is put on screen (default setting is NO).
- The QCView automatically stops rendering when it is put off screen.
- When the QCView is not rendering, it is filled with the erase color.
*/

/* Notification names */
extern NSString* const QCViewDidStartRenderingNotification;
extern NSString* const QCViewDidStopRenderingNotification;

/* QuartzComposer Composition Player */
@interface QCView : NSView
{
@private
	__strong void*				_QCViewPrivate;
}

/*
Loads a Quartz Composer composition file on the view.
*/
- (BOOL) loadCompositionFromFile:(NSString*)path;

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
- (void) setEventForwardingMask:(unsigned)mask;
- (unsigned) eventForwardingMask;

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

/*
Stops rendering in the view.
*/
- (void) stopRendering;

/*
Returns YES if the view is currently rendering.
*/
- (BOOL) isRendering;

/*
Returns a dictionary containing attributes describing the composition and the input / output ports on its root patch.
The dictionary may define the following composition attributes:
	- QCCompositionAttributeNameKey: the name of the composition as specified in the information dialog in Quartz Composer (NSString*)
	- QCCompositionAttributeDescriptionKey: the description of the composition as specified in the information dialog in Quartz Composer (NSString*)
	- QCCompositionAttributeCopyrightKey: the copyright of the composition as specified in the information dialog in Quartz Composer (NSString*)
The dictionary also contains dictionaries corresponding to the keys identifying each input / output port of the root patch of the composition. Each of those dictionaries defines the following port attributes:
	- QCPortAttributeTypeKey: the type of the port (NSString)
	- QCPortAttributeNameKey: the name of the port if available (NSString)
	- QCPortAttributeMinimumValueKey: the minimum numerical value accepted by the port if available - smaller values will be clamped (NSNumber)
	- QCPortAttributeMaximumValueKey: the maximum numerical value accepted by the port if available - bigger values will be clamped (NSNumber)
*/
- (NSDictionary*) attributes;

/*
Returns an array listing the keys identifying the input ports of the root patch of the composition.
*/
- (NSArray*) inputKeys;

/*
Returns an array listing the keys identifying the output ports of the root patch of the composition.
*/
- (NSArray*) outputKeys;

/*
Sets the value on an input port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid or return NO if it cannot set the value.
The types of values you can pass depends on the type of the input port:
	- NSNumber or any object that responds to -intValue, -floatValue or -doubleValue for Boolean, Index and Number ports
	- NSString or any object that responds to -stringValue or -description for String ports
	- NSColor for Color ports
	- NSImage, CGImageRef, CIImage or CVImageBufferRef for Image ports
	- NSArray or NSDictionary for Structure ports
This method will force a redraw if the view is currently rendering in "kQCViewRenderingModeAutomatic" mode.
*/
- (BOOL) setValue:(id)value forInputKey:(NSString*)key;

/*
Returns the current value on an input port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid.
The type of value returned depends on the type of the input port:
- NSNumber for Boolean, Index and Number ports
- NSString for String ports
- NSColor for Color ports
- NSImage for Image ports
- NSDictionary for Structure ports
*/
- (id) valueForInputKey:(NSString*)key; 

/*
Returns the current value on an output port (identified by its key) of the root patch of the composition.
This method will throw an exception if "key" is invalid.
The type of value returned depends on the type of the output port:
	- NSNumber for Boolean, Index and Number ports
	- NSString for String ports
	- NSColor for Color ports
	- NSImage for Image ports
	- NSDictionary for Structure ports
*/
- (id) valueForOutputKey:(NSString*)key;

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

@end
