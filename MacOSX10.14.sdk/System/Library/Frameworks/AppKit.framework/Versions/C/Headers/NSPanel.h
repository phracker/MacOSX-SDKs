/*
    NSPanel.h
    Application Kit
    Copyright (c) 1994-2018, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSWindow.h>

@interface NSPanel : NSWindow

@property (getter=isFloatingPanel) BOOL floatingPanel;
@property BOOL becomesKeyOnlyIfNeeded;
@property BOOL worksWhenModal;

@end


/* Deprecated API */

APPKIT_EXTERN NSInteger NSRunAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0, "Use NSAlert, and present it with -[NSAlert beginSheetModalForWindow:completionHandler:] instead");
APPKIT_EXTERN NSInteger NSRunInformationalAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0, "Use NSAlert with a style of NSAlertStyleInformational, and present it with -[NSAlert beginSheetModalForWindow:completionHandler:] instead");
APPKIT_EXTERN NSInteger NSRunCriticalAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0, "Use NSAlert with a style of NSAlertStyleCritical, and present it with -[NSAlert beginSheetModalForWindow:completionHandler:] instead");

APPKIT_EXTERN NSInteger NSRunAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");
APPKIT_EXTERN NSInteger NSRunInformationalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert with a style of NSAlertStyleInformational, and present it with -[NSAlert runModal] instead");
APPKIT_EXTERN NSInteger NSRunCriticalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert with a style of NSAlertStyleCritical, and present it with -[NSAlert runModal] instead");

APPKIT_EXTERN void NSBeginAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...) NS_FORMAT_FUNCTION(10,11) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert, and present it with -[NSAlert beginSheetModalForWindow:completionHandler:] instead");
APPKIT_EXTERN void NSBeginInformationalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...)NS_FORMAT_FUNCTION(10,11) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert with a style of NSAlertStyleInformational, and present it with -[NSAlert beginSheetModalForWindow:completionHandler:] instead");
APPKIT_EXTERN void NSBeginCriticalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...) NS_FORMAT_FUNCTION(10,11) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert with a style of NSAlertStyleCritical, and present it with -[NSAlert beginSheetModalForWindow:completionHandler:] instead");
APPKIT_EXTERN id NSGetAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert");
APPKIT_EXTERN id NSGetInformationalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert with a style of NSAlertStyleInformational instead");
APPKIT_EXTERN id NSGetCriticalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert with a style of NSAlertStyleCritical instead");
APPKIT_EXTERN void NSReleaseAlertPanel(id panel) NS_DEPRECATED_MAC(10_0, 10_10, "Use NSAlert instead");

/*
 These constants are used by deprecated NSRunAlertPanel() and NSGetAlertPanel() functions.
 Modern NSAlert API uses NSAlertFirstButtonReturn, etc.
 */
enum {
    NSAlertDefaultReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn with an NSAlert presentation instead") = 1,
    NSAlertAlternateReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn and other NSModalResponses with an NSAlert presentation instead") = 0,
    NSAlertOtherReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn and other NSModalResponses with an NSAlert presentation instead") = -1,
    NSAlertErrorReturn NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSAlertFirstButtonReturn and other NSModalResponses with an NSAlert presentation instead") = -2
};
enum {
    NSOKButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSModalResponseOK", 10_0, 10_10) = NSModalResponseOK,
    NSCancelButton NS_DEPRECATED_WITH_REPLACEMENT_MAC("NSModalResponseCancel", 10_0, 10_10) = NSModalResponseCancel,
};
