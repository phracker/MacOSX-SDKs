/*
	SFChooseIdentityPanel.h
	SecurityInterface
	Copyright (c) 2002-2004 Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFCHOOSEIDENTITYPANEL_H_
#define _SFCHOOSEIDENTITYPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecIdentity.h>

@class SFCertificateView;

/*!
	@class SFChooseIdentityPanel 
    @abstract SFChooseIdentityPanel is a panel and sheet interface that allows a user to select an identity from a list.
*/

@interface SFChooseIdentityPanel : NSPanel
{
@private
	/* All instance variables are private */
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
	id _reserved_SFChooseIdentityPanel;
}

/*!
	@method sharedChooseIdentityPanel
	@abstract Returns a shared instance of SFChooseIdentityPanel.
	@discussion If your application can display multiple SFChooseIdentityPanels at once,
	you should allocate (alloc) and initialize (init) separate object instances instead of using this class method.
*/
+ (SFChooseIdentityPanel *)sharedChooseIdentityPanel;

/*!
    @method runModalForIdentities:message:
    @abstract Displays a supplied list of identities in a modal panel, returning NSOKButton or NSCancelButton when dismissed.
	Use the -identity method to subsequently obtain the identity chosen by the user.
    @param identities An array of SecIdentityRef objects, usually obtained from an identity search (see <Security/SecIdentitySearch.h>).
    @param message Client-defined message string to display in the panel.
*/
- (int)runModalForIdentities:(NSArray *)identities message:(NSString *)message;

/*!
	@method beginSheetForWindow:modalDelegate:didEndSelector:contextInfo:identities:message:
	@abstract Displays a sheet version of the SFChooseIdentityPanel. The didEndSelector returnCode will contain either NSOKButton or NSCancelButton.
	@param docWindow The parent window to which the sheet is attached.
	@param modalDelegate The object whose didEndSelector method will be called when the sheet is dismissed.
	@param didEndSelector This method is called when the sheet is dismissed.
	@param contextInfo Client-defined contextual data which will be passed to the didEndSelector method.
	@param identities An array of SecIdentityRef objects, usually obtained from an identity search (see <Security/SecIdentitySearch.h>).
	@param message Client-defined message string to display in the panel.
	@discussion The didEndSelector method should have the following signature:
        - (void)chooseIdentitySheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo identities:(NSArray *)identities message:(NSString *)message;

/*!
    @method identity
    @abstract Returns the identity that the user chose in the panel.
*/
- (SecIdentityRef)identity;

/*!
    @method setPolicies:
	@abstract Specifies one or more policies that apply to the displayed certificates.
    @param policies The policies to use when evaluating the certificates' status.
		You can pass either a SecPolicyRef or a NSArray (containing one or more SecPolicyRef instances) in this parameter.
		If policies is set to nil, the Apple X.509 Basic Policy will be used.
	@discussion Applications will typically display a SFChooseIdentityPanel in the context of a specific usage, such as SSL or S/MIME.
	You should set only the policy references which apply to your intended usage.
*/
- (void)setPolicies:(id)policies;

/*!
    @method policies
	@abstract Returns an array of policies used to evaluate the status of the displayed certificates.
	@discussion This method returns an autoreleased NSArray containing one or more SecPolicyRef instances, as set by a previous setPolicies: call.
*/
- (NSArray *)policies;

/*!
    @method setDefaultButtonTitle:
    @abstract Customizes the title of the default button.
    @param title The new title for the default button.
*/
- (void)setDefaultButtonTitle:(NSString *)title;

/*!
    @method setAlternateButtonTitle:
    @abstract Customizes the title of the alternate button.
    @param title The new title for the alternate button. If title is set to nil, the button will not be shown.
*/
- (void)setAlternateButtonTitle:(NSString *)title;

/*
    @method setShowsHelp:
	@abstract Displays a help button in the panel.
    @param showsHelp Set to YES if the help button should be displayed, NO if it should be hidden.
    @discussion -setShowsHelp:YES adds a help button to the panel. When the help button is pressed, the delegate 
is first consulted.  If the delegate does not implement -chooseIdentityPanelShowHelp: or returns NO, then 
-[NSHelpManager openHelpAnchor:inBook:] is called with a nil book and the anchor specified by -setHelpAnchor: 
(if any). An exception will be raised if the delegate returns NO and there is no help anchor set.
*/
- (void)setShowsHelp:(BOOL)showsHelp;

/*
    @method showsHelp
	@abstract Returns YES if the help button is currently displayed, NO if hidden.
*/
- (BOOL)showsHelp;

/*
    @method setHelpAnchor:
	@abstract Sets the help anchor string for the modal panel.
    @param anchor The new help anchor string.
*/
- (void)setHelpAnchor:(NSString *)anchor;

/*
    @method helpAnchor
	@abstract Returns the current help anchor string for the modal panel.
*/
- (NSString *)helpAnchor;

@end

@interface NSObject (SFChooseIdentityPanelDelegate)
/*
    @method chooseIdentityPanelShowHelp:
	@abstract The delegate should implement this method if custom help behavior is required.
*/
- (BOOL)chooseIdentityPanelShowHelp:(SFChooseIdentityPanel *)sender;

@end

#endif /* !_SFCHOOSEIDENTITYPANEL_H_ */
