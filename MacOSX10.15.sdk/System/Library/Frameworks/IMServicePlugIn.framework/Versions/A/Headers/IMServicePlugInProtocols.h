/*
    IMServicePlugIn Protocol
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@protocol IMServiceApplication;


#pragma mark -
#pragma mark IMServicePlugIn (Messages -> Service Plug-in)

/*!
    @protocol   IMServicePlugIn

    @discussion The principal class for each service plug-in must implement the IMServicePlugIn protocol.
    
                Messages messages your service plug-in instance to perform basic tasks such as
                logging in, logging out, and updating account settings.
*/
@protocol IMServicePlugIn <NSObject>


/*!
    @method     initWithServiceApplication:

    @discussion Messages calls this method to instantiate your service plug-in.
                
                At instantiation time, you are handed an IMServiceApplication
                which implements the corresponding protocols for each 
                optional protocol that your IMServicePlugIn implements.

    @param      serviceApplication  Your service application interface, used
                to communicate upwards to Messages.
*/
- (id) initWithServiceApplication:(id<IMServiceApplication>)serviceApplication NS_DEPRECATED_MAC(10_7, 10_13);


/*!
    @method     updateAccountSettings:

    @discussion Messages calls this method on the IMServicePlugIn prior to login
                with the user's account settings.

    @param      accountSettings  An NSDictionary containing the account settings.
    
                Common keys:
                IMServerHostAccountSetting     NSString - the server hostname
                IMServerPortAccountSetting     NSNumber - the server port number
                IMLoginHandleAccountSetting    NSString - the login handle to use
                IMPasswordAccountSetting       NSString - the password
                IMUsesSSLAccountSetting        NSNumber - (YES = use SSL, NO = do not use SSL)
*/
- (oneway void) updateAccountSettings:(NSDictionary *)accountSettings NS_DEPRECATED_MAC(10_7, 10_13);


/*!
    @method     login

    @discussion Messages calls this method on the IMServicePlugIn instance when the user 
                wishes to log into your service.

                Messages will show your service in the "Connecting" state until
                -plugInDidLogIn is called on the service application.
*/
- (oneway void) login NS_DEPRECATED_MAC(10_7, 10_13);


/*!
    @method     logout

    @discussion Messages calls this method on the IMServicePlugIn instance when the user 
                wishes to disconnect from your service.

                Messages will show your service in the "Disconnecting" state until
                -plugInDidLogOutWithError: is called on the service application.
*/
- (oneway void) logout NS_DEPRECATED_MAC(10_7, 10_13);

@end


#pragma mark -
#pragma mark IMServiceApplication (Service Plug-in -> Messages)

/*!
    @protocol   IMServiceApplication

    @discussion The IMServiceApplication is the base protocol your service plug-in uses to communicate
                information back to Messages.
                
                An object implementing the IMServiceApplication protocol is handed to your service
                plug-in in the -initWithServiceApplication: method.
*/
@protocol IMServiceApplication <NSObject>


/*!
    @method     plugInDidLogIn

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                changes the connection state from "Connecting" to "Connected"
*/
- (oneway void) plugInDidLogIn NS_DEPRECATED_MAC(10_7, 10_13);


/*!
    @method     plugInDidLogOutWithError:

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                changes the connection state to "Disconnected".
         
    @param      error      An error, if any, that caused the disconnection.  If plugInDidLogOutWithError:
                           is called in response to a requested -logout, error should be nil
    @param      reconnect  If set to YES, Messages will attempt to reconnect to the service when the
                           IMAccountSettingServerHost associated with the account becomes reachable.
                           reconnect should only be set to YES when a network error causes a log out.
*/
- (oneway void) plugInDidLogOutWithError:(NSError *)error reconnect:(BOOL)reconnect NS_DEPRECATED_MAC(10_7, 10_13);


/*!
     @method     plugInDidFailToAuthenticate
     
     @discussion When the IMServicePlugIn instance calls this method on the service application during
                 the login process, Messages will re-request the user name and password. It will then call
                 updateAccountSettings: with the new settings or logout if the user cancels.
*/
- (oneway void) plugInDidFailToAuthenticate NS_DEPRECATED_MAC(10_7, 10_13);


/*!
    @method     plugInDidUpdateProperties:ofHandle:

    @discussion The IMServicePlugIn instance should call this method on Messages in response to 
                a change in one or more of a handle's properties.

                In addition, this method should be called once for each handle in the group 
                list after the first call to -plugInDidUpdateGroupList:error:

                Note:
                Messages may discard the properties of handles which are neither in the group list nor have
                an active conversation.  For this reason, only call -plugInDidUpdateProperties:ofHandle:
                to update the properties of a handle after specifying the handle in
                -plugInDidUpdateGroupList:error:, -plugInDidReceiveMessage:fromHandle:, or
                -plugInDidSendMessage:toHandle:error:
                
    @param      handle  A handle
                changes An NSDictionary, corresponding to new handle properties for the handle
                
                        Available keys include:
                        IMHandlePropertyAvailability      - The IMHandleAvailability of the handle
                        IMHandlePropertyStatusMessage     - Current status message as plaintext NSString
                        IMHandlePropertyIdleDate          - The time of the last user activity
                        IMHandlePropertyAlias             - A "prettier" version of the handle, if available
                        IMHandlePropertyFirstName         - The first name (given name) of a handle
                        IMHandlePropertyLastName          - The last name (family name) of a handle
                        IMHandlePropertyEmailAddress      - The e-mail address for a handle
                        IMHandlePropertyPictureIdentifier - A unique identifier for the handle's picture
                        IMHandlePropertyCapabilities      - The capabilities of the handle                
*/
- (oneway void) plugInDidUpdateProperties:(NSDictionary *)changes ofHandle:(NSString *)handle NS_DEPRECATED_MAC(10_7, 10_13);

@end



