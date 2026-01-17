/*
    CBIdentityPicker.h
    Collaboration.framework
  
    Copyright 2006 Apple Computer. All rights reserved.
*/

#import <Foundation/NSObject.h>


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5

@class NSArray;
@class NSString;
@class NSWindow;

/* CBIdentityPicker - Runs an Identity Picker panel, the result of which is an array of identities */

@interface CBIdentityPicker : NSObject {
    @private
    id _reserved[2];
}

/* The title text appears at the top of the panel. The default title is "Select a person to share with:" */
- (void)setTitle:(NSString *)title;
- (NSString *)title;

/* Allow the user to select more than one identity at a time. Defaults to NO. */
- (void)setAllowsMultipleSelection:(BOOL)flag;
- (BOOL)allowsMultipleSelection;

/* Run the IdentityPicker as an application-modal panel and return an array of selected CBIdentities. Return NSOKButton or NSCancelButton. */
- (NSInteger)runModal;

/* Run the Identity Picker as a sheet.  The didEndSelector will be invoked after the return value is known but before the sheet is dismissed.
   The didEndSelector should have the following signature:
    - (void)identityPickerDidEnd:(CBIdentityPicker *)identityPicker returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
*/
- (void)runModalForWindow:(NSWindow *)window modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

/* Return the array of selected identities (NSArray of CBIdentity*) */
- (NSArray *)identities;

@end

#endif
