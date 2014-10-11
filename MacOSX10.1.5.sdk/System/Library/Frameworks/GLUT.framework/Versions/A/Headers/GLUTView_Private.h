
/* Copyright (c) Dietmar Planitzer, 1998 */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */


#import <AppKit/AppKit.h>
#import "GLUTView.h"


NSOpenGLContext *globalGLContext(void);

/* *** GLUTView(GLUTPrivate) category *** */

@interface GLUTView(GLUTPrivate)

- (GLUquadricObj *)_getQuadObj;
- (BOOL)isFlipped;
- (BOOL)isOpaque;
- (void)resizeWithOldSuperviewSize:(NSSize)oldFrameSize;
- (void)didAddSubview:(NSView *)subview;
- (void)willRemoveSubview:(NSView *)subview;
- (void)reshapeWithNewSize: (NSSize)newFrameSize;

	/* drawing */
- (void)drawRect: (NSRect)aRect;
- (void)_recursivelyUnlockDrawing;

	/* event handling */
- (void)keyDown: (NSEvent *)theEvent;
- (void)mouseDown: (NSEvent *)theEvent;
- (void)mouseUp: (NSEvent *)theEvent;
- (void)mouseDragged: (NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)rightMouseDown: (NSEvent *)theEvent;
- (void)rightMouseUp: (NSEvent *)theEvent;
- (void)rightMouseDragged: (NSEvent *)theEvent;
- (void)mouseEntered:(NSEvent *)theEvent;
- (void)mouseExited:(NSEvent *)theEvent;

- (void)_mouseDown:(NSEvent *)theEvent mouseButton: (int)button;
- (void)_mouseUp:(NSEvent *)theEvent mouseButton: (int)button;
- (void)_mouseDragged:(NSEvent *)theEvent mouseButton: (int)button;
- (void)_updateModifierFlags: (NSEvent *)theEvent;
- (int)_mapNativeKeyCodeToGLUTCode: (unichar)unicodeKey isAscii: (BOOL *)isascii;
- (void)_updateTrackingRects: (NSNotification *)notification;
	
	/* cursors */
- (void)resetCursorRects;
- (NSCursor *)_unvisibleCursor;

	/* window status */

+ (NSArray *)arrayWithWindowsContainedOrIntersectedByRect: (NSRect)screenRect;
+ (void)walkWindowStackStartingWithView: (GLUTView *)refView ignoreSiblings: (BOOL)ignoreSiblings;
- (void)_recursivelyMarkAsVisibilityUnknown;
- (void)_recursivelyMarkAsHidden;
- (void)_recursivelyUpdateState:sender;

	/* NSWindow delegate methods */
- (void)windowWillMiniaturize:(NSNotification *)notification;
- (void)windowDidDeminiaturize:(NSNotification *)notification;
- (void)windowWillMove:(NSNotification *)notification;
- (void)windowDidMove:(NSNotification *)notification;
- (void)windowDidExpose:(NSNotification *)notification;
	
	/* Actions */
#if defined(INTERCEPTOR_HATES_EPS)
- (NSWindow *)_windowWithTIFFInsideRect: (NSRect)rect;
- (IBAction)print: (id)sender;
# ifndef WIN32
- (IBAction)fax:(id)sender;
# endif
#endif

@end
