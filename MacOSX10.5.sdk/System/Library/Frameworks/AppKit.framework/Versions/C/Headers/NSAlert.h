/*
	NSAlert.h
	Application Kit
	Copyright (c) 1994-2007, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSGraphics.h>
@class NSTextField, NSPanel, NSArray, NSWindow, NSImage, NSButton, NSError;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3

// The default alert style is NSAlertWarningStyle.  NSAlertCriticalStyle should be reserved for critical alerts and will cause the icon to be badged with a caution icon.
enum {
    NSWarningAlertStyle = 0,
    NSInformationalAlertStyle = 1,
    NSCriticalAlertStyle = 2
};
typedef NSUInteger NSAlertStyle;

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
    CGFloat _buttonSpacing;
    CGFloat _buttonPadding;
    CGFloat _messagePadding;
    CGFloat _buttonSpacingMaxX;
    CGFloat _buttonSpacingY;
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
    BOOL _layoutDone;
    BOOL _showsHelp;
    BOOL _showsSuppressionButton;
    BOOL reserved;
    id _suppressionButton;
    id _accessoryView;
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
// setTag:(NSInteger)tag;	setting a tag on a button will cause that tag to be the button's return value
// Note that we reserve the use of the tag for this purpose.  We also reserve the use of the target and the action
// by default, the first button has a key equivalent of return which implies a pulsing default button, the button named "Cancel", if any, has a key equivalent of escape, and the button named "Don't Save", if any, has a key equivalent of cmd-d.  The following methods can be used to customize key equivalents.
// setKeyEquivalent:(NSString *)charCode:
// setKeyEquivalentModifierMask:(NSUInt)mask;


// -setShowsHelp:YES adds a help button to the alert panel. When the help button is pressed, the delegate is first consulted.  If the delegate does not implement alertShowHelp: or returns NO, then -[NSHelpManager openHelpAnchor:inBook:] is called with a nil book and the anchor specified by -setHelpAnchor:, if any.  An exception will be raised if the delegate returns NO and there is no help anchor set.
- (void)setShowsHelp:(BOOL)showsHelp;
- (BOOL)showsHelp;

- (void)setHelpAnchor:(NSString *)anchor;
- (NSString *)helpAnchor;

- (void)setAlertStyle:(NSAlertStyle)style;
- (NSAlertStyle)alertStyle;

- (void)setDelegate:(id)delegate;
- (id)delegate;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
/* -setShowsSuppressionButton: indicates whether or not the alert should contain a suppression checkbox.  The default is NO.  This checkbox is typically used to give the user an option to not show this alert again.  If shown, the suppression button will have a default localized title similar to @"Do not show this message again".  You can customize this title using [[alert suppressionButton] setTitle:].  When the alert is dismissed, you can get the state of the suppression button, using [[alert suppressionButton] state] and store the result in user defaults, for example.  This setting can then be checked before showing the alert again.  By default, the suppression button is positioned below the informative text, and above the accessory view (if any) and the alert buttons, and left-aligned with the informative text.  However do not count on the placement of this button, since it might be moved if the alert panel user interface is changed in the future. If you need a checkbox for purposes other than suppression text, it is recommended you create your own using an accessory view.
*/
- (void)setShowsSuppressionButton:(BOOL)flag;
- (BOOL)showsSuppressionButton;

/* -suppressionButton returns a suppression button which may be customized, including the title and the initial state.  You can also use this method to get the state of the button after the alert is dismissed, which may be stored in user defaults and checked before showing the alert again.  In order to show the suppression button in the alert panel, you must call -setShowsSuppressionButton:YES.
*/
- (NSButton *)suppressionButton;


/* -setAccessoryView: sets the accessory view displayed in the alert panel.  By default, the accessory view is positioned below the informative text and the suppression button (if any) and above the alert buttons, left-aligned with the informative text.  If you want to customize the location of the accessory view, you must first call -layout.  See the discussion of -layout for more information.
*/
- (void)setAccessoryView:(NSView *)view;
- (NSView *)accessoryView;

/* -layout can be used to indicate that the alert panel should do immediate layout, overriding the default behavior of laying out lazily just before showing panel.  You should only call this method if you want to do your own custom layout after it returns.  You should call this method only after you have finished with NSAlert customization, including setting message and informative text, and adding buttons and an accessory view if needed.  You can make layout changes after this method returns, in particular to adjust the frame of an accessory view.  Note that the standard layout of the alert may change in the future, so layout customization should be done with caution.
*/
- (void)layout;

#endif

// Run the alert as an application-modal panel and return the result
- (NSInteger)runModal;

// Run the alert as a sheet.  didEndSelector will be invoked after the return value is known but before the sheet is dismissed.  Callers that want to dismiss the sheet themselves before carrying out an action in response to the return value should do so by calling orderOut: on [alert window].  The didEndSelector should have the following signature:
//- (void)alertDidEnd:(NSAlert *)alert returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;

- (void)beginSheetModalForWindow:(NSWindow *)window modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

// return the application-modal panel or the document-modal sheet corresponding to this alert
- (id)window;

@end

@interface NSObject(NSAlertDelegate)
// the delegate should implement this if custom help behavior is required.
- (BOOL)alertShowHelp:(NSAlert *)alert;
@end

#endif
