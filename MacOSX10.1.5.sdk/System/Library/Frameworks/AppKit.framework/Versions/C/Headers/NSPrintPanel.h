/*
	NSPrintPanel.h
	Application Kit
	Copyright (c) 1994-2001, Apple Computer, Inc.
	All rights reserved.
*/


#import <Foundation/NSObject.h>


@class NSPopUpButton, NSPrintInfo, NSView, NSWindow;


#ifndef WIN32


// Tags for use with -viewWithTag:.  NSPAGELAYOUT IS NO LONGER A SUBCLASS OF NSPANEL.  THESE ARE ALL DEPRECATED.
enum {
    NSPPSaveButton			= 3,
    NSPPPreviewButton			= 4,
    NSFaxButton				= 5,
    NSPPTitleField			= 40,
    NSPPImageButton			= 41,
    NSPPNameTitle			= 42,
    NSPPNameField			= 43,
    NSPPNoteTitle			= 44,
    NSPPNoteField			= 45,
    NSPPStatusTitle			= 46,
    NSPPStatusField			= 47,
    NSPPCopiesField			= 49,
    NSPPPageChoiceMatrix		= 50,
    NSPPPageRangeFrom			= 51,
    NSPPPageRangeTo			= 52,
    NSPPScaleField			= 53,
    NSPPOptionsButton			= 54,
    NSPPPaperFeedButton			= 55,
    NSPPLayoutButton			= 56
};


@interface NSPrintPanel : NSObject

// Instance variables.
{

    // All instance variables are private.
    unsigned char _244BytesOfPrivateData[244];

}

// Creating an NSPrintPanel.
+ (NSPrintPanel *)printPanel;

// Running the NSPrintPanel, document-modally.  didEndSelector must have the same signature as:
// - (void)printPanelDidEnd:(NSPrintPanel *)printPanel returnCode:(int)returnCode contextInfo:(void *)contextInfo;
- (void)beginSheetWithPrintInfo:(NSPrintInfo *)printInfo modalForWindow:(NSWindow *)docWindow delegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

// Running the NSPrintPanel, application-modally.
- (int)runModal;

// Customizing the panel.
- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;

// Communicating with the NSPrintInfo object.
- (void)updateFromPrintInfo;
- (void)finalWritePrintInfo;

// Updating the panel's display.  THESE ARE ALL DEPRECATED.
- (void)pickedAllPages:(id)sender;
- (void)pickedButton:(id)sender;
- (void)pickedLayoutList:(id)sender;

@end // interface NSPrintPanel


#else  WIN32


@interface NSPrintPanel : NSObject

// Instance variables.
{

    // All instance variables are private.
    void *_printdlg;
    NSPrintInfo *_printInfo;
    id _accessoryView;
    NSPopUpButton *_printServicesPopUp;
    BOOL _checkedForPrintServicesPopUp;
    unsigned int _reservedPrintPanel1;

}

// Class methods.
+ (NSPrintPanel *)printPanel;

// Instance methods.
- (void)setAccessoryView:(NSView *)aView;
- (NSView *)accessoryView;
- (void)updateFromPrintInfo;
- (void)finalWritePrintInfo;
- (int) runModal;

@end // interface NSPrintPanel


#endif WIN32

