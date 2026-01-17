/*
	SFKeychainSettingsPanel.h
	SecurityInterface
	Copyright (c) 2000-2004 Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFKEYCHAINSETTINGSPANEL_H_
#define _SFKEYCHAINSETTINGSPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecKeychain.h>

/*!
	@class SFKeychainSettingsPanel 
    @abstract SFKeychainSettingsPanel is a panel and sheet interface that allows users to change their keychain settings.
*/
@class AutoLockTextValue;

@interface SFKeychainSettingsPanel : NSPanel 
{
@private
    IBOutlet NSTextField *_panelMessage;
    IBOutlet AutoLockTextValue *_autoLockValue;
    IBOutlet NSStepper *_autoLockStepper;
    IBOutlet NSButton *_autoLockCtrl;	
    IBOutlet NSButton *_lockOnSleepCtrl;	
    IBOutlet NSButton *_cancelButton;	
    IBOutlet NSButton *_saveButton;	
    IBOutlet NSWindow *_panel;
    NSString *_keychainNameStr;
    NSWindow *_parentWindowForSheet;	
    SEL _clientDidEndSelector;
    id _clientDelegate;			
    void *_clientContextInfo;
    unsigned long _lockIntervalVal;
	SecKeychainRef _keychainRef;
    BOOL _lockOnSleepVal;
    SecKeychainSettings _settings;
    id _reserved;
}

/*!
    @method sharedKeychainSettingsPanel
    @abstract Returns a global instance of SFKeychainSettingsPanel object.
*/
+ (SFKeychainSettingsPanel *)sharedKeychainSettingsPanel;

/*!
    @method runModalForSettings:keychain:
    @abstract Changes the keychain settings using the settings panel. The panel contains settings such as "lock on sleep", "automatic lock", etc. If the user attempts to change the settings of a locked keychain, the unlock panel will be presented.  It returns NSOKButton or NSCancelButton.
    @param settings A pointer to a keychain settings structure. Since this structure is versioned, you must preallocate it and fill in the version of the structure.
    @param keychain The keychain that will have it's settings changed.
*/
- (int)runModalForSettings:(SecKeychainSettings *)settings keychain:(SecKeychainRef)keychain;

/*!
    @method beginSheetForWindow:settings:keychain:modalDelegate:didEndSelector:contextInfo:
    @abstract Presents a sheet version of SFKeychainSettingsPanel. The didEndSelector returnCode will contain either NSOKButton or NSCancelButton.
    @param docWindow The panel in which the settings sheet slides down; acting as a document modal window. If docWindow is nil, the behavior defaults to a standalone modal window.
    @param delegate Delegate object in which didEndSelector is a method.
    @param didEndSelector The didEndSelector method is optional. If implemented by the delegate, this method is invoked after the modal session has ended, but before dismissing the same panel. The didEndSelector may dismiss the keychain panel itself; otherwise it will be dismissed on return from the method. The didEndSelector should have the following signature:
    @param contextInfo A client-defined context.
    @param settings A pointer to a keychain settings structure. Since this structure is versioned, you must preallocate it and fill in the version of the structure.
    @param keychain The keychain that will have it's settings changed.

- (void)settingsPanelDidEnd:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo;
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo settings:(SecKeychainSettings *)settings keychain:(SecKeychainRef)keychain;

@end

#endif /* !_SFKEYCHAINSETTINGSPANEL_H_ */

