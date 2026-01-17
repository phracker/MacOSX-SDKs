/*
 * Copyright (c) 2006-2020 Apple Inc. All Rights Reserved.
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
    @header SFAuthorizationPluginView
*/

#ifndef _SFAUTHORIZATIONPLUGINVIEW_H_
#define _SFAUTHORIZATIONPLUGINVIEW_H_

#import <Cocoa/Cocoa.h>
#import <Security/AuthorizationPlugin.h>
#import <Availability.h>

API_UNAVAILABLE_BEGIN(ios, tvos, watchos, macCatalyst)

/*!
	@typedef SFButtonType
	@abstract Defines the button types that are used by AuthorizationPlugins.
	@constant SFButtonTypeCancel Indicates the Cancel button was pressed.
	@constant SFButtonTypeOK Indicates the OK button was pressed.
	@constant SFButtonTypeBack Indicates the Back button was pressed.
	@constant SFButtonTypeLogin Indicates the Login button was pressed.
*/
typedef enum
{
	SFButtonTypeCancel			= NSCancelButton,
	SFButtonTypeOK				= NSOKButton,

	SFButtonTypeBack			= SFButtonTypeCancel,
	SFButtonTypeLogin			= SFButtonTypeOK

} SFButtonType;


/*!
	@typedef SFViewType
	@abstract Defines the view types requested by AuthorizationPlugins.
	@constant SFViewTypeIdentityAndCredentials Indicates a view that has controls for identity and credentials was requested.
	@constant SFViewTypeCredentials Indicates a view that has controls for credentials was requested.
*/
typedef enum
{
	SFViewTypeIdentityAndCredentials,
	SFViewTypeCredentials

} SFViewType;



/*!
    @class SFAuthorizationPluginView
    @abstract SFAuthorizationPluginView is a class that you can use to insert an NSView into AuthorizationPlugin interfaces.
    @discussion  SFAuthorizationPluginView provides AuthorizationPlugin writers with an easy way to provide a user interface for their AuthorizationPlugin without having to duplicate the standard authentication dialog or the login window dialog.  This class was designed to be subclassed by the AuthorizationPlugin writer.  The following methods were designed to be overridden: buttonPressed:, didActivate, willActivateWithUser:, didDeactivate, firstKeyView, firstResponder, lastKeyView, setEnabled:, and viewForType:.  In order to display the user interface, the AuthorizationPlugin should create an instance of your subclass and then call displayView.  That will cause the appropriate dialog to be displayed and when credentials are needed, the overridden methods will be called in order to display the NSView provided by the subclass.
*/
@interface SFAuthorizationPluginView : NSObject
{
@private
	const AuthorizationCallbacks	*_callbacks;
	AuthorizationEngineRef			_engineRef;
	void							*_private;
}

/*!
    @method initWithCallbacks:andEngineRef:
    @abstract The initialization method of this class.  You must provide the callbacks and engineRef that were provided to the AuthorizationPlugin and AuthorizationMechanismRef.
    @param callbacks The AuthorizationCallbacks provided to the AuthorizationPlugin.
	@param engineRef The AuthorizationEngineRef provided to the AuthorizationMechanismRef.
*/
- (id)initWithCallbacks:(const AuthorizationCallbacks *)callbacks andEngineRef:(AuthorizationEngineRef)engineRef API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method engineRef
    @abstract An accessor method to the AuthorizationEngineRef provided to the init method.  Use this value when calling the functions of the AuthorizationCallbacks when you need to set the result or set a context value.
*/
- (AuthorizationEngineRef)engineRef API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method callbacks
    @abstract An accessor method to the AuthorizationEngineRef provided to the init method.  Use this to get the function pointers to SetResult, SetContextValue, etc.  See the AuthorizationCallbacks documentation for more details.
*/
- (const AuthorizationCallbacks	*)callbacks API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method buttonPressed:
    @abstract When a user presses a button, this method will be called to inform the SFAuthorizationPluginView of the user's action. By default buttonPressed: will set a result of Deny when the OK or Login buttons are pressed.

	If a user has pressed Login or OK button was pressed, the subclass needs to set the context values for the short name of the user so that user attributes can be looked up.  Use kAuthorizationEnvironmentUsername as the key.  The subclass should also set any additional context values that are needed by the authentication plugin to verify the user's credentials.

	@param inButtonType the type of button that was pressed.
