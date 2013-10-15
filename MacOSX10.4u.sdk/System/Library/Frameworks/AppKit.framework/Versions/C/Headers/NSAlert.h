/*
	NSAlert.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSGraphics.h>
@class NSTextField, NSPanel, NSArray, NSWindow, NSImage, NSButton, NSError;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

// The default alert style is NSAlertWarningStyle.  NSAlertCriticalStyle should be reserved for critical alerts and will cause the icon to be badged with a caution icon.
typedef enum NSAlertStyle {
    NSWarningAlertStyle = 0,
    NSInformationalAlertStyle = 1,
    NSCriticalAlertStyle = 2
} NSAlertStyle;

@interface NSAlert : NSObject
{
    @private
    /*All instance variables are private*/
    NSTextField *_informationField;
    id  _first;
    id  _second;
    id  _third;
    NSArray *_buttons;
    NSPanel *_panel;
    id  _messageField;
    id  _imageView;
    NSSize _minButtonSize;
    float _buttonSpacing;
    float _buttonPadding;
    float _messagePadding;
    float _buttonSpacingMaxX;
    float _buttonSpacingY;
    id _modalDelegate;
    NSWindow *_docWindow;
    SEL _didEndSelector;
    SEL _didDismissSelector;
    NSImage *_unbadgedImage;
    NSSize _defaultPanelSize;
    id _helpButton;
    id _delegate;
    NSAlertStyle _alertStyle;
    id _helpAnchor;
    BOOL _useNSLayout;
    BOOL _showsHelp;
    BOOL reserved[2];
    id reserved1;
    id reserved2;
}

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

/* Given an NSError, create an NSAlert that can be used to present the error to the user. The error's localized description, recovery suggestion, and recovery options will be used to set the alert's message text, informative text, and button titles, respectively.
*/
+ (NSAlert *)alertWithError:(NSError *)error;

#endif

// the following class method is for use by apps migrating from the C-based API.  Note that this returns an NSAlert that is equivalent to the one created in NSRunAlertPanel, so the layout, button return values, and key equivalents are the same as for the C-based API.
+ (NSAlert *)alertWithMessageText:(NSString *)message defaultButton:(NSString *)defaultButton alternateButton:(NSString *)alternateButton otherButton:(NSString *)otherButton informativeTextWithFormat:(NSString *)format, ...;

- (void)setMessageText:(NSString *)messageText;
- (void)setInformativeText:(NSString *)informativeText;

- (NSString *)messageText;
- (NSString *)informativeText;

// customize the icon.  By default uses the image named NSApplicationIcon
- (void)setIcon:(NSImage *)icon;
- (NSImage *)icon;

// customize the buttons in the alert panel
// buttons are added from right to left (for left to right languages)
- (NSButton *)addButtonWithTitle:(NSString *)title;
// get the buttons, where the rightmost button is at index 0
- (NSArray *)buttons;

// by default, NSAlert return values are position dependent, with this mapping:
// first (rightmost) button = NSAlertFirstButtonReturn
// second button = NSAlertSecondButtonReturn
// third button = NSAlertThirdButtonReturn
// buttonPosition 3+x = NSAlertThirdButtonReturn + x

enum {
	NSAlertFirstButtonReturn	= 1000,
	NSAlertSecondButtonReturn	= 1001,
	NSAlertThirdButtonReturn	= 1002
};

// The following method can be used to customize return values for buttons
// setTag:(int)tag;	setting a tag on a button will cause that tag to be the button's return value
// Note that we reserve the use of the tag for this purpose.  We also reserve the use of the target and the action
// by default, the first button has a key equivalent of return which implies a pulsing default button, the button named "Cancel", if any, has a key equivalent of escape, and the button named "Don't Save", if any, has a key equivalent of cmd-d.  The following methods can be used to customize key equivalents.
// setKeyEquivalent:(NSString *)charCode:
// setKeyEquivalentModifierMask:(unsigned int)mask;


// -setShowsHelp:YES adds a help button to the alert panel. When the help button is pressed, the delegate is first consulted.  If the delegate does not implement alertShowHelp: or returns NO, then -[NSHelpManager openHelpAnchor:inBook:] is called with a nil book and the anchor specified by -setHelpAnchor:, if any.  An exception will be raised if the delegate returns NO and there is no help anchor set.
- (void)setShowsHelp:(BOOL)showsHelp;
- (BOOL)showsHelp;

- (void)setHelpAnchor:(NSString *)anchor;
- (NSString *)helpAnchor;

- (void)setAlertStyle:(NSAlertStyle)style;
- (NSAlertStyle)alertStyle;

- (void)setDelegate:(id)delegate;
- (id)delegate;

// Run the alert as an application-modal panel and return the result
- (int)runModal;

// Run the alert as a sheet.  didEndSelector will be invoked after the return value is known but before the sheet is dismissed.  Callers that want to dismiss the sheet themselves before carrying out an action in response to the return value should do so by calling orderOut: on [alert window].  The didEndSelector should have the following signature:
//- (void)alertDidEnd:(NSAlert *)alert returnCode:(int)returnCode contextInfo:(void *)contextInfo;

- (void)beginSheetModalForWindow:(NSWindow *)window modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

// return the application-modal panel or the document-modal sheet corresponding to this alert
- (id)window;

@end

@interface NSObject(NSAlertDelegate)
// the delegate should implement this if custom help behavior is required.
- (BOOL)alertShowHelp:(NSAlert *)alert;
@end

#endif
