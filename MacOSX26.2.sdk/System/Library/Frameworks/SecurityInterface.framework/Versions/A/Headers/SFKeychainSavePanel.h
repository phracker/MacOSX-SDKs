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
    @header SFKeychainSavePanel.h
*/

#ifndef _SFKEYCHAINSAVEPANEL_H_
#define _SFKEYCHAINSAVEPANEL_H_

#import <AppKit/AppKit.h>
#include <Security/SecKeychain.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

#ifndef __APPLE_CC__
#define __strong
#endif

/*!
	@class SFKeychainSavePanel
    @abstract SFKeychainSavePanel is a panel and sheet interface used to create a keychain using the NSSavePanel UI.
*/
@interface SFKeychainSavePanel : NSSavePanel
{
@private
	/* All instance variables are private */
#if defined (__LP64__)
	id _reserved_SFKeychainSavePanel;
#else
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
    id _reserved_SFKeychainSavePanel;
#endif
}

/*!
    @method sharedKeychainSavePanel
    @abstract Returns a global instance of SFKeychainSavePanel object.
*/
+ (SFKeychainSavePanel *)sharedKeychainSavePanel API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method runModalForDirectory:file:
    @abstract Displays a keychain save panel.
    @param path The path to where the keychain is created (nil for ~/Library/Keychains).
    @param name The keychain name to be automatically filled out in the NSSave panel.
    @result a result code returned by NSSavePanel's runModalForDirectory method.
*/
- (NSInteger)runModalForDirectory:(NSString *)path file:(NSString *)name API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method setPassword:
    @abstract Specifies the password for the keychain that will be created.
    @param The password string object.
*/
- (void)setPassword:(NSString *)password API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method keychain
    @abstract Returns the keychain created by the SFKeychainSavePanel.
    @result The keychain object.
*/
- (SecKeychainRef)keychain API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method error
    @abstract Returns the last error encountered by SFKeychainSavePanel.
    @result The error object.
*/
- (NSError *)error API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method beginSheetForDirectory:file:modalForWindow:modalDelegate:didEndSelector:contextInfo:
    @abstract Displays a keychain save panel as a sheet.
    @param path The path to where the keychain is created (nil for ~/Library/Keychains).
    @param name The keychain name to be automatically filled out in the NSSave panel.
    @param docWindow The panel in which the save sheet slides down; acting as a document modal window. If docWindow is nil, the behavior defaults to a standalone modal window.
    @param delegate Delegate object in which didEndSelector is a method.
    @param didEndSelector The didEndSelector method is optional. If implemented by the delegate, this method is invoked after the modal session has ended, but before dismissing the same panel. didEndSelector may dismiss the keychain panel itself; otherwise it will be dismissed on return from the method. didEndSelector should have the following signature:
	- (void)createPanelDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void  *)contextInfo;
    @param contextInfo Client-defined context pointer.
*/
- (void)beginSheetForDirectory:(NSString *)path file:(NSString *)name modalForWindow:(NSWindow *)docWindow modalDelegate:(id)delegate didEndSelector:(SEL)didEndSelector contextInfo:(void *)contextInfo API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

API_UNAVAILABLE_END

#endif /* !_SFKEYCHAINSAVEPANEL_H_ */
