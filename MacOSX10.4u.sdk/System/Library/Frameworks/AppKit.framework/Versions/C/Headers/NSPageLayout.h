/*
	NSPageLayout.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/


#import <AppKit/NSApplication.h>
#import <AppKit/NSPanel.h>		// For NSCancelButton & NSOKButton.
#import <Foundation/NSObject.h>


@class NSPrintInfo, NSView, NSWindow;


#ifndef WIN32


// Tags for use with -viewWithTag:.  NSPAGELAYOUT IS NO LONGER A SUBCLASS OF NSPANEL.  THESE ARE ALL DEPRECATED.
enum {
    NSPLImageButton			= 50,
    NSPLTitleField			= 51,
    NSPLPaperNameButton			= 52,
    NSPLUnitsButton			= 54,
    NSPLWidthForm			= 55,
    NSPLHeightForm			= 56,
    NSPLOrientationMatrix		= 57,
    NSPLCancelButton			= NSCancelButton,
    NSPLOKButton			= NSOKButton
};


@interface NSPageLayout : NSObject

// Instance variables.
{

@private

    // All instance variables are private.
    unsigned char _184BytesOfPrivateData[184];
    
}

// Creating an NSPageLayout.
+ (NSPageLayout *)pageLayout;

// Running the NSPageLayout panel, document-modally.  didEndSelector must have the same signature as:
// - (void)pageLayoutDidEnd:(NSPageLayout *)pageLayout returnCode:(int)returnCode contextInfo:(void *)contextInfo;
- (void)beginSheetWithPrintInfo:(NSPrintInfo *)printInfo modalForWindow:(NSWindow *)docWindow delegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

// Running the NSPageLayout panel, application-modally.
- (int)runModal;
- (int)runModalWithPrintInfo:(NSPrintInfo *)pInfo;

// Customizing an NSPageLayout.
- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;

// Accessing the NSPrintInfo.
- (NSPrintInfo *)printInfo;
- (void)readPrintInfo;
- (void)writePrintInfo;

// Updating the display.  THESE ARE ALL DEPRECATED.
- (void)convertOldFactor:(float *)oldFactor newFactor:(float *)newFactor;
- (void)pickedButton:(id)sender;
- (void)pickedOrientation:(id)sender;
- (void)pickedPaperSize:(id)sender;
- (void)pickedUnits:(id)sender;

@end // interface NSPageLayout


@interface NSApplication(NSPageLayoutPanel)

// Showing standard panels.
- (void)runPageLayout:(id)sender;

@end // interface NSApplication(NSPageLayoutPanel)


#else // WIN32


@interface NSPageLayout : NSObject

// Instance variables.
{

    // All instance variables are private.
    void *_printdlg;
    NSPrintInfo *_printInfo;
    id _accessoryView;
    unsigned int _reservedPageLayout1;

}

// Class methods.
+ (NSPageLayout *)pageLayout;

// Instance methods.
- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)readPrintInfo;
- (void)writePrintInfo;
- (NSPrintInfo *)printInfo;
- (int)runModalWithPrintInfo:(NSPrintInfo *)pInfo;
- (int)runModal;

@end // interface NSPageLayout


@interface NSApplication(NSPageLayoutPanel)

// Instance methods.
- (void)runPageLayout:(id)sender;

@end // interface NSApplication(NSPageLayoutPanel)


#endif // WIN32
