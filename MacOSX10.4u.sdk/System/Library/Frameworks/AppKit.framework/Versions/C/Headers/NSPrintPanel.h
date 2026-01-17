/*
	NSPrintPanel.h
	Application Kit
	Copyright (c) 1994-2005, Apple Computer, Inc.
	All rights reserved.
*/

#import <AppKit/AppKitDefines.h>
#import <Foundation/NSObject.h>

@class NSPrintInfo, NSView, NSWindow;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

// Valid values for passing into -[NSPrintPanel setJobStyleHint:].
APPKIT_EXTERN NSString *NSPrintPhotoJobStyleHint;

#endif

// Tags for use with -viewWithTag:.  NSPRINTPANEL IS NO LONGER A SUBCLASS OF NSPANEL.  THESE ARE ALL DEPRECATED.
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

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2

// Set or get a string that provides a hint about the type of print job in which this print panel is being used.  This controls the set of items that appear in the Presets menu.  The string must be one of the job style hint strings declared above, or nil to provide no hint.
- (void)setJobStyleHint:(NSString *)hint;
- (NSString *)jobStyleHint;

#endif

// Communicating with the NSPrintInfo object.
- (void)updateFromPrintInfo;
- (void)finalWritePrintInfo;

// Updating the panel's display.  THESE ARE ALL DEPRECATED.
- (void)pickedAllPages:(id)sender;
- (void)pickedButton:(id)sender;
- (void)pickedLayoutList:(id)sender;

@end // interface NSPrintPanel
