/*
	NSPageLayout.h
	Application Kit
	Copyright (c) 1994-2015, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <AppKit/NSApplication.h>

NS_ASSUME_NONNULL_BEGIN

@class NSPrintInfo, NSView, NSViewController, NSWindow, NSWindowController;

@interface NSPageLayout : NSObject {
    @private
    NSMutableArray *_accessoryControllers;
    NSPrintInfo *_originalPrintInfo;
    id _delegate;
    SEL _didEndSelector;
    void *_contextInfo;
    NSPrintInfo *_presentedPrintInfo;
    NSWindowController *_windowController;
#if __LP64__
    id _reserved[4];
#else
    unsigned char _compatibilityPadding[156];
#endif
}

/* Create a new NSPageLayout.
*/
+ (NSPageLayout *)pageLayout;


/* Controllers for the accessory views that will be presented in the page setup panel by the methods below. When the page setup panel is presented to the user each controller is automatically sent a -setRepresentedObject: message with this object's NSPrintInfo. Because NSViewControllers are KVC and KVO compliant for "representedObject," you can use one as the file's owner of an accessory view's nib and bind controls to the file's owner using key paths that start with "representedObject." to take advantage of NSPrintInfo's KVC and KVO compliance. Each controller is also automatically sent a -title message. If that returns nil the application's short name is used in the popup menu that lets the user choose an accessory view.
*/
- (void)addAccessoryController:(NSViewController *)accessoryController NS_AVAILABLE_MAC(10_5);
- (void)removeAccessoryController:(NSViewController *)accessoryController NS_AVAILABLE_MAC(10_5);
@property (readonly, copy) NSArray<__kindof NSViewController *> *accessoryControllers NS_AVAILABLE_MAC(10_5);


/* Present a page setup panel to the user, document-modally. When the user has dismissed it, send the message selected by didEndSelector to the delegate, with the contextInfo as the last argument. The method selected by didEndSelector must have the same signature as:

    - (void)pageLayoutDidEnd:(NSPageLayout *)pageLayout returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
*/
- (void)beginSheetWithPrintInfo:(NSPrintInfo *)printInfo modalForWindow:(NSWindow *)docWindow delegate:(nullable id)delegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(nullable void *)contextInfo;

/* Present a page setup panel to the user, application-modally, and return either NSOKButton or NSCancelButton. The default implementation of -runModal just invokes [self runModalWithPrintInfo:[NSPrintInfo sharedPrintInfo]].
*/
- (NSInteger)runModalWithPrintInfo:(NSPrintInfo *)printInfo;
- (NSInteger)runModal;

/* A simple accessor. Your -beginSheetWithPrintInfo:... delegate can use this so it doesn't have to keep a pointer to the NSPrintInfo elsewhere while waiting for the user to dismiss the print panel.
*/
@property (nullable, readonly, strong) NSPrintInfo *printInfo;

@end

@interface NSPageLayout(NSDeprecated)

/* Methods that were deprecated in Mac OS 10.5. -setAccessoryView: replaces all of the accessory controllers that have been added so far by -addAccessoryController:. -accessoryView merely returns the view of the first accessory controller, or nil.
*/
- (void)setAccessoryView:(null_unspecified NSView *)accessoryView NS_DEPRECATED_MAC(10_0, 10_5);
- (null_unspecified NSView *)accessoryView NS_DEPRECATED_MAC(10_0, 10_5);

/* Methods that were deprecated in Mac OS 10.5.
*/
- (void)readPrintInfo NS_DEPRECATED_MAC(10_0, 10_5);
- (void)writePrintInfo NS_DEPRECATED_MAC(10_0, 10_5);

@end

@interface NSApplication(NSPageLayoutPanel)

/* An action method that merely invokes [[NSPageLayout pageLayout] runModal].
*/
- (void)runPageLayout:(nullable id)sender;

@end

NS_ASSUME_NONNULL_END
