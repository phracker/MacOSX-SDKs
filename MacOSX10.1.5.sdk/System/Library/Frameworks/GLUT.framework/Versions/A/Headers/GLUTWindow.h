
/* Copyright (c) Dietmar Planitzer, 1998 */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */


#import <AppKit/AppKit.h>
#import "macxglut_private.h"






/* *** GLUT window class *** */

@class GLUTView;
@class GLUTVisual;
@class GLUTOverlay;


@interface GLUTWindow : NSWindow
{
@private
		
	GLUTView *				_view;							/* weak ref */
	struct __gwFlags {
		unsigned int			pendingShowHide	: 1;
		unsigned int			doShowOp				: 1;
		unsigned int			pendingPushPop		: 1;
		unsigned int			doPushOp				: 1;
		unsigned int			pendingMove			: 1;
		unsigned int			pendingReshape		: 1;
		unsigned int			pendingFullScreen	: 1;
		unsigned int			pendingIconify		: 1;
		unsigned int			reserved0			: 8;
	}						_flags;
	int					_windowKey;
    NSPoint				Xpos;
    NSSize				Xsize;
}

- (id)initWithTitle: (NSString *)title pixelFormat:(NSOpenGLPixelFormat *)pixelFormat gameMode:(BOOL)isGameMode;
- (void)dealloc;

- (void)makeKeyAndOrderFront: (id)sender;
- (BOOL)canBecomeKeyWindow;

		/* root window specific attributes */
- (void)iconify;
- (void)updateWindowState;
- (void)setPosition: (NSPoint)position;
- (void)setSize: (NSSize)size;
- (void)setToFullScreen;
- (void)notifyPushPop:(BOOL)push;
- (void)notifyShowHide:(BOOL)show;
@end
