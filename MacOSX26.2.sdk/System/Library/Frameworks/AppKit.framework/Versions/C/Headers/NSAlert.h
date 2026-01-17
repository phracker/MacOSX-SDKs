/*
	NSAlert.h
	Application Kit
	Copyright (c) 1994-2024, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSApplication.h>
#import <AppKit/NSHelpManager.h>
#import <AppKit/NSGraphics.h>

NS_HEADER_AUDIT_BEGIN(nullability, sendability)
APPKIT_API_UNAVAILABLE_BEGIN_MACCATALYST

@class NSTextField, NSPanel, NSWindow, NSImage, NSButton, NSError;
@protocol NSAlertDelegate;

/// The alert styles used by the `alertStyle` property on instances of `NSAlert`.
typedef NS_ENUM(NSUInteger, NSAlertStyle) {
    /// An alert style to be used to warn the user about a current or impending event.
    /// This style should be used when the alert’s content is more severe than `NSAlertStyleInformational` but less than `NSAlertStyleCritical`.
    /// This is the default alert style.
    NSAlertStyleWarning = 0,
    
    /// An alert style to be used to inform the user about a current or impending event.
    /// - Note: Currently, there is no visual difference between informational and warning alerts.
    NSAlertStyleInformational = 1,
    
    /// An alert style to be used to inform the user about a critical event.
    /// Causes the alert’s icon to be badged with a caution icon.
    /// The critical (or “caution”) style should be used sparingly. Using it too frequently diminishes its significance. Use the symbol only when extra attention is really needed, as when confirming an action that might result in unexpected loss of data. Don’t use the symbol for tasks whose only purpose is to overwrite or remove data, such as a save or empty trash.
    NSAlertStyleCritical = 2
};

/* These are additional `NSModalResponse` values used by `NSAlert`’s `-runModal` and `-beginSheetModalForWindow:completionHandler:`.

 By default, `NSAlert` return values are position dependent, with this mapping:
 first (rightmost) button = NSAlertFirstButtonReturn
 second button = NSAlertSecondButtonReturn
 third button = NSAlertThirdButtonReturn
 buttonPosition 3+x = NSAlertThirdButtonReturn + x

 Note that these return values do not apply to an `NSAlert` created via `+alertWithMessageText:defaultButton:alternateButton:otherButton:informativeTextWithFormat:`, which instead uses the same return values as `NSRunAlertPanel`. See `NSAlertDefaultReturn`, etc. in NSPanel.h
 
 If an alert is presented with no buttons added via `-addButtonWithTitle:`, the implicitly-created OK button will return with response code of 0.
 */
static const NSModalResponse NSAlertFirstButtonReturn = 1000;
static const NSModalResponse NSAlertSecondButtonReturn = 1001;
static const NSModalResponse NSAlertThirdButtonReturn = 1002;

/// A modal dialog or sheet attached to a document window.
/// The `NSAlert` class is not designed for subclassing.
NS_SWIFT_UI_ACTOR
@interface NSAlert : NSObject

// MARK: - Creating Alerts

/// Returns an alert initialized from information in an error object.
/// - Parameter error: Error information to display.
/// - Returns: An initialized alert.
/// - Note: The `NSAlert` class extracts the localized error description, recovery suggestion, and recovery options from the error parameter and uses them as the alert’s message text, informative text, and button titles, respectively.
+ (NSAlert *)alertWithError:(NSError *)error;

// MARK: - Accessing Alert Text

/// The text that is displayed prominently in the alert.
/// - Note: Use this string to get the user’s attention and communicate the reason for displaying the alert.
@property (copy) NSString *messageText;

/// The descriptive text that provides more details about the reason for the alert.
/// - Note: The informative text string is displayed below the message text and is less prominent. Use this string to provide additional context about the reason for the alert or about the actions that the user might take.
@property (copy) NSString *informativeText;

// MARK: - Accessing a Custom Alert Icon

/// The custom icon displayed in the alert.
///
/// By default, the image used in an alert is the app icon. If you set this property’s value, your specified custom image is used in place of the app icon.
///
/// If you’ve set a custom alert icon, you can clear it by setting this property’s value to `nil`, which restores use of the app icon for the alert.
///
/// - Note: AppKit may omit the icon from the alert if it’s the app icon and the alert’s context is clear, such as being presented as a sheet on an app window.
@property (null_resettable, strong) NSImage *icon;

