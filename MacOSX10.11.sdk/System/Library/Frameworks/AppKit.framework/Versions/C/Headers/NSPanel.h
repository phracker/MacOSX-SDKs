/*
    NSPanel.h
    Application Kit
    Copyright (c) 1994-2015, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSWindow.h>

// Panel specific styleMask options
enum {
    NSUtilityWindowMask			= 1 << 4,
    NSDocModalWindowMask 		= 1 << 6,
    NSNonactivatingPanelMask		= 1 << 7,           // specify a panel that does not activate owning application
    NSHUDWindowMask NS_ENUM_AVAILABLE_MAC(10_6) = 1 << 13   // specify a heads up display panel
};

@interface NSPanel : NSWindow {

}

@property (getter=isFloatingPanel) BOOL floatingPanel;
@property BOOL becomesKeyOnlyIfNeeded;
@property BOOL worksWhenModal;

@end





/*
 ** The NSRunAlertPanelRelativeToWindow variants are deprecated.
 ** Please use the corresponding NSBeginAlertSheet() function instead.
 */
APPKIT_EXTERN NSInteger NSRunAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0);
APPKIT_EXTERN NSInteger NSRunInformationalAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0);
APPKIT_EXTERN NSInteger NSRunCriticalAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0);


/*
 These functions are deprecated in 10.9 and will be formally deprecated in the following release
 NSAlert should be used instead
 * In the following three functions, msg may be a printf-like message with
 * the arguments tacked onto the end.  Thus, to get a '%' in your message,
 * you must use '%%'
 */
APPKIT_EXTERN NSInteger NSRunAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN NSInteger NSRunInformationalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN NSInteger NSRunCriticalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");

/*
 These functions are deprecated in 10.9 and will be formally deprecated in the following release
 NSAlert should be used instead.
 **  Present a sheet alert on the given window.  When the modal session is ended, but before the sheet is dismissed,
 ** the didEndSelector will be invoked in the modalDelegate.  After the sheet
 ** is dismissed, the didDismissSelector will be invoked. Typically, you will want to implement the didEndSelector but you may
 ** pass NULL for the didDismissSelector.
 ** The methods should have the following signatures:
 ** - (void)sheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
 ** - (void)sheetDidDismiss:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
 **
 */
APPKIT_EXTERN void NSBeginAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...) NS_FORMAT_FUNCTION(10,11) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN void NSBeginInformationalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...)NS_FORMAT_FUNCTION(10,11) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN void NSBeginCriticalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...) NS_FORMAT_FUNCTION(10,11) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN id NSGetAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN id NSGetInformationalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN id NSGetCriticalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN void NSReleaseAlertPanel(id panel) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");


/*
 These constants are deprecated in 10.9 and will be formally deprecated in the following release
 These constants are used by deprecated NSRunAlertPanel() and NSGetAlertPanel()functions.
 Modern NSAlert API uses NSAlertFirstButtonReturn, etc.
 */
enum {
    NSAlertDefaultReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn, etc instead") = 1,
    NSAlertAlternateReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn, etc instead") = 0,
    NSAlertOtherReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn, etc instead") = -1,
    NSAlertErrorReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn, etc instead") = -2
};
enum {
    NSOKButton NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSModalResponseOK instead") = 1, // NSModalResponseOK should be used instead (in NSWindow)
    NSCancelButton NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSModalResponseCancel instead") = 0  // NSModalResponseCancel should be used instead (in NSWindow)
};
