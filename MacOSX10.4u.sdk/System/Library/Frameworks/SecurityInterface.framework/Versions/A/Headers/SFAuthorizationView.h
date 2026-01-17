/*
	SFAuthorizationView.h
	SecurityInterface
    Copyright (c) 2000-2004 Apple Computer, Inc.
	All rights reserved.
*/

#ifndef _SFAUTHORIZATIONVIEW_H_
#define _SFAUTHORIZATIONVIEW_H_

#import <Cocoa/Cocoa.h>
#import <SecurityFoundation/SFAuthorization.h>

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
@protected
	SFAnimatedLockButton *_button;
    NSButton *_textButton;
	AuthorizationRights *_authorizationRights;
	SFAuthorization *_authorization;
	id _delegate;
	int	_currentState;
    BOOL _authorized;
    NSTimeInterval _timeInterval;
    AuthorizationFlags _flags;
	void *_privateData;
}

/*!
    @method setString:
    @abstract A convenience method to specify an authorization rights set containing a single item with the name set to the specified string.
    @param authorizationString Authorization string.
*/
- (void)setString:(AuthorizationString)authorizationString;

/*!
    @method setAuthorizationRights:
    @abstract Sets the authorization rights for this view.
    @param authorizationRights Authorization rights.
*/
- (void)setAuthorizationRights:(const AuthorizationRights *)authorizationRights;

/*!
	@method authorizationRights
	@abstract Returns the authorization rights for this view.
*/
- (AuthorizationRights *)authorizationRights;

/*!
	@method authorization
	@abstract Returns the authorization object associated with this view.
*/
- (SFAuthorization *)authorization;

/*!
    @method updateStatus:
	@abstract This method is called when the state of the authorization object has changed.
    @param inSender The action that is marked for updateStatus.
*/
- (BOOL)updateStatus:(id)inSender;

/*!
    @method setAutoupdate:
*/
- (void)setAutoupdate:(BOOL)autoupdate;

/*!
    @method setAutoUpdate:interval:
*/
- (void)setAutoupdate:(BOOL)autoupdate interval:(NSTimeInterval)interval;

/*!
	@method authorizationState
	@abstract Returns the current state of the authorization view.
*/
- (SFAuthorizationViewState)authorizationState;

/*!
    @method setEnabled:
	@abstract Sets the current state of the authorization view.
    @param enabled Enable flag.
*/
- (void)setEnabled:(BOOL)enabled;

/*!
	@method isEnabled
	@abstract Indicates if the authorization view is enabled or disabled.
*/
- (BOOL)isEnabled;

/*!
    @method setFlags:
	@abstract Sets the current authorization flags for the view.
    @param flags Authorization flags.
*/
- (void)setFlags:(AuthorizationFlags)flags;

/*!
    @method setDelegate:
	@abstract Sets the delegate for this authorization view. If you want to hear state changes (for example, the user clicked the button), set your delegate and implement the delegate methods mentioned for SFAuthorizationViewDelegate
    @param delegate The client's delegate object.
*/
- (void)setDelegate:(id)delegate;

/*!
    @method delegate
	@abstract
*/
- (id)delegate;

/*!
    @method authorize:
	@abstract
*/
- (BOOL)authorize:(id)inSender;

/*!
    @method deauthorize:
	@abstract
*/
- (BOOL)deauthorize:(id)inSender;

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
- (void)authorizationViewDidAuthorize:(SFAuthorizationView *)view;

/*!
    @method authorizationViewDidDeauthorize:
    @abstract
    @param view
*/
- (void)authorizationViewDidDeauthorize:(SFAuthorizationView *)view;

/*!
    @method authorizationViewShouldDeauthorize:
    @abstract
    @param view
*/
- (BOOL)authorizationViewShouldDeauthorize:(SFAuthorizationView *)view;

/*!
    @method authorizationViewCreatedAuthorization:
    @abstract
    @param view
*/
- (void)authorizationViewCreatedAuthorization:(SFAuthorizationView *)view;

/*!
    @method authorizationViewReleasedAuthorization:
    @abstract
    @param view
*/
- (void)authorizationViewReleasedAuthorization:(SFAuthorizationView *)view;
@end

#endif /* !_SFAUTHORIZATIONVIEW_H_ */
