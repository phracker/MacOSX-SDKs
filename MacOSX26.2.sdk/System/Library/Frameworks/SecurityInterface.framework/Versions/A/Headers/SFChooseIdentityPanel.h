/*
 * Copyright (c) 2002-2020 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

/*!
    @header SFChooseIdentityPanel
*/

#ifndef _SFCHOOSEIDENTITYPANEL_H_
#define _SFCHOOSEIDENTITYPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecIdentity.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

@class SFCertificateView;

/*!
	@class SFChooseIdentityPanel
    @abstract SFChooseIdentityPanel is a panel and sheet interface that allows a user to select an identity from a list.
*/

@interface SFChooseIdentityPanel : NSPanel
{
@private
	/* All instance variables are private */
#if defined (__LP64__)
	id _reserved_SFChooseIdentityPanel;
#else
	IBOutlet NSTextField *_panelMessage;
	IBOutlet NSPopUpButton *_identityPopup;
	IBOutlet SFCertificateView *_certificateView;
	IBOutlet NSButton *_cancelButton;
	IBOutlet NSButton *_okButton;
	IBOutlet NSLayoutConstraint *_aboveContentHeightConstraint;
	int _indexOfChosenIdentity;
	SecCertificateRef _currCertRefDisplayed;
	NSArray *_identities;
	NSWindow *_parentWindowForSheet;
	IBOutlet NSWindow *_panel;
	SEL _clientDidEndSelector;
	id _clientDelegate;
	void *_clientContextInfo;
	id _reserved_SFChooseIdentityPanel;
#endif
}

/*!
	@method sharedChooseIdentityPanel
	@abstract Returns a shared instance of SFChooseIdentityPanel.
	@discussion If your application can display multiple SFChooseIdentityPanels at once,
	you should allocate (alloc) and initialize (init) separate object instances instead of using this class method.
*/
+ (SFChooseIdentityPanel *)sharedChooseIdentityPanel API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method runModalForIdentities:message:
    @abstract Displays a supplied list of identities in a modal panel, returning NSOKButton or NSCancelButton when dismissed.
	Use the -identity method to subsequently obtain the identity chosen by the user.
    @param identities An array of SecIdentityRef objects, usually obtained from an identity search (see <Security/SecIdentitySearch.h>).
    @param message Client-defined message string to display in the panel.
*/
- (NSInteger)runModalForIdentities:(NSArray *)identities message:(NSString *)message API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

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
        - (void)chooseIdentitySheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo identities:(NSArray *)identities message:(NSString *)message API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method identity
    @abstract Returns the identity that the user chose in the panel.
*/
- (SecIdentityRef)identity API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setPolicies:
	@abstract Specifies one or more policies that apply to the displayed certificates.
    @param policies The policies to use when evaluating the certificates' status.
		You can pass either a SecPolicyRef or a NSArray (containing one or more SecPolicyRef instances) in this parameter.
		If policies is set to nil, the Apple X.509 Basic Policy will be used.
	@discussion Applications will typically display a SFChooseIdentityPanel in the context of a specific usage, such as SSL or S/MIME.
	You should set only the policy references which apply to your intended usage.
*/
- (void)setPolicies:(id)policies API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method policies
	@abstract Returns an array of policies used to evaluate the status of the displayed certificates.
	@discussion This method returns an autoreleased NSArray containing one or more SecPolicyRef instances, as set by a previous setPolicies: call.
*/
- (NSArray *)policies API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setDefaultButtonTitle:
    @abstract Customizes the title of the default button.
    @param title The new title for the default button.
*/
- (void)setDefaultButtonTitle:(NSString *)title API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setAlternateButtonTitle:
    @abstract Customizes the title of the alternate button.
    @param title The new title for the alternate button. If title is set to nil, the button will not be shown.
*/
- (void)setAlternateButtonTitle:(NSString *)title API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*
    @method setShowsHelp:
	@abstract Displays a help button in the panel.
    @param showsHelp Set to YES if the help button should be displayed, NO if it should be hidden.
    @discussion -setShowsHelp:YES adds a help button to the panel. When the help button is pressed, the delegate
is first consulted.  If the delegate does not implement -chooseIdentityPanelShowHelp: or returns NO, then
-[NSHelpManager openHelpAnchor:inBook:] is called with a nil book and the anchor specified by -setHelpAnchor:
(if any). An exception will be raised if the delegate returns NO and there is no help anchor set.
*/
- (void)setShowsHelp:(BOOL)showsHelp API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*
    @method showsHelp
	@abstract Returns YES if the help button is currently displayed, NO if hidden.
*/
- (BOOL)showsHelp API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*
    @method setHelpAnchor:
	@abstract Sets the help anchor string for the modal panel.
    @param anchor The new help anchor string.
*/
- (void)setHelpAnchor:(NSString *)anchor API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*
    @method helpAnchor
	@abstract Returns the current help anchor string for the modal panel.
*/
- (NSString *)helpAnchor API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setInformativeText:
    @abstract Sets the optional informative text displayed in the SFChooseIdentityPanel.
	@param informativeText The informative text to display in the panel.
	@discussion Call this method to set the informative text to be displayed.
*/
- (void)setInformativeText:(NSString *)informativeText API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method informativeText
	@abstract Returns the informative text currently displayed in the SFChooseIdentityPanel.
*/
- (NSString *)informativeText API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setDomain:
    @abstract Sets an optional domain in which the identity is to be used.
	@param domainString A string containing a hostname, RFC822 name (email address), URL, or similar identifier.
	@discussion Call this method to associate a domain with the chosen identity.
		If the user chooses an identity and a domain has been set, an identity preference item will be created in the default keychain. Subsequently, calling SecIdentitySearchCreateWithPolicy and SecIdentitySearchCopyNext will return the preferred identity for this domain first.
*/
- (void)setDomain:(NSString *)domainString API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method domain
	@abstract Returns the domain which will be associated with the chosen identity.
*/
- (NSString *)domain API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

@interface NSObject (SFChooseIdentityPanelDelegate)
/*
    @method chooseIdentityPanelShowHelp:
	@abstract The delegate should implement this method if custom help behavior is required.
*/
- (BOOL)chooseIdentityPanelShowHelp:(SFChooseIdentityPanel *)sender API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

API_UNAVAILABLE_END

#endif /* !_SFCHOOSEIDENTITYPANEL_H_ */
