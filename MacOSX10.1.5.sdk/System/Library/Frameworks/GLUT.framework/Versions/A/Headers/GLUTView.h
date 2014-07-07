
/* Copyright (c) Dietmar Planitzer, 1998 */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */


#import <AppKit/AppKit.h>
#import <AppKit/NSOpenGL.h>
#import "macxglut_private.h"


#define	GLUT_UNKNOWN_VISIBILITY		GLUT_FULLY_COVERED + 1




/* *** types *** */

/* *** GLUT view class *** */

@interface GLUTView : NSOpenGLView
{
@private
	
	NSCursor *							_cursorObj;
        GLUquadricObj *_quadObj;
	
	GLUTKeyboardCallback				_keyboardCallback;
	GLUTKeyboardCallback				_keyUpCallback;
	GLUTMouseCallback					_mouseCallback;
	GLUTMotionCallback				_motionCallback;
	GLUTMotionCallback				_passiveMotionCallback;
	GLUTEntryCallback					_entryCallback;
	GLUTSpecialCallback				_specialCallback;
	GLUTSpecialCallback				_specialUpCallback;
	GLUTDisplayCallback				_displayCallback;
	GLUTReshapeCallback				_reshapeCallback;
	GLUTWindowStatusCallback		_windowStatusCallback;
	GLUTVisibilityCallback			_visibilityCallback;
	
	GLUTSpaceballMotionCallback	_spaceballMotionCallback;
	GLUTSpaceballRotateCallback	_spaceballRotateCallback;
	GLUTSpaceballButtonCallback	_spaceballButtonCallback;
	GLUTButtonBoxCallback			_buttonBoxCallback;
	GLUTDialCallback					_dialCallback;
	GLUTTabletMotionCallback		_tabletMotionCallback;
	GLUTTabletButtonCallback		_tabletButtonCallback;
	GLUTJoystickCallback				_joystickCallback;
	
	struct __vFlags {
		unsigned int						pendingShowHide		: 1;
		unsigned int						doShowOp					: 1;
		unsigned int						pendingPushPop			: 1;
		unsigned int						doPushOp					: 1;
		unsigned int						pendingRedisplay		: 1;
		unsigned int						pendingMove				: 1;
		unsigned int						pendingReshape			: 1;
		unsigned int						forceReshapeCall		: 1;		// forces call of reshapeWithNewSize: after initialization in drawRect:
		unsigned int						isDamaged				: 1;
		unsigned int						modifierFlagsValid	: 1;
		unsigned int						ignoreKeyRepeats		: 1;
		unsigned int						cursor					: 8;
		unsigned int						needsUpdate				: 1;
		unsigned int						isDrawingLocked		: 1;
		unsigned int						reserved0				: 11;
	}										_flags;
	int									_viewStatus;
	int									_viewKey;
	int									_modifierFlags;
	NSTrackingRectTag					_trackingRectTag;
	NSTimeInterval						_pollInterval;
	NSPoint								_keyDownMouseLocation;
	NSPoint								_pos;
	NSSize								_size;
}

- (id)initWithFrame: (NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)pixelFormat;
- (void)dealloc;

		/* accessors */
- (NSPoint)windowPositionRelativeToParent: (BOOL)yesno;
- (NSSize)windowSize;
- (BOOL)isVisible;
- (BOOL)isDamaged;
- (int)modifierFlags;
- (BOOL)ignoreKeyRepeats;
- (void)setIgnoreKeyRepeats: (BOOL)yesno;
- (NSTimeInterval)joystickPollInterval;
- (void)setViewKey: (int)key;
- (int)viewKey;
- (int)visualInfoID;

		/* context */
- (void)makeCurrent;
- (void)makeNotCurrent;
- (void)swapBuffers;

- (void)show;
- (void)hide;

		/* callbacks */
- (void)setKeyboardCallback: (GLUTKeyboardCallback)func isKeyDown: (BOOL)yesno;
- (void)setMouseCallback: (GLUTMouseCallback)func;
- (void)setMotionCallback: (GLUTMotionCallback)func;
- (void)setPassiveMotionCallback: (GLUTMotionCallback)func;
- (void)setEntryCallback: (GLUTEntryCallback)func;
- (void)setSpecialCallback: (GLUTSpecialCallback)func isKeyDown: (BOOL)yesno;
- (void)setDisplayCallback: (GLUTDisplayCallback)func;
- (void)setReshapeCallback: (GLUTReshapeCallback)func;
- (void)setWindowStatusCallback: (GLUTWindowStatusCallback)func;
- (void)setVisibilityCallback: (GLUTVisibilityCallback)func;
- (void)setSpaceballMotionCallback: (GLUTSpaceballMotionCallback)func;
- (void)setSpaceballRotateCallback: (GLUTSpaceballRotateCallback)func;
- (void)setSpaceballButtonCallback: (GLUTSpaceballButtonCallback)func;
- (void)setButtonBoxCallback: (GLUTButtonBoxCallback)func;
- (void)setDialCallback: (GLUTDialCallback)func;
- (void)setTabletMotionCallback: (GLUTTabletMotionCallback)func;
- (void)setTabletButtonCallback: (GLUTTabletButtonCallback)func;
- (void)setJoystickCallback: (GLUTJoystickCallback)func pollInterval: (NSTimeInterval)delay;

		/* cursor */
- (void)setCursor: (int)crsrnum;
- (int)cursor;

		/* window update state */
- (void)setNeedsStateUpdate: (BOOL)yesno;
- (BOOL)needsStateUpdate;

		/* defered operations */
- (void)postRedisplay;
- (void)setPosition: (NSPoint)position;
- (void)setSize: (NSSize)size;
- (void)show;
- (void)hide;
- (void)push;
- (void)pop;
- (void)updateViewState;
	
		/* window status management */
- (int)determineViewStatusIgnoringSiblings: (BOOL)ignoreSiblings;
- (void)updateViewStatus: (int)state;
- (int)viewStatus;

@end
