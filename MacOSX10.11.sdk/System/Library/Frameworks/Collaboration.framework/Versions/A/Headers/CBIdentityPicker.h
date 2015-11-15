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

NS_CLASS_AVAILABLE(10_5, NA)
@interface CBIdentityPicker : NSObject {
    @private
    id _reserved[2];
}

/* The title text appears at the top of the panel. The default title is "Select a person to share with:" */
@property (nullable, readwrite, nonatomic, copy) NSString *title;

/* Allow the user to select more than one identity at a time. Defaults to NO. */
@property (readwrite, nonatomic) BOOL allowsMultipleSelection;

/* Run the IdentityPicker as an application-modal panel and return an array of selected CBIdentities. Return NSModalResponseOK or NSModalResponseCancel. */
- (NSInteger)runModal;

/* Run the Identity Picker as a sheet.  The didEndSelector will be invoked after the return value is known but before the sheet is dismissed.
   The didEndSelector should have the following signature:
    - (void)identityPickerDidEnd:(CBIdentityPicker *)identityPicker returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
*/
- (void)runModalForWindow:(NSWindow *)window modalDelegate:(nullable id)delegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(nullable void *)contextInfo NS_DEPRECATED(10_5, 10_11, NA, NA "Use runModalForWindow:completionHandler: instead.");

/* Run the Identity Picker as a sheet.  The completionHandler will be invoked after the return value is known but before the sheet is dismissed. */
- (void)runModalForWindow:(NSWindow *)window completionHandler:(nullable void (^)(NSModalResponse returnCode))completionHandler;

/* Return the array of selected identities (NSArray of CBIdentity*) */
@property (readonly, nonatomic) NSArray<CBIdentity *> *identities;

@end

NS_ASSUME_NONNULL_END
