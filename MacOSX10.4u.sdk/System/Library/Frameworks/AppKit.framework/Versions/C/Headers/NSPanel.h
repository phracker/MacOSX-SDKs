/*
	NSPanel.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/NSWindow.h>

/*
 * In the following two functions, msg may be a printf-like message with
 * the arguments tacked onto the end.  Thus, to get a '%' in your message,
 * you must use '%%'
 */

APPKIT_EXTERN int NSRunAlertPanel(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);
APPKIT_EXTERN int NSRunInformationalAlertPanel(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);
APPKIT_EXTERN int NSRunCriticalAlertPanel(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);

/*
** The NSRunAlertPanelRelativeToWindow variants are deprecated.  
** Please use the corresponding NSBeginAlertSheet() function instead.
*/
APPKIT_EXTERN int NSRunAlertPanelRelativeToWindow(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...);
APPKIT_EXTERN int NSRunInformationalAlertPanelRelativeToWindow(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...);
APPKIT_EXTERN int NSRunCriticalAlertPanelRelativeToWindow(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...);

/*
**  Present a sheet alert on the given window.  When the modal session is ended, but before the sheet is dismissed,
** the didEndSelector will be invoked in the modalDelegate.  After the sheet
** is dismissed, the didDismissSelector will be invoked. Typically, you will want to implement the didEndSelector but you may
** pass NULL for the didDismissSelector.
** The methods should have the following signatures:
** - (void)sheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
** - (void)sheetDidDismiss:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
**
*/
APPKIT_EXTERN void NSBeginAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msg, ...);
APPKIT_EXTERN void NSBeginInformationalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msg, ...);
APPKIT_EXTERN void NSBeginCriticalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msg, ...);

APPKIT_EXTERN id NSGetAlertPanel(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);
APPKIT_EXTERN id NSGetInformationalAlertPanel(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);
APPKIT_EXTERN id NSGetCriticalAlertPanel(NSString *title, NSString *msg, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...);

APPKIT_EXTERN void NSReleaseAlertPanel(id panel);

/*
 * NSRunAlertPanel() return values (also returned by runModalSession: when
 * the modal session is run with a panel returned by NSGetAlertPanel()).
 */

enum {
    NSAlertDefaultReturn		= 1,
    NSAlertAlternateReturn		= 0,
    NSAlertOtherReturn			= -1,
    NSAlertErrorReturn			= -2
};

enum {
    NSOKButton				= 1,
    NSCancelButton			= 0
};

// Panel specific styleMask
enum {
    NSUtilityWindowMask			= 1 << 4,
    NSDocModalWindowMask 		= 1 << 6
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
enum {
    NSNonactivatingPanelMask		= 1 << 7	// specify a panel that does not activate owning application
};
#endif

@interface NSPanel : NSWindow
{
/*All instance variables are private*/
}

- (BOOL)isFloatingPanel;
- (void)setFloatingPanel:(BOOL)flag;
- (BOOL)becomesKeyOnlyIfNeeded;
- (void)setBecomesKeyOnlyIfNeeded:(BOOL)flag;
- (BOOL)worksWhenModal;
- (void)setWorksWhenModal:(BOOL)flag;

@end

