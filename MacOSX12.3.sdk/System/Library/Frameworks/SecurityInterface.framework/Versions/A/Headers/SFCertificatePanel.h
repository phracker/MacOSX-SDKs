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
    @header SFCertificatePanel
*/

#ifndef _SFCERTIFICATEPANEL_H_
#define _SFCERTIFICATEPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecCertificate.h>
#include <Security/SecTrust.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

@class SFCertificateView;

/*!
	@class SFCertificatePanel
    @abstract SFCertificatePanel is a panel and sheet interface that displays one or more certificates.
*/

@interface SFCertificatePanel : NSPanel
{
@private
	/* All instance variables are private */
#if defined (__LP64__)
	id _reserved_SFCertificatePanel;
#else
	IBOutlet SFCertificateView *_certView;
	IBOutlet NSWindow *_panel;
	IBOutlet NSButton *_okButton;
	IBOutlet NSTableView *_certTable;
	NSWindow *_parentWindowForSheet;
	SEL _clientDidEndSelector;
	id _clientDelegate;
	void *_clientContextInfo;
	NSMutableArray *_certDataArray;
	id _reserved_SFCertificatePanel;
#endif
}

/*!
	@method sharedCertificatePanel
	@abstract Returns a shared instance of SFCertificatePanel.
	@discussion If your application can display multiple SFCertificatePanels at once,
	you should allocate (alloc) and initialize (init) separate object instances instead of using this class method.
*/
+ (SFCertificatePanel *)sharedCertificatePanel API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method runModalForTrust:showGroup:
	@abstract Displays a certificate chain in a modal panel, returning NSOKButton when dismissed.
		This method is preferred over runModalForCertificates, since the SecTrustRef parameter lets you
		specify policies that determine whether the certificate is valid within your application's context.
    @param trust A trust reference which contains the certificates to display.
    @param showGroup Specifies whether additional certificates (other than the leaf certificate) are displayed.
*/
- (NSInteger)runModalForTrust:(SecTrustRef)trust showGroup:(BOOL)showGroup API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method runModalForCertificates:showGroup:
	@abstract Displays one or more specified certificates in a modal panel, returning NSOKButton when dismissed.
    @param certificates The certificates to display.
		Pass a NSArray containing one or more SecCertificateRef instances in this parameter.
		The leaf certificate is assumed to be at index 0; the order of additional certificates in the array is not critical.
    @param showGroup Specifies whether additional certificates (other than the leaf certificate) are displayed.
		To show only a single certificate, specify only one SecCertificateRef in the array and set showGroup to NO.
*/
- (NSInteger)runModalForCertificates:(NSArray *)certificates showGroup:(BOOL)showGroup API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method beginSheetForWindow:modalDelegate:didEndSelector:contextInfo:trust:showGroup:
	@abstract Displays a certificate chain in a modal sheet.
		This is the preferred sheet method for SFCertificatePanel, since the SecTrustRef parameter lets you
		specify policies that determine whether the certificate is valid within your application's context.
    @param docWindow The parent window to which the sheet is attached.
    @param modalDelegate The object whose didEndSelector method will be called when the sheet is dismissed.
    @param didEndSelector This method is called when the sheet is dismissed.
    @param contextInfo Client-defined contextual data which will be passed to the didEndSelector method.
    @param trust A trust reference which contains the certificates to display.
    @param showGroup Specifies whether additional certificates (other than the leaf certificate) are displayed.
    @discussion The didEndSelector method should have the following signature:
        - (void)certificateSheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo trust:(SecTrustRef)trust showGroup:(BOOL)showGroup API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method beginSheetForWindow:modalDelegate:didEndSelector:contextInfo:certificates:showGroup:
	@abstract Displays one or more specified certificates in a modal sheet.
    @param docWindow The parent window to which the sheet is attached.
    @param modalDelegate The object whose didEndSelector method will be called when the sheet is dismissed.
    @param didEndSelector This method is called when the sheet is dismissed.
    @param contextInfo Client-defined contextual data which will be passed to the didEndSelector method.
    @param certificates The certificates to display.
		Pass a NSArray containing one or more SecCertificateRef instances in this parameter.
    @param showGroup Specifies whether additional certificates (other than the leaf certificate) are displayed.
    @discussion The didEndSelector method should have the following signature:
        - (void)certificateSheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo certificates:(NSArray *)certificates showGroup:(BOOL)showGroup API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setPolicies:
	@abstract Specifies one or more policies that apply to the displayed certificates.
    @param policies The policies to use when evaluating the certificates' status.
		You can pass either a SecPolicyRef or a NSArray (containing one or more SecPolicyRef instances) in this parameter.
		If policies is set to nil, the Apple X.509 Basic Policy will be used.
	@discussion Applications will typically display a SFCertificatePanel in the context of a specific usage, such as SSL or S/MIME.
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
is first consulted.  If the delegate does not implement -certificatePanelShowHelp: or returns NO, then
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

/*
    @method certificateView
	@abstract Returns the current SFCertificateView instance for the modal panel.
*/
- (SFCertificateView *)certificateView API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

@interface NSObject (SFCertificatePanelDelegate)
/*
    @method certificatePanelShowHelp:
	@abstract The delegate should implement this method if custom help behavior is required.
*/
- (BOOL)certificatePanelShowHelp:(SFCertificatePanel *)sender API_AVAILABLE(macos(10.4)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

API_UNAVAILABLE_END

#endif /* !_SFCERTIFICATEPANEL_H_ */

