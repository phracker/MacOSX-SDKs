/*
	SFCertificatePanel.h
	SecurityInterface
	Copyright (c) 2002-2003, Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFCERTIFICATEPANEL_H_
#define _SFCERTIFICATEPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecCertificate.h>

@class SFCertificateView;

/*!
	@class SFCertificatePanel 
    @abstract SFCertificatePanel is a panel and sheet interface that displays a certificate.
*/

@interface SFCertificatePanel : NSPanel
{
@private
    IBOutlet SFCertificateView *_certView;
    IBOutlet NSWindow *_panel;
    IBOutlet NSButton *_okButton;	
	IBOutlet NSTableView *_certTable;
    NSWindow *_parentWindowForSheet;	
    SEL _clientDidEndSelector;
    id _clientDelegate;			
    void *_clientContextInfo;
    NSMutableArray *_certDataArray;
    void *_reserved_SFCertificatePanel;
}

/*!
	@method sharedCertificatePanel
	@abstract Returns a global instance of SFCertificatePanel.
*/
+ (SFCertificatePanel *)sharedCertificatePanel;

/*!
    @method runModalForCertificates:showGroup
	@abstract Displays a panel containing the data for each certificate in the array. If one certificate is specified in the array, the intermediate certificate will also be displayed. To show only a single certificate without its intermediate certificates, specify only one in the array and set showGroup to FALSE. It returns NSOKButton or NSCancelButton. 
    @param certificates One or more certificates to display.
    @param showGroup Indicates if intermediate certificates will be displayed.
*/
- (int)runModalForCertificates:(NSArray *)certificates showGroup:(BOOL)showGroup;

/*!
    @method beginSheetForWindow:modalDelegate:didEndSelector:contextInfo:certificate:
	@abstract Displays a sheet version of SFCertificatePanel. The didEndSelector returnCode will contain either NSOKButton or NSCancelButton.
    @param docWindow The parent window where the sheet appears.
    @param modalDelegate The object that has the 'didEndSelector' method when the sheet goes away.
    @param didEndSelector This method is called when the sheet goes away.
    @param contextInfo A client-defined context.
    @param certificates The certificates to display.
    @param showGroup Indicates if intermediate certificates will be displayed.
    @discussion The didEndSelector should like like:
        - (void)myDisplayCertificateSheetDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo certificates:(NSArray *)certificates showGroup:(BOOL)showGroup;

@end

#endif /* !_SFCERTIFICATEPANEL_H_ */

