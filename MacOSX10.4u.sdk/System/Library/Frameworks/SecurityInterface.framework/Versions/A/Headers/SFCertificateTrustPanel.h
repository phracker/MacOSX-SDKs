/*
	SFCertificateTrustPanel.h
	SecurityInterface
	Copyright (c) 2002-2004 Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFCERTIFICATETRUSTPANEL_H_
#define _SFCERTIFICATETRUSTPANEL_H_

#import <Cocoa/Cocoa.h>
#import <SecurityInterface/SFCertificatePanel.h>
#include <Security/SecTrust.h>

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
	IBOutlet NSSplitView *_splitView;		
	IBOutlet NSTextField *_messageView;		
	IBOutlet NSButton *_saveChangesButton;
	IBOutlet NSButton *_cancelButton;	
	NSString *_defaultMessage;
	BOOL _saveChanges;
	id _reserved_SFCertificateTrustPanel;
}

/*!
	@method sharedCertificateTrustPanel
	@abstract Returns a shared instance of SFCertificateTrustPanel.
	@discussion If your application can display multiple SFCertificateTrustPanels at once,
	you should allocate (alloc) and initialize (init) separate object instances instead of using this class method.
*/
+ (SFCertificateTrustPanel *)sharedCertificateTrustPanel;

/*!
    @method runModalForTrust:message:
    @abstract Displays a modal panel that shows the results of a certificate trust evaluation.
		Returns NSOKButton if the default button is pressed, or NSCancelButton if the alternate button is pressed.
		Note that the user can edit trust decisions in this panel; call SecTrustGetResult after the panel is dismissed
		to obtain the current trust result for the SecTrustRef.
	@param trust A trust reference, previously created with SecTrustCreateWithCertificates (see <Security/SecTrust.h>).
    @param message Client-defined message string to display in the panel.
*/
- (int)runModalForTrust:(SecTrustRef)trust message:(NSString *)message;

/*!
	@method beginSheetForWindow:trust:message:modalDelegate:didEndSelector:contextInfo:
	@abstract Displays a modal sheet that shows the results of a certificate trust evaluation.
	@discussion The didEndSelector method should have the following signature:
        - (void)certificateTrustSheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
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
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo trust:(SecTrustRef)trust message:(NSString *)message;

@end

#endif /* !_SFCERTIFICATETRUSTPANEL_H_ */

