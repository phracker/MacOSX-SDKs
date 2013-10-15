/*
    Protocols for Chat Room Support
    IMServicePlugIn Framework
    Copyright (c) 2009-2010, Apple, Inc.
    All rights reserved.
*/

#import <Foundation/Foundation.h>

@class IMServicePlugInMessage;


#pragma mark -
#pragma mark IMServicePlugIn (Messages -> Service Plug-in)

/*!
    @protocol   IMServicePlugInChatRoomSupport

    @discussion Implementing this protocol on your service plug-in's principal class indicates that your
                service supports chat-room-based messaging.

                If implementing this protocol, you must also include "IMServiceCapabilityChatRoomSupport"
                in the "IMServiceCapabilities" key in the Info.plist of your service plug-in.

                IMServicePlugInChatRoomSupport and IMServiceApplicationChatRoomSupport are
                paired protocols.  If your service plug-in's principal class implements the
                IMServicePlugInChatRoomSupport protocol, the IMServiceApplication object handed to your
                IMServicePlugIn will implement the IMServiceApplicationChatRoomSupport protocol.
*/

@protocol IMServicePlugInChatRoomSupport


/*!
    @method     joinChatRoom:

    @discussion Messages calls this method on the IMServicePlugIn instance when the user attempts
                to join a chat room.
                
                To indicate success, -plugInDidJoinChatRoom: should be called by the service plug-in on the
                service application, followed by -handles:didJoinChatRoom: to indicate the current
                chat room member handles.

                To indicate failure, -plugInDidLeaveChatRoom:error: should be called by the service plug-in
                with a non-nil error.
                
                This method may also be called by Messages when the user clicks "Accept" to a chat
                room invitation.
                
    @param      roomName  The name of the room which the user wishes to join.
*/
- (oneway void) joinChatRoom:(NSString *)roomName;


/*!
    @method     leaveChatRoom:

    @discussion Messages calls this method on the IMServicePlugIn instance when the user closes
                the chat room window, or when the service disconnects.
                
                The service plug-in should attempt to cleanly leave the chat room, and then
                call -plugInDidLeaveChatRoom:error: on the service application once the room is left.

    @param      roomName  The name of the room which the user wishes to leave.
*/
- (oneway void) leaveChatRoom:(NSString *)roomName;


/*!
    @method     inviteHandles:toChatRoom:withMessage:

    @discussion Messages calls this method on the IMServicePlugIn instance when the user 
                invites handles to a specific chatRoom

    @param      handles   The handles to invite.
    @param      roomName  The name of the room which the user wishes to leave
    @param      message   The invitation message
*/
- (oneway void) inviteHandles:(NSArray *)handles toChatRoom:(NSString *)roomName withMessage:(IMServicePlugInMessage *)message;


/*!
    @method     sendMessage:toChatRoom:

    @discussion Messages calls this method on the IMServicePlugIn instance when the user sends
                a message to a chat room.

                The service plug-in should use -plugInDidSendMessage:toChatRoom:error: to report 
                delivery of the message.
                
                Some instant messaging services do not report message delivery status of
                messages sent to chat rooms.  Instead, the message is received in a similar
                fashion to other incoming chat room messages.  In this case, the service
                plug-in may choose to reflect successful message delievery status via
                a call to -plugInDidReceiveMessage:forChatRoom:fromHandle:, with the handle
                parameter set to the handle name.

    @param      message  The message to send.
    @param      roomName The recipient chat room.
*/
- (oneway void) sendMessage:(IMServicePlugInMessage *)message toChatRoom:(NSString *)roomName;


/*!
    @method     declineChatRoomInvitation:

    @discussion Messages calls this method on the IMServicePlugIn instance when the user clicks
                the "Decline" button of an incoming chat room invitation.
                
                This method is always called in response to Messages receiving
                -plugInDidReceiveInvitation:forChatRoom:fromHandle: from the service plug-in.

    @param      roomName  The name of the room which the user has declined.
*/
- (oneway void) declineChatRoomInvitation:(NSString *)roomName;

@end


#pragma mark -
#pragma mark IMServiceApplication (Service Plug-in -> Messages)

@protocol IMServiceApplicationChatRoomSupport <IMServiceApplication>

