//
//  JRSUIControl.h
//  Copyright 2011-2015 Apple Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>


typedef CFTypeRef JRSUIRendererRef;

/* -----------------------------------------------------------------------------
 
 JRSUIRendererCreate
 
 Summary:	Creates an instance of a UI renderer.
 
 Returns:
 - a reference to a UI renderer which is used to render and measure controls. It is the responsibility of the caller to release the renderer when it is no longer needed. The renderer must be disposed with JRSUIRendererRelease(). The renderer is a CFType, so it may be put into collections, CFRetain()'d and CFRelease()'d.
 
 ----------------------------------------------------------------------------- */
JRSUIRendererRef JRSUIRendererCreate();

/* -----------------------------------------------------------------------------
 
 JRSUIRendererRelease
 
 Summary:	Disposes of an instance of a UI renderer.
 
 Parameters:
 - renderer: A renderer to dispose of.
 
 ----------------------------------------------------------------------------- */
void JRSUIRendererRelease(JRSUIRendererRef renderer);



typedef CFTypeRef JRSUIControlRef;

/* -----------------------------------------------------------------------------
 
 JRSUIControlCreate
 
 Summary:	Creates an instance of a UI control.
 
 Parameters:
 - isFlipped: determines if the UI control should be rendered and measured using a flipped coordinate system.
 
 Returns:
 - a reference to a UI control which contains all of the properties of a specific UI component. It is the responsibility of the caller to release the control when it is no longer needed. The control must be disposed with JRSUIControlRelease(). The control is a CFType, so it may be put into collections, CFRetain()'d and CFRelease()'d.
 
 ----------------------------------------------------------------------------- */
JRSUIControlRef JRSUIControlCreate(Boolean isFlipped);

/* -----------------------------------------------------------------------------
 
 JRSUIControlRelease
 
 Summary:	Disposes of an instance of a UI control.
 
 Parameters:
 - control: A control to dispose of.
 
 ----------------------------------------------------------------------------- */
void JRSUIControlRelease(JRSUIControlRef control);


/* -----------------------------------------------------------------------------
 
 JRSUIControlDraw
 
 Summary:	Draws a UI element.
 
 Discussion: Any caching of UI drawing should be disposed upon receiving a NSSystemColorsDidChangeNotification notification.
 
 Parameters
 - renderer: The renderer that will do the drawing.
 - control: The control properties which represent the UI control to draw.
 - context: The CG context in which to draw.
 - bounds: The bounds in which to draw.
 
 ----------------------------------------------------------------------------- */
void JRSUIControlDraw(JRSUIRendererRef renderer, JRSUIControlRef control, CGContextRef context, CGRect bounds);
