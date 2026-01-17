/*
    CBIdentityPicker.h
    Collaboration.framework
  
    Copyright (c) 2006-2012 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>


NS_ASSUME_NONNULL_BEGIN

@class NSArray;
@class NSString;
@class NSWindow;
@class CBIdentity;

/* CBIdentityPicker - Runs an Identity Picker panel, the result of which is an array of identities */

    
    /// A `CBIdentityPicker` object allows a user to select identities—for
    /// example, user or group objects—that it wants one or more services or
    /// shared resources to have access to. An identity picker can be displayed
    /// either as an application-modal dialog or as a sheet attached to a
    /// document window. An identity picker returns the selected records to be
    /// added to access control lists using Collaboration. If a selected record
    /// is not a user or group identity, then an identity picker prompts the
    /// user for additional information—such as a password—to promote that
    /// record to a sharing account.
NS_CLASS_AVAILABLE(10_5, NA)
@interface CBIdentityPicker : NSObject {
    @private
    id _reserved[2];
}

/* The title text appears at the top of the panel. The default title is "Select a person to share with:" */

/// The title of the identity picker.
///
/// The value of this property is the title text that appears at the top of the
/// panel. By default, the title is "Select a person to share with:".
@property (nullable, readwrite, nonatomic, copy) NSString *title;

/* Allow the user to select more than one identity at a time. Defaults to NO. */

/// A Boolean value indicating whether the user is allowed to select multiple
/// identities.
///
/// The value of this property is
/// <doc://com.apple.documentation/documentation/objectivec/yes> if the user can
/// select multiple records; otherwise,
/// <doc://com.apple.documentation/documentation/objectivec/no>. The default
/// value is <doc://com.apple.documentation/documentation/objectivec/no>.
@property (readwrite, nonatomic) BOOL allowsMultipleSelection;

/* Run the IdentityPicker as an application-modal panel and return an array of selected CBIdentities. Return NSModalResponseOK or NSModalResponseCancel. */

/// Runs the receiver as an application-modal dialog.
///
/// The receiver may create identities for selected records if necessary.
///
/// - Returns: `NSOKButton` if the user selected OK; otherwise,
/// `NSCancelButton`.
- (NSInteger)runModal;

/* Run the Identity Picker as a sheet.  The didEndSelector will be invoked after the return value is known but before the sheet is dismissed.
   The didEndSelector should have the following signature:
    - (void)identityPickerDidEnd:(CBIdentityPicker *)identityPicker returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
*/

/// Runs the receiver modally as a sheet attached to a specified window.
///
/// The `didEndSelector` parameter is a selector that takes three arguments. The
/// corresponding method should have a declaration modeled on the following
/// example:
///
/// ```swift
///  - (void)identityPickerDidEnd:(CBIdentityPicker *)identityPicker returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
/// ```
///
/// where the `identityPicker` argument is the identity picker object, the
/// `returnCode` argument is the button the user clicked, and `contextInfo` is
/// the same `contextInfo` argument that was passed in the original message.
///
/// - Parameters:
///   - window: The parent window for the sheet.
///
///   - delegate: The delegate for the modal session.
///
///   - didEndSelector: A message sent to the delegate after the user responds but
/// before the sheet is dismissed.
///
///   - contextInfo: Contextual data passed to the delegate in the
/// `didEndSelector` message.
- (void)runModalForWindow:(NSWindow *)window modalDelegate:(nullable id)delegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(nullable void *)contextInfo NS_DEPRECATED(10_5, 10_11, NA, NA, "Use runModalForWindow:completionHandler: instead.");

/* Run the Identity Picker as a sheet.  The completionHandler will be invoked after the return value is known but before the sheet is dismissed. */

/// Runs the identity picker modally as a sheet attached to a specified window.
///
/// - Parameters:
///   - window: The parent window for the sheet.
///
/// - completionHandler: The handler to run after the return value is known, but
/// before the sheet is dismissed.
- (void)runModalForWindow:(NSWindow *)window completionHandler:(nullable void (^)(NSModalResponse returnCode))completionHandler;

/* Return the array of selected identities (NSArray of CBIdentity*) */

/// The array of identities (represented by `CBIdentity` objects) selected using
/// the identity picker.
@property (readonly, nonatomic) NSArray<CBIdentity *> *identities;

@end

NS_ASSUME_NONNULL_END