/*!
    @method     plugInDidReceiveInvitation:forChatRoom:fromHandle:

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                displays an invitation window from the specified handle for the chat room.

                If the user clicks "Accept" on the window, Messages then calls -joinChatRoom: on the
                service plug-in.  If the user clicks "Decline", Messages calls -declineChatRoomInvitation:
                instead.

    @param      invitation An invitation message.  If nil, Messages uses a default invitation message.
    @param      roomName   The name of the chat room.
    @param      handle     The handle of the inviter.
*/
- (oneway void) plugInDidReceiveInvitation:(IMServicePlugInMessage *)invitation forChatRoom:(NSString *)roomName fromHandle:(NSString *)handle;


/*!
    @method     plugInDidReceiveMessage:forChatRoom:fromHandle:

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                appends the sender and message to the transcript for the specified chat room.
                 
                This call may be used to indicate successful delivery of a message sent via
                -sendMessage:toChatRoom:

    @param      message    The message.
    @param      roomName   The name of the chat room.
    @param      handle     The sender of the message.
*/
- (oneway void) plugInDidReceiveMessage:(IMServicePlugInMessage *)message forChatRoom:(NSString *)roomName fromHandle:(NSString *)handle;


/*!
    @method     plugInDidReceiveNotice:forChatRoom:

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                appends an information message to the transcript for the specified chat room.

                Since the IMServicePlugIn API does not support chat room properties such as topic,
                moderator status, or chat room settings; clients may use this method to display
                additional information which would otherwise be hidden to the user.

    @param      notice    An informational message to be displayed.
    @param      roomName  The name of the chat room.
*/
- (oneway void) plugInDidReceiveNotice:(NSString *)notice forChatRoom:(NSString *)roomName;


/*!
    @method     plugInDidSendMessage:toChatRoom:error:

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                appends the message to the transcript for the specified chat room.
                 
                This call may be used to indicate successful delivery of a message sent via
                -sendMessage:toChatRoom:

    @param      message    The message.
    @param      roomName   The name of the chat room.
    @param      error      An error, if one occurred during message delivery.
*/
- (oneway void) plugInDidSendMessage:(IMServicePlugInMessage *)message toChatRoom:(NSString *)roomName error:(NSError *)error;


/*!
    @method     plugInDidJoinChatRoom:

    @discussion When the IMServicePlugIn instance calls this method on the service application, Messages
                indicates to the user that the specified chat room is now joined and ready to receive
                messages.
                 
                This call should be used in response to joinChatRoom: being called on the service plug-in.

    @param      roomName   The name of the chat room
*/
- (oneway void) plugInDidJoinChatRoom:(NSString *)roomName;


/*!
    @method     plugInDidLeaveChatRoom:error:

    @discussion The IMServicePlugIn should call this method on the service application to indiciate that
                a chat room has been successfully left, and that the user may attempt to re-enter that
                room in the future.

                This call may also be used in response to joinChatRoom: to indicate that an error occurred
                while joining the room.

    @param      roomName   The name of the chat room.
    @param      error      An error, if any, which caused the user to be removed from the chat room,
                           or prevented the user from joining the chat room.
*/
- (oneway void) plugInDidLeaveChatRoom:(NSString *)roomName error:(NSError *)error;


/*!
    @method     handles:didJoinChatRoom:

    @discussion The IMServicePlugIn should call this method on the service application to indiciate that
                a handle, or multiple handles, have joined the chat room.

                This method may also be used after plugInDidJoinChatRoom: to report the initial list
                of chat room members.

    @param      handles   An NSArray of NSString objects, corresponding to the handles which joined the room.
    @param      roomName  The name of the chat room.
*/
- (oneway void) handles:(NSArray *)handles didJoinChatRoom:(NSString *)roomName;


/*!
    @method     handles:didLeaveChatRoom:

    @discussion The IMServicePlugIn should call this method on the service application to indiciate that
                a handle, or multiple handles, have left or been removed from the chat room.

    @param      handles   An NSArray of NSString objects, corresponding to the handles which left the room.
    @param      roomName  The name of the chat room.
*/
- (oneway void) handles:(NSArray *)handles didLeaveChatRoom:(NSString *)roomName;


@end
