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
    @header SFKeychainSettingsPanel.h
*/

#ifndef _SFKEYCHAINSETTINGSPANEL_H_
#define _SFKEYCHAINSETTINGSPANEL_H_

#import <Cocoa/Cocoa.h>
#include <Security/SecKeychain.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

/*!
	@class SFKeychainSettingsPanel
    @abstract SFKeychainSettingsPanel is a panel and sheet interface that allows users to change their keychain settings.
*/
@class SFAutoLockTextValue;

@interface SFKeychainSettingsPanel : NSPanel
{
@private
	/* All instance variables are private */
#if defined (__LP64__)
	id _reserved_SFKeychainSettingsPanel;
#else
    IBOutlet NSTextField *_panelMessage;
    IBOutlet SFAutoLockTextValue *_autoLockValue;
    IBOutlet NSStepper *_autoLockStepper;
    IBOutlet NSButton *_autoLockCtrl;
    IBOutlet NSButton *_lockOnSleepCtrl;
    IBOutlet NSButton *_cancelButton;
    IBOutlet NSButton *_saveButton;
    IBOutlet NSWindow *_panel;
    IBOutlet NSTextField *_syncStateMessage;
    NSString *_keychainNameStr;
    NSWindow *_parentWindowForSheet;
    SEL _clientDidEndSelector;
    id _clientDelegate;
    void *_clientContextInfo;
    uint32_t _lockIntervalVal;
    SecKeychainRef _keychainRef;
    BOOL _lockOnSleepVal;
    SecKeychainSettings _settings;
    id _reserved_SFKeychainSettingsPanel;
#endif
}

/*!
    @method sharedKeychainSettingsPanel
    @abstract Returns a global instance of SFKeychainSettingsPanel object.
*/
+ (SFKeychainSettingsPanel *)sharedKeychainSettingsPanel API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method runModalForSettings:keychain:
    @abstract Changes the keychain settings using the settings panel. The panel contains settings such as "lock on sleep", "automatic lock", etc. If the user attempts to change the settings of a locked keychain, the unlock panel will be presented. It returns NSOKButton or NSCancelButton.
    @param settings A pointer to a keychain settings structure. Since this structure is versioned, you must preallocate it and fill in the version of the structure.
    @param keychain The keychain that will have its settings changed.
*/
- (NSInteger)runModalForSettings:(SecKeychainSettings *)settings keychain:(SecKeychainRef)keychain API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method beginSheetForWindow:settings:keychain:modalDelegate:didEndSelector:contextInfo:
    @abstract Presents a sheet version of SFKeychainSettingsPanel. The didEndSelector returnCode will contain either NSOKButton or NSCancelButton.
    @param docWindow The panel in which the settings sheet slides down; acting as a document modal window. If docWindow is nil, the behavior defaults to a standalone modal window.
    @param delegate Delegate object in which didEndSelector is a method.
    @param didEndSelector The didEndSelector method is optional. If implemented by the delegate, this method is invoked after the modal session has ended, but before dismissing the same panel. The didEndSelector may dismiss the keychain panel itself; otherwise it will be dismissed on return from the method. The didEndSelector should have the following signature:
	- (void)settingsPanelDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
    @param contextInfo A client-defined context.
    @param settings A pointer to a keychain settings structure. Since this structure is versioned, you must preallocate it and fill in the version of the structure.
    @param keychain The keychain that will have its settings changed.
*/
- (void)beginSheetForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo settings:(SecKeychainSettings *)settings keychain:(SecKeychainRef)keychain API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

API_UNAVAILABLE_END

#endif /* !_SFKEYCHAINSETTINGSPANEL_H_ */
