/*
	SFChooseIdentityPanel.h
	SecurityInterface
	Copyright (c) 2002-2003, Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFCHOOSEIDENTITYPANEL_H_
#define _SFCHOOSEIDENTITYPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecIdentity.h>

@class SFCertificateView;

/*!
	@class SFChooseIdentityPanel 
    @abstract SFChooseIdentityPanel is a panel and sheet interface that allows a user to pick from a list of identities that exist in the system.
*/

@interface SFChooseIdentityPanel : NSPanel
{
@private
    IBOutlet NSTextField *_panelMessage;
    IBOutlet NSPopUpButton *_identityPopup;
    IBOutlet SFCertificateView *_certificateView;
    IBOutlet NSButton *_cancelButton;	
    IBOutlet NSButton *_okButton;	
    int _indexOfChosenIdentity;
    SecCertificateRef _currCertRefDisplayed;
    NSArray *_identities;
    NSWindow *_parentWindowForSheet;	
    IBOutlet NSWindow *_panel;
    SEL _clientDidEndSelector;
    id _clientDelegate;			
    void *_clientContextInfo;
    void *_reserved_SFChooseIdentityPanel;
}

/*!
	@method sharedChooseIdentityPanel
	@abstract Returns a global instance of SFChooseIdentityPanel.
*/
+ (SFChooseIdentityPanel *)sharedChooseIdentityPanel;

/*!
    @method runModalForIdentities:message:
    @abstract Displays a panel that shows a list of identities in the system. It returns NSOKButton or NSCancelButton. Use the 'identity' method to obtain the identity chosen by the user.
    @param identities An array of SFIdentity objects to choose from.
    @param message Client-defined string to display in the panel.
*/
- (int)runModalForIdentities:(NSArray *)identities message:(NSString *)message;

/*!
  @method beginSheetForWindow:identities:message:modalDelegate:didEndSelector:contextInfo:
    @abstract Displays a sheet version of the SFChooseIdentityPanel. The didEndSelector returnCode will contain either NSOKButton or NSCancelButton.
    @param docWindow The parent window where the sheet appears.
    @param modalDelegate The object that has the didEndSelector method when the sheet goes away.
    @param didEndSelector This method is called when the sheet goes away.
    @param contextInfo A client-defined context.
    @param identities An array of SFIdentity objects to choose from.
    @param message Client-defined string to display in the panel.
    @discussion The didEndSelector should like like:
        - (void)myChooseIdentitySheetDidEnd:(NSWindow *)sheet identity:(SFIdentity *)identity returnCode:(int)returnCode contextInfo:(void *)contextInfo
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo identities:(NSArray *)identities message:(NSString *)message;

/*!
    @method identity
    @abstract Returns the identity that the user chose in the panel.
*/
- (SecIdentityRef)identity;

@end

#endif /* !_SFCHOOSEIDENTITYPANEL_H_ */