// MARK: - Accessing Alert Response Buttons

/// Adds a button with a given title to the alert.
///
/// Buttons should be added from most-to-least prominent. The exact visual arrangement of the buttons is determined by `NSAlert` internally. In general, they are arranged from trailing-to-leading edge when laid out horizontally, and top-to-bottom when laid out vertically, with some exceptions for buttons like “Cancel”.
///
/// The first three buttons are identified by the order in which they are added (not the order in which they may appear visually) as `NSAlertFirstButtonReturn`, `NSAlertSecondButtonReturn`, `NSAlertThirdButtonReturn` in the return-code parameter. Subsequent buttons are identified as `NSAlertThirdButtonReturn` + *n*, where *n* is an integer.
///
/// By default, the first button has a key equivalent of Return, any button with a title of “Cancel” has a key equivalent of Escape, and any button with the title “Don’t Save” has a key equivalent of Command-D (but only if it’s not the first button). You can also assign different key equivalents for the buttons using the `keyEquivalent` method of the `NSButton` class. In addition, you can use the `tag` property of the `NSButton` class to set the alert presentation’s return-code. The framework reserves the use of the button’s `target` and `action`.
///
/// - Parameter title: Title of the button to add to the alert.
/// - Returns: The button that was added to the alert.
- (NSButton *)addButtonWithTitle:(NSString *)title;

/// The array of response buttons for the alert.
/// The buttons are in the order in which they were added, and do not necessarily reflect the order they are arranged visually. The array does not include the default “OK” button that is shown in an alert presented without any buttons added with `-addButtonWithTitle:`.
@property (readonly, copy) NSArray<NSButton *> *buttons;

// MARK: - Configuring Alerts

/// Indicates the alert’s severity level. See the `NSAlertStyle` enumeration for the list of alert style constants.
@property NSAlertStyle alertStyle;

/// Specifies whether the alert has a help button.
///
/// Set this property’s value to `YES` to specify that the alert has a help button, or `NO` to specify it does not.
///
/// When a user clicks an alert’s help button, the alert delegate (`delegate`) receives an `alertShowHelp:` message. The delegate is responsible for displaying the help information related to this particular alert.
///
/// Clicking an alert’s help button can alternately cause the `-openHelpAnchor:inBook:` message to be sent to the app’s help manager with a `nil` book and the anchor specified by the `helpAnchor` property, if any of the following conditions are true:
/// - There is no alert delegate.
/// - The alert delegate does not implement `-alertShowHelp:`.
/// - The alert delegate implements `-alertShowHelp:` but returns `NO`. When this is the case, an exception is raised if no help anchor is set.
@property BOOL showsHelp;

/// The alert’s HTML help anchor used when the user clicks the alert’s help button
@property (nullable, copy) NSHelpAnchorName helpAnchor;

/// The delegate of the receiver, currently only allows for custom help behavior of the alert.
/// For apps linked against 10.12, this property has zeroing weak memory semantics. When linked against an older SDK this back to having `retain` semantics, matching legacy behavior.
@property (nullable, weak) id<NSAlertDelegate> delegate;

/// The accessory view displayed in the alert, placed between the informative text or suppression checkbox (if present) and the response buttons. Before changing the location of the accessory view, first call the `-layout` method.
@property (nullable, strong) NSView *accessoryView API_AVAILABLE(macos(10.5));

/// Specifies that the alert must do immediate layout instead of lazily just before display.
/// Used to indicate that the alert panel should do immediate layout, overriding the default behavior of laying out lazily just before showing panel. Only call this method if wanting to do custom layout after it returns. Call this method only after the alert’s other customization, including setting message and informative text, and adding buttons and an accessory view if needed. Layout changes can be made after this method returns, in particular to adjust the frame of an accessory view. Note that the standard layout of the alert may change in the future, so layout customization should be done with caution.
- (void)layout API_AVAILABLE(macos(10.5));

// MARK: - Displaying Alerts

/// Runs the alert as an app-modal dialog and returns the constant that identifies the button clicked.
- (NSModalResponse)runModal;

