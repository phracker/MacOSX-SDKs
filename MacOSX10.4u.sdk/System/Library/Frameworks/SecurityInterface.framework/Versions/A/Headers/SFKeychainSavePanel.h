/*
	SFKeychainSavePanel.h
	SecurityInterface
	Copyright (c) 2002-2004 Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFKEYCHAINSAVEPANEL_H_
#define _SFKEYCHAINSAVEPANEL_H_

#import <AppKit/AppKit.h>
#include <Security/SecKeychain.h>

/*!
	@class SFKeychainSavePanel
    @abstract SFKeychainSavePanel is a panel and sheet interface used to create a keychain using the NSSavePanel UI.
*/
@interface SFKeychainSavePanel : NSSavePanel 
{
@private
    IBOutlet NSView *_customView;
    IBOutlet NSTextField *_message;
	NSString *_password;
	NSString *_kcFullPathName;
	NSString *_startPath;
	NSString *_keychainFileName;
    __strong SecKeychainRef _returnedKeychain;
	NSWindow *_parentWindowForSheet;	
    SEL	_clientDidEndSelector;
	id	_clientDelegate;			
	void *_contextInfo;
    OSStatus _result;
    void *_reserved_SFKeychainSavePanel;
}

/*!
    @method sharedKeychainSavePanel
    @abstract Returns a global instance of SFKeychainSavePanel object.
*/
+ (SFKeychainSavePanel *)sharedKeychainSavePanel;

/*!
    @method runModalForDirectory:file:
    @abstract Displays a keychain save panel.
    @param path The path to where the keychain is created (nil for ~/Library/Keychains).
    @param name The keychain name to be automatically filled out in the NSSave panel.
    @result a result code returned by NSSavePanel's runModalForDirectory method.
*/
- (int)runModalForDirectory:(NSString *)path file:(NSString *)name;

/*!
	@method setPassword:
    @abstract Specifies the password for the keychain that will be created.
    @param The password string object.
*/
- (void)setPassword:(NSString *)password;

/*!
    @method keychain
    @abstract Returns the keychain created by the SFKeychainSavePanel.
    @result The keychain object.
*/
- (SecKeychainRef)keychain;

/*!
    @method beginSheetForDirectory:file:modalForWindow:modalDelegate:didEndSelector:contextInfo:
    @abstract Displays a keychain save panel as a sheet.
    @param path The path to where the keychain is created (nil for ~/Library/Keychains).
    @param name The keychain name to be automatically filled out in the NSSave panel.
    @param docWindow The panel in which the save sheet slides down; acting as a document modal window. If docWindow is nil, the behavior defaults to a standalone modal window.
    @param delegate Delegate object in which didEndSelector is a method.
    @param didEndSelector The didEndSelector method is optional.  If implemented by the delegate, this method is invoked after the modal session has ended, but before dismissing the same panel. didEndSelector may dismiss the keychain panel itself; otherwise it will be dismissed on return from the method.  didEndSelector should have the following signature:

- (void)createPanelDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void  *)contextInfo;
    @param contextInfo Client-defined context pointer.
*/
- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo;

@end

#endif /* !_SFKEYCHAINSAVEPANEL_H_ */

