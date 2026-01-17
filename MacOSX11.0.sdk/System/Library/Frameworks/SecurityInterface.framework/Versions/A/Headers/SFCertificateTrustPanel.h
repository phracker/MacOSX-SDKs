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
    @header SFCertificateTrustPanel
*/

#ifndef _SFCERTIFICATETRUSTPANEL_H_
#define _SFCERTIFICATETRUSTPANEL_H_

#import <Cocoa/Cocoa.h>
#import <SecurityInterface/SFCertificatePanel.h>
#include <Security/SecTrust.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

@class SFCertificateView;

/*!
    @class SFCertificateTrustPanel
    @abstract SFCertificateTrustPanel is a panel and sheet interface that allows a user to make trust decisions
	when one or more certificates involved in an operation are invalid or cannot be verified. It should be used
	whenever confirmation is required before proceeding with a certificate-related operation. It can also be
	displayed as an informative alert without requiring a decision to be made (if the operation or transaction
	has already occurred.)
*/
@interface SFCertificateTrustPanel : SFCertificatePanel
{
@private
	/* All instance variables are private */
#if defined (__LP64__)
	id _reserved_SFCertificateTrustPanel;
#else
    IBOutlet NSStackView *_stackView;
	IBOutlet NSSplitView *_splitView;
	IBOutlet NSButton *_saveChangesButton;
	IBOutlet NSButton *_cancelButton;
    IBOutlet NSLayoutConstraint *_discloseContentHeightConstraint;
	NSString *_defaultMessage;
	BOOL _saveChanges;
	id _reserved_SFCertificateTrustPanel;
#endif
}

/*!
	@method sharedCertificateTrustPanel
	@abstract Returns a shared instance of SFCertificateTrustPanel.
	@discussion If your application can display multiple SFCertificateTrustPanels at once,
	you should allocate (alloc) and initialize (init) separate object instances instead of using this class method.
*/
+ (SFCertificateTrustPanel *)sharedCertificateTrustPanel API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method runModalForTrust:message:
    @abstract Displays a modal panel that shows the results of a certificate trust evaluation.
		Returns NSOKButton if the default button is pressed, or NSCancelButton if the alternate button is pressed.
		Note that the user can edit trust decisions in this panel; call SecTrustGetResult after the panel is dismissed
		to obtain the current trust result for the SecTrustRef.
	@param trust A trust reference, previously created with SecTrustCreateWithCertificates (see <Security/SecTrust.h>).
    @param message Client-defined message string to display in the panel.
*/
- (NSInteger)runModalForTrust:(SecTrustRef)trust message:(NSString *)message API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method beginSheetForWindow:trust:message:modalDelegate:didEndSelector:contextInfo:
	@abstract Displays a modal sheet that shows the results of a certificate trust evaluation.
	@discussion The didEndSelector method should have the following signature:
        - (void)certificateTrustSheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo
		returnCode will contain either NSOKButton or NSCancelButton.
		Note that the user can edit trust decisions in this panel; call SecTrustGetResult after the panel is dismissed
		to obtain the current trust result for the SecTrustRef.
    @param docWindow The parent window to which the sheet is attached.
    @param modalDelegate The object whose didEndSelector method will be called when the sheet is dismissed.
    @param didEndSelector This method is called when the sheet is dismissed.
    @param contextInfo Client-defined contextual data which will be passed to the didEndSelector method.
    @param trust A trust reference, previously created with SecTrustCreateWithCertificates (see <Security/SecTrust.h>).
    @param message Client-defined message string to display in the panel.
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo trust:(SecTrustRef)trust message:(NSString *)message API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setInformativeText:
    @abstract Sets the optional informative text displayed in the SFCertificateTrustPanel.
	@param informativeText The informative text to display in the panel.
	@discussion By default, informative text describing the current certificate trust status is displayed.
		Call this method only if your application needs to customize the displayed informative text.
*/
- (void)setInformativeText:(NSString *)informativeText API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method informativeText
	@abstract Returns the informative text currently displayed in the SFCertificateTrustPanel.
*/
- (NSString *)informativeText API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

API_UNAVAILABLE_END

#endif /* !_SFCERTIFICATETRUSTPANEL_H_ */

