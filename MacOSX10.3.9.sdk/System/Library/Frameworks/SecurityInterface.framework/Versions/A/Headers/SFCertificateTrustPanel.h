/*
	SFCertificateTrustPanel.h
	SecurityInterface
	Copyright (c) 2002-2003, Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFCERTIFICATETRUSTPANEL_H_
#define _SFCERTIFICATETRUSTPANEL_H_

#import <Cocoa/Cocoa.h>
#import <SecurityInterface/SFCertificatePanel.h>
#import <SecurityInterface/SFCertificateView.h>
#include <Security/SecTrust.h>

@class SFCertificateView;

/*!
    @class SFCertificateTrustPanel 
    @abstract SFCertificateTrustPanel is a panel and sheet interface that allows a user to apply trust decisions to the trust configuration.
*/
@interface SFCertificateTrustPanel : SFCertificatePanel 
{
@private
	IBOutlet NSSplitView *_splitView;		
	IBOutlet NSTextField *_messageView;		
	IBOutlet NSButton *_saveChangesButton;
    IBOutlet NSButton *_cancelButton;	
	NSString *_defaultMessage;
	BOOL _saveChanges;
	void *_reservedTrust;
}

/*!
	@method sharedCertificateTrustPanel
	@abstract Returns a global instance of SFEditTrustPanel.
*/
+ (SFCertificateTrustPanel *)sharedCertificateTrustPanel;

/*!
    @method runModalForTrust:message:
    @abstract Displays a panel that shows the results of a trust evaluation from the specified trust object. It returns NSOKButton or NSCancelButton. The trust result can be retrieved from the trust object if the user made additional changes to the trust object in the panel.
    @param trust Trust reference used for the trust evaluation.
    @param message Client-defined string to display in the panel.
*/
- (int)runModalForTrust:(SecTrustRef)trust message:(NSString *)message;

/*!
@method beginSheetForWindow:trust:message:modalDelegate:didEndSelector:contextInfo:
@abstract Displays a sheet version of the SFCertificateTrustPanel.
 @discussion Displays the edit trust panel sheet showing the results of a trust evaluation. The user can edit trust decisions in the panel. The trust return value gets returned in the client's didEndSelector method.The didEndSelector returnCode will contain either NSOKButton or NSCancelButton. If the user changed trust settings, you can examine the trust evaluation result using the result method of your SFTrust object.
    @param docWindow The parent window where the sheet appears.
    @param modalDelegate The object that has the didEndSelector method when the sheet goes away.
    @param didEndSelector This method is called when the sheet goes away.
    @param contextInfo A client-defined context.
    @param trust Trust reference used for the trust evaluation.
    @param message Client-defined string to display in the panel.
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo trust:(SecTrustRef)trust message:(NSString *)message;

@end

#endif /* !_SFCERTIFICATETRUSTPANEL_H_ */

