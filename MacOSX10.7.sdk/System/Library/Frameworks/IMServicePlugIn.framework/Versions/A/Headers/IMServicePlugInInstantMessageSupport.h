/*
    Protocols for Instant Messaging Support
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@class IMServicePlugInMessage;


#pragma mark -
#pragma mark IMServicePlugIn (iChat -> Service Plug-in)

/*!
    @protocol   IMServicePlugInInstantMessagingSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports one-to-one instant messaging.

                If implementing this protocol, you must also include "IMServiceCapabilityInstantMessagingSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                IMServicePlugInInstantMessagingSupport and IMServiceApplicationInstantMessagingSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInInstantMessagingSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationInstantMessagingSupport protocol.
*/
@protocol IMServicePlugInInstantMessagingSupport


/*!
    @method     userDidStartTypingToHandle:

    @discussion iChat calls this method on the IMServicePlugIn instance when the user starts
                typing a message to a specific handle from the input line.

    @param      handle  The handle to which the user has started typing.
*/
- (oneway void) userDidStartTypingToHandle:(NSString *)handle;


/*!
    @method     userDidStopTypingToHandle:

    @discussion iChat calls this method on the IMServicePlugIn instance if the user clears the input line
                after typing instead of sending the message.

    @param      handle  The handle to which the user started typing, but then cleared the input line.
*/
- (oneway void) userDidStopTypingToHandle:(NSString *)handle;


/*!
    @method     sendMessage:toHandle:

    @discussion iChat calls this method on the IMServicePlugIn instance when the user sends a message
                to a specific handle.
                
                To indicate successful delivery of the message (and have it show up in iChat), the
                IMServicePlugIn should reflect the message via
                
                -[id<IMServiceApplicationInstantMessagingSupport> plug-inDidSendMessage:toHandle:error:]
                
                with a nil error.  A non-nil error indicates that the message could not be sent.

    @param      message  The message to send
    @param      handle   The receipient of the message
*/
- (oneway void) sendMessage:(IMServicePlugInMessage *)message toHandle:(NSString *)handle;

@end


#pragma mark -
#pragma mark IMServiceApplication (Service Plug-in -> iChat)

/*!
    @protocol   IMServiceApplicationInstantMessagingSupport

    @discussion This protocol is used to pass incoming instant messaging events from the server up to
                iChat, and to provide response callbacks to IMServicePlugInInstantMessagingSupport 
                methods.
                
                IMServicePlugInInstantMessagingSupport and IMServiceApplicationInstantMessagingSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInInstantMessagingSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationInstantMessagingSupport protocol.
*/
@protocol IMServiceApplicationInstantMessagingSupport


/*!
    @method     handleDidStartTyping:

    @discussion When the IMServicePlugIn instance calls this method on the service application, iChat displays
                the "thought bubble" for the specified handle.  
                
                A call to -handleDidStopTyping: will clear the thought bubble.
                
                A call to -plugInDidReceiveMessage:fromHandle: will replace the thought bubble with an actual message.

    @param      handle   The handle that started typing
*/
- (oneway void) handleDidStartTyping:(NSString *)handle;


/*!
    @method     handleDidStopTyping:

    @discussion When the IMServicePlugIn instance calls this method on the service application, iChat removes
                any thought bubble for the specified handle.  

    @param      handle   The handle that stopped typing
*/
- (oneway void) handleDidStopTyping:(NSString *)handle;


/*!
    @method     plugInDidReceiveMessage:fromHandle:

    @discussion When the IMServicePlugIn instance calls this method on the service application, iChat appends
                the message to the active chat with the handle.
                
                If no chat is present, iChat displays the message in a notifier window.

    @param      message  The incoming message
    @param      handle   The sender of the message
*/
- (oneway void) plugInDidReceiveMessage:(IMServicePlugInMessage *)message fromHandle:(NSString *)handle;


/*!
    @method     plugInDidSendMessage:toHandle:error:

    @discussion When the IMServicePlugIn instance calls this method on the service application with a nil
                error, iChat appends the message to the active chat with the handle.
    
                If an error is non-nil, iChat displays an error informing the user that the message
                could not be delivered.
                
                This method should be called once in response to every:
                -[id<IMServicePlugInInstantMessageSupport> sendMessage:toHandle:]
    
    @param      message  The incoming message
    @param      handle   The sender of the message
    @param      error    An error that occurred during message delivery
*/
- (oneway void) plugInDidSendMessage:(IMServicePlugInMessage *)message toHandle:(NSString *)handle error:(NSError *)error;

@end
