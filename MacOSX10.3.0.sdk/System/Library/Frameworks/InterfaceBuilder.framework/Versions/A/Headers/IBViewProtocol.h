// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBViewProtocol.h 
//	Copyright (c) 2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <AppKit/AppKit.h>
#import <InterfaceBuilder/IBEditors.h>
#import <InterfaceBuilder/IBDefines.h>

// --------------------------------------------------------------------------------
//	@protocol IBViewProtocol
// --------------------------------------------------------------------------------
// This protocol describes all the public API a subclass of NSView may need to implement in order to 
// correctly behaves inside IB. NSView implements all those methods.

@protocol IBViewProtocol

// Return the minimum/maximum size of the view if resized from the knob position `position'.
- (NSSize)minimumFrameSizeFromKnobPosition:(IBKnobPosition)position;
- (NSSize)maximumFrameSizeFromKnobPosition:(IBKnobPosition)knobPosition;

// The default implementation sends `setFrame:'.
- (void)placeView:(NSRect)newFrame;

// Return YES to allow the view to be alt-dragged into a matrix.
// The view must provide a cell for the resulting matrix.
- (BOOL)allowsAltDragging;

// Used when dragging colors to views.
- (BOOL)acceptsColor:(NSColor *)color atPoint:(NSPoint)point;
- (void)depositColor:(NSColor *)color atPoint:(NSPoint)point;

// Tracker class Name
- (NSString *)trackerClassNameForEvent:(NSEvent *)event;

// ?
- (float)lineFragmentPadding;

// View that edit themself should return YES to -canEditSelf. NSView returns NO by default but still
// provides a standard implementation of -editSelf:in:
- (BOOL)canEditSelf;
- (void)editSelf:(NSEvent *)theEvent in:(NSView<IBEditors>*)viewEditor;

// Size of the widget shadow
- (IBInset)ibShadowInset;

// Should returns the class of widget (e.g. PushButton, CheckBox, etc)
- (NSString*)ibWidgetType;

// Alternnate minimum Size
- (BOOL)ibHasAlternateMinimumWidth;
- (BOOL)ibHasAlternateMinimumHeight;

- (float)ibAlternateMinimumWidth;
- (float)ibAlternateMinimumHeight;

// Returns YES if view supports auto selection of its deepest elements
- (BOOL)ibSupportsInsideOutSelection;

// Returns YES if view is a container
- (BOOL)ibIsContainer;

- (id)ibNearestTargetForDrag;

//Returns YES if the view supports the display of guides while resizing
- (BOOL)ibShouldShowContainerGuides;

// Returns YES if view wants to redraw as it grows 
- (BOOL)ibSupportsLiveResize;
   
// Base line supports for widget
// baseLineAtIndex is relative to the bottom of the layoutRect (layoutRect.origin.y is not flipped)
- (int)ibNumberOfBaseLine;
- (float)ibBaseLineAtIndex:(int)index;

// Return YES if you want a border to be drawn while the view is resized. Useful for views like TextField or Custom
// that don't have an edge. Default is NO.
- (BOOL)ibDrawFrameWhileResizing;

@end

