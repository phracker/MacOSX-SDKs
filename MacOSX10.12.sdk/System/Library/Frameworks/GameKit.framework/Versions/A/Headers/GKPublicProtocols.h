/*
 GKPublicProtocols.h
 GameKit
 
 Copyright 2010 Apple Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <GameKit/GKPublicConstants.h>

@class GKSession;
@protocol GKSessionDelegate;

NS_ASSUME_NONNULL_BEGIN

/* Callbacks to the GKSession delegate.
*/
@protocol GKSessionDelegate <NSObject>

@optional

/* Indicates a state change for the given peer.
*/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (void)session:(GKSession *)session peer:(NSString *)peerID didChangeState:(GKPeerConnectionState)state;
#pragma clang diagnostic pop

/* Indicates a connection request was received from another peer. 
 
Accept by calling -acceptConnectionFromPeer:
Deny by calling -denyConnectionFromPeer:
*/
- (void)session:(GKSession *)session didReceiveConnectionRequestFromPeer:(NSString *)peerID;

/* Indicates a connection error occurred with a peer, which includes connection request failures, or disconnects due to timeouts.
*/
- (void)session:(GKSession *)session connectionWithPeerFailed:(NSString *)peerID withError:(NSError *)error;

/* Indicates an error occurred with the session such as failing to make available.
*/
- (void)session:(GKSession *)session didFailWithError:(NSError *)error;

@end


@class GKVoiceChatService;

//All clients will need to implement this protocol
@protocol GKVoiceChatClient <NSObject>

@required

//this channel will only be used to setup voice chat, and not to send audio data. The only requirement is that messages are sent and received within a few (1-2) seconds time.
- (void)voiceChatService:(GKVoiceChatService *)voiceChatService sendData:(NSData *)data toParticipantID:(NSString *)participantID; //must be sent within some reasonble period of time and should accept at least 512 bytes.

- (NSString *)participantID; // voice chat client's participant ID

@optional

//should be sent immediately with no delay on a UDP peer-to-peer connection.  
// If this method is implemented, then the Voice Chat Service will not attempt to set up a peer-to-peer connection. And will rely on this one.  To transmit audio.
- (void)voiceChatService:(GKVoiceChatService *)voiceChatService sendRealTimeData:(NSData *)data toParticipantID:(NSString *)participantID;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didStartWithParticipantID:(NSString *)participantID;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didNotStartWithParticipantID:(NSString *)participantID error:(nullable NSError *)error;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didStopWithParticipantID:(NSString *)participantID error:(nullable NSError *)error;

- (void)voiceChatService:(GKVoiceChatService *)voiceChatService didReceiveInvitationFromParticipantID:(NSString *)participantID callID:(NSInteger)callID;

@end

NS_ASSUME_NONNULL_END