/// Specifies whether the alert includes a suppression checkbox, which can be employed to allow a user to opt out of seeing the alert again.
/// The default value of this property is `NO`, which specifies the absence of a suppression checkbox in the alert. Set the value to `YES` to show a suppression checkbox in the alert.
/// By default, a suppression checkbox has the title, “Do not show this message again.” In macOS 11.0 and later, if the alert displays multiple buttons that prompt the user to make a choice, the title is “Do not ask again.” To customize it, use the checkbox’s title property, as follows:
///
///     myAlert.suppressionButton.title = @"Do not show this warning again";
///
/// To create an alert that responds to the selection state of the suppression checkbox, check `myAlert.suppressionButton.state`.
@property BOOL showsSuppressionButton API_AVAILABLE(macos(10.5));

/// The alert’s suppression checkbox. The checkbox may be customized, including the title and the initial state. Additionally, use this method to get the state of the button after the alert is dismissed, which may be stored in user defaults and checked before showing the alert again. In order to show the suppression button in the alert panel, you must set `showsSuppressionButton` to `YES`.
@property (nullable, readonly, strong) NSButton *suppressionButton API_AVAILABLE(macos(10.5));

/// Runs the alert modally as a sheet attached to the specified window.
/// - Parameters:
///   - sheetWindow: The window on which to display the sheet.
///   - handler: The completion handler that gets called when the sheet’s modal session ends.
///
/// This method uses the `NSWindow` sheet methods to display the alert. If the alert has an alert style of `NSCriticalAlertStyle`, it is presented as a critical sheet, which means that it can display on top of other sheets that might already be attached to the window. Otherwise, it is presented--or queued for presentation--as a standard sheet.
/// Note that `-orderOut:` no longer needs to be called in the completion handler. If the alert isn’t  don’t dismiss the alert, it will be done for you after the completion handler finishes.
- (void)beginSheetModalForWindow:(NSWindow *)sheetWindow completionHandler:(void (^ _Nullable)(NSModalResponse returnCode))handler API_AVAILABLE(macos(10.9));

// MARK: - Getting Alert Windows

/// The app-modal panel or document-modal sheet that corresponds to the alert
@property (readonly, strong) NSWindow *window;

@end

/// A set of optional methods implemented by the delegate of an `NSAlert` object to respond to a user’s request for help.
@protocol NSAlertDelegate <NSObject>

@optional

/// Sent to the delegate when the user clicks the alert’s help button. The delegate causes help to be displayed for an alert, directly or indirectly.
/// - Returns: `YES` when the delegate displayed help directly, `NO` otherwise. When `NO` and the alert has a help anchor (`helpAnchor`), the application’s help manager displays help using the help anchor.
/// - Discussion: The delegate implements this method only to override the help-anchor lookup behavior.
- (BOOL)alertShowHelp:(NSAlert *)alert NS_SWIFT_UI_ACTOR;

@end


@interface NSAlert (NSAlertDeprecated)

/* This was intended for use by apps migrating from the C-based API.  This uses alternate return codes that were compatible with this C-based API, but not with modern alerts, see NSAlertDefaultReturn, etc. in NSPanel.h
 Alerts should be created with the -init method and setting properties.
 */
+ (NSAlert *)alertWithMessageText:(nullable NSString *)message defaultButton:(nullable NSString *)defaultButton alternateButton:(nullable NSString *)alternateButton otherButton:(nullable NSString *)otherButton informativeTextWithFormat:(NSString *)format, ... NS_FORMAT_FUNCTION(5,6) API_DEPRECATED("Use -init instead", macos(10.3,10.10));

- (void)beginSheetModalForWindow:(NSWindow *)window modalDelegate:(nullable id)delegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(nullable void *)contextInfo API_DEPRECATED("Use -beginSheetModalForWindow:completionHandler: instead", macos(10.3,10.10));

@end

static const NSAlertStyle NSWarningAlertStyle API_DEPRECATED_WITH_REPLACEMENT("NSAlertStyleWarning", macos(10.3,10.12)) = NSAlertStyleWarning;
static const NSAlertStyle NSInformationalAlertStyle API_DEPRECATED_WITH_REPLACEMENT("NSAlertStyleInformational", macos(10.3,10.12)) = NSAlertStyleInformational;
static const NSAlertStyle NSCriticalAlertStyle API_DEPRECATED_WITH_REPLACEMENT("NSAlertStyleCritical", macos(10.3,10.12)) = NSAlertStyleCritical;

API_UNAVAILABLE_END
NS_HEADER_AUDIT_END(nullability, sendability)
