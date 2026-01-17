/*
 * Copyright (c) 2000-2020 Apple Inc. All Rights Reserved.
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
    @header SFAuthorizationView
*/

#ifndef _SFAUTHORIZATIONVIEW_H_
#define _SFAUTHORIZATIONVIEW_H_

#import <Cocoa/Cocoa.h>
#import <SecurityFoundation/SFAuthorization.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

/*!
	@typedef SFAuthorizationViewState
	@abstract Defines the current state of the authorization view.
	@constant SFAuthorizationStartupState Indicates the state is starting up.
	@constant SFAuthorizationViewLockedState Indicates the state is locked.
	@constant SFAuthorizationViewInProgressState Indicates the state is 'in progress'.
	@constant SFAuthorizationViewUnlockedState Indicates the state is unlocked.
*/
typedef enum
{
    SFAuthorizationStartupState,
    SFAuthorizationViewLockedState,
    SFAuthorizationViewInProgressState,
    SFAuthorizationViewUnlockedState
} SFAuthorizationViewState;

/*!
    @class SFAuthorizationView
    @abstract SFAuthorizationView is a custom view that you can use to visually represent restricted functionality, requiring authorization for access.
    @discussion  You can add SFAuthorizationView to your application as a custom view, make your controller the delegate for the view and initialize the view by setting a right string (setString:) or rights structure (setAuthorizationRights:) to check for, as well as auto-updates (setAutoupdate:) or manual updates (updateStatus:). Note that you'll have to call updateStatus: to set the lock icon to its initial state. Changes to the current state as well as the startup state (after the initial updateStatus) are communicated to the delegate.  Implementing any of the following is optional):
    <ul>
      <li>authorized: changed to unlocked
      <li>deauthorized: changed to locked
      <li>shouldDeauthorize: when a user wants to lock, the delegates can react to this before it happens and avoid it by returning NO.
      <li>cancelAuthorization: the user cancelled authorization.
    </ul>
Calls to updateStatus: return YES if in the unlocked state, NO otherwise. Note that when committing changes or performing actions, authorization has to be checked again before going ahead with it. The default behavior of this view is to pre-authorize rights, if this is not possible it will unlock and wait for authorization to be checked when explicitly required. For handing the SFAuthorization (authorization:) to another process it's NSCoder support can be used.
*/
@class SFAuthorizationViewDelegate;
@class SFAnimatedLockButton;

@interface SFAuthorizationView : NSView
{
#if defined (__LP64__)
@private
	/* All instance variables are private */
	id _reserved_SFAuthorizationView;
#else
@protected
	/* Warning: do not access these instance variables directly from a subclass;
	   always use accessor methods! */
	SFAnimatedLockButton *_button;
	NSButton *_textButton;
	AuthorizationRights *_authorizationRights;
	SFAuthorization *_authorization;
	id _delegate;
	SFAuthorizationViewState _currentState;
	BOOL _authorized;
	NSTimeInterval _timeInterval;
	AuthorizationFlags _flags;
	id _privateData;
#endif
}

/*!
    @method setString:
    @abstract A convenience method to specify an authorization rights set containing a single item with the name set to the specified string.
    @param authorizationString Authorization string.
*/
- (void)setString:(AuthorizationString)authorizationString API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setAuthorizationRights:
    @abstract Sets the authorization rights for this view.
    @param authorizationRights Authorization rights.
*/
- (void)setAuthorizationRights:(const AuthorizationRights *)authorizationRights API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method authorizationRights
	@abstract Returns the authorization rights for this view.
*/
- (AuthorizationRights *)authorizationRights API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method authorization
	@abstract Returns the authorization object associated with this view.
*/
- (SFAuthorization *)authorization API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method updateStatus:
	@abstract This method is called when the state of the authorization object has changed.
    @param inSender The action that is marked for updateStatus.
*/
- (BOOL)updateStatus:(id)inSender API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setAutoupdate:
*/
- (void)setAutoupdate:(BOOL)autoupdate API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setAutoUpdate:interval:
*/
- (void)setAutoupdate:(BOOL)autoupdate interval:(NSTimeInterval)interval API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method authorizationState
	@abstract Returns the current state of the authorization view.
*/
- (SFAuthorizationViewState)authorizationState API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setEnabled:
	@abstract Sets the current state of the authorization view.
    @param enabled Enable flag.
*/
- (void)setEnabled:(BOOL)enabled API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method isEnabled
	@abstract Indicates if the authorization view is enabled or disabled.
*/
- (BOOL)isEnabled API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setFlags:
	@abstract Sets the current authorization flags for the view.
    @param flags Authorization flags.
*/
- (void)setFlags:(AuthorizationFlags)flags API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setDelegate:
	@abstract Sets the delegate for this authorization view. If you want to hear state changes (for example, the user clicked the button), set your delegate and implement the delegate methods mentioned for SFAuthorizationViewDelegate
    @param delegate The client's delegate object.
*/
- (void)setDelegate:(id)delegate API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method delegate
	@abstract
*/
- (id)delegate API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method authorize:
	@abstract
*/
- (BOOL)authorize:(id)inSender API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method deauthorize:
	@abstract
*/
- (BOOL)deauthorize:(id)inSender API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

/*!
    @category NSObject(SFAuthorizationViewDelegate)
    @abstract Optionally implement these delegate methods to obtain the state of the authorization object.
*/
@interface NSObject (SFAuthorizationViewDelegate)

/*!
    @method authorizationViewDidAuthorize:
    @abstract
    @param view
*/
- (void)authorizationViewDidAuthorize:(SFAuthorizationView *)view API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method authorizationViewDidDeauthorize:
    @abstract
    @param view
*/
- (void)authorizationViewDidDeauthorize:(SFAuthorizationView *)view API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method authorizationViewShouldDeauthorize:
    @abstract
    @param view
*/
- (BOOL)authorizationViewShouldDeauthorize:(SFAuthorizationView *)view API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method authorizationViewCreatedAuthorization:
    @abstract
    @param view
*/
- (void)authorizationViewCreatedAuthorization:(SFAuthorizationView *)view API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method authorizationViewReleasedAuthorization:
    @abstract
    @param view
*/
- (void)authorizationViewReleasedAuthorization:(SFAuthorizationView *)view API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
 @method authorizationViewDidHide:
 @abstract
 @param view
 */
- (void)authorizationViewDidHide:(SFAuthorizationView *)view API_AVAILABLE(macos(10.3)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end

API_UNAVAILABLE_END

#endif /* !_SFAUTHORIZATIONVIEW_H_ */
