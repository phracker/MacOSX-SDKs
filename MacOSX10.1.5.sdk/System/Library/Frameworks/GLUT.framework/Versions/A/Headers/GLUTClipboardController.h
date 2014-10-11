
/* Copyright (c) Planitzer Dietmar, 1998. */

/* This program is freely distributable without licensing fees
   and is provided without guarantee or warrantee expressed or
   implied. This program is -not- in the public domain. */


#import <AppKit/AppKit.h>


/* *** class interface *** */

@interface GLUTClipboardController : NSWindowController
{
	IBOutlet NSScrollView *		_scrollView;
	IBOutlet NSTextField *		_infoText;
				int					_lastChangeCount;		/* PBoards change count when we created the last view */
				BOOL					_firstTime;
}

- (id)init;

- (void)windowDidLoad;

- (IBAction)toggleWindow:(id)sender;
- (BOOL)validateMenuItem:(NSMenuItem *)anItem;

- (BOOL)isClipboardWindowVisible;

- (void)updateClipboardWindow;

@end