*/
- (void)buttonPressed:(SFButtonType)inButtonType API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
	@method lastError
	@abstract Called by the Apple provided SecurityAgent plugin to get a description of the error that occurred during evaluation.  If no error occurred, the method should return nil.

	A downstream mechanism that works in cooperation with the SFAuthorizationPluginView can set a context value using the kAuthorizationContextFlagSticky flag to make it available to the SFAuthorizationPluginView in case of an error.
*/
- (NSError*)lastError API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method didActivate
    @abstract Called when the user interface was made active by the AuthorizationPlugin.
*/
- (void)didActivate API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method willActivateWithUser:
    @abstract Called by the Apple provided SecurityAgent plugin before the UI is made active.
	@param inUserInformation is a dictionary contains the following information:
		kSFAuthorizationPluginViewUserNameKey - an NSString with the selected user's name
		kSFAuthorizationPluginViewUserShortNameKey - an NSString with the selected user's short name

		The user name can be used to pre-populate a Text Field.
		NOTE: inUserInformation may be nil.
*/
- (void)willActivateWithUser:(NSDictionary *)inUserInformation API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method didDeactivate
    @abstract Called when the user interface is deactivated by the AuthorizationPlugin.
*/
- (void)didDeactivate API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method firstKeyView
	@abstract When called by the AuthorizationPlugin, the subclass should return the first view in the keyboard loop of the NSView.  The default value returned is nil.
*/
- (NSView*)firstKeyView API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method firstResponder
	@abstract When called by the AuthorizationPlugin, the subclass should return the view that should get the focus for keyboard events.  The default value returned is nil.
*/
- (NSResponder*)firstResponder API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method lastKeyView
	@abstract When called by the AuthorizationPlugin, the subclass should return the last view in the keyboard loop for the view.  The default value returned is nil.
*/
- (NSView*)lastKeyView API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setEnabled:
	@abstract When called by the AuthorizationPlugin, the subclass should call setEnabled: on the controls that are in its view.
	@param inEnabled the state the controls should be in.
*/
- (void)setEnabled:(BOOL)inEnabled API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method viewForType:
	@abstract When called by the AuthorizationPlugin, the subclass should return the appropriate NSView for the requested SFViewType.  The NSView and its contents should have the autoresize flags set as appropriate to allow for the view to be resized.
	@param inType is the type of view being requested by the AuthorizationPlugin.

	NOTE: Currently a maximum width of 394 points is supported, but Apple reserves the right to change that in the future.  Do not assume that the width of the NSView won't change.
*/
- (NSView*)viewForType:(SFViewType)inType API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end


/*!
    @category SFAuthorizationPluginView (SFHostControl)
    @abstract Methods called by the AuthorizationPlugin that instantiated the subclass or by the subclass.
*/
@interface SFAuthorizationPluginView (SFHostControl)

/*!
    @method displayView
	@abstract displayView is called in order to display the user interface provided by the subclass.  If you subclass this method, be sure to call [super displayView].  displayView will raise an SFDisplayViewException exception if an error occurs displaying the authorization dialog.
*/
- (void)displayView API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method setButton:enabled:
    @abstract The SFAuthorizationPluginView calls this when it would like to disable a button in the UI.
	@param inButtonType the type of the button
	@param inEnabled YES to enabled the button, NO to disable the button
*/
- (void)setButton:(SFButtonType)inButtonType enabled:(BOOL)inEnabled API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

/*!
    @method updateView
	@abstract updateView is called in order to have a new or modified NSView loaded by the AuthorizationPlugin.
*/
- (void)updateView API_AVAILABLE(macos(10.5)) API_UNAVAILABLE(ios, tvos, watchos, macCatalyst);

@end


extern NSString	* const SFAuthorizationPluginViewUserNameKey;
extern NSString	* const SFAuthorizationPluginViewUserShortNameKey;
extern NSString	* const SFDisplayViewException;

API_UNAVAILABLE_END

#endif /* !_SFAUTHORIZATIONPLUGINVIEW_H_ */

