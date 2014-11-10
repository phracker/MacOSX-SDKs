//
//  MCSession.h
//  MultipeerConnectivity
//
//  Copyright 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MCPeerID.h"
#import "MCError.h"

// MCSession send modes for the -sendData:toPeers:withMode:error: method
typedef NS_ENUM(NSInteger, MCSessionSendDataMode) {
    MCSessionSendDataReliable,      // guaranteed reliable and in-order delivery
    MCSessionSendDataUnreliable     // sent immediately without queuing, no guaranteed delivery
} NS_ENUM_AVAILABLE(10_10,7_0);

// Peer states
typedef NS_ENUM(NSInteger, MCSessionState) {
    MCSessionStateNotConnected,     // not in the session
    MCSessionStateConnecting,       // connecting to this peer
    MCSessionStateConnected         // connected to the session
} NS_ENUM_AVAILABLE(10_10,7_0);

// Encryption preference
typedef NS_ENUM(NSInteger, MCEncryptionPreference) {
    MCEncryptionOptional                = 0,    // session preferred encryption but will accept unencrypted connections
    MCEncryptionRequired                = 1,    // session requires encryption
    MCEncryptionNone                    = 2,    // session should not be encrypted
} NS_ENUM_AVAILABLE(10_10,7_0);

// Minimum number of peers in a session
MC_EXTERN NSUInteger const kMCSessionMinimumNumberOfPeers NS_AVAILABLE(10_10,7_0);

// Maximum number of peers in a session
MC_EXTERN NSUInteger const kMCSessionMaximumNumberOfPeers NS_AVAILABLE(10_10,7_0);

@class NSProgress;
@protocol MCSessionDelegate;

/*!
 @class MCSession
 @abstract 
 A MCSession facilitates communication among all peers in a multipeer 
 session.
 
 @discussion
 To start a multipeer session with remote peers, a MCPeerID that 
 represents the local peer needs to be supplied to the init method.
 
 Once a peer is added to the session on both sides, the delegate 
 callback -session:peer:didChangeState: will be called with 
 MCSessionStateConnected state for the remote peer.
 
 Data messages can be sent to a connected peer with the -sendData:
 toPeers:withMode:error: method.
 
 The receiver of data messages will receive a delegate callback 
 -session:didReceiveData:fromPeer:.
 
 Resources referenced by NSURL (e.g. a file) can be sent to a connected 
 peer with the -sendResourceAtURL:toPeer:withTimeout:completionHandler: 
 method. The completionHandler will be called when the resource is fully
 received by the remote peer, or if an error occurred during 
 transmission. The receiver of data messages will receive a delegate 
 callbacks -session:didStartReceivingResourceWithName:fromPeer:
 withProgress: when it starts receiving the resource and -session:
 didFinishReceivingResourceWithName:fromPeer:atURL:withError: 
 when the resource has been fully received.
 
 A byte stream can be sent to a connected peer with the 
 -startStreamWithName:toPeer:error: method. On success, an 
 NSOutputStream  object is returned, and can be used to send bytes to 
 the remote peer once the stream is properly set up. The receiver of the
 byte stream will receive a delegate callback -session:didReceiveStream:
 withName:fromPeer:
 
 Delegate calls occur on a private serial queue. If your app needs to
 perform an action on a particular run loop or operation queue, its
 delegate method should explicitly dispatch or schedule that work.
 */
NS_CLASS_AVAILABLE(10_10,7_0)
@interface MCSession : NSObject

// Create a session with an MCPeerID for the local peer
- (instancetype)initWithPeer:(MCPeerID *)myPeerID;

// Create a session with a security configuration
//   The securityIdentity argument is an array of
//   [ SecIdentityRef, [ zero or more additional certs ]].
- (instancetype)initWithPeer:(MCPeerID *)myPeerID securityIdentity:(NSArray *)identity encryptionPreference:(MCEncryptionPreference)encryptionPreference NS_DESIGNATED_INITIALIZER;

// Send a data message to a list of destination peers
- (BOOL)sendData:(NSData *)data toPeers:(NSArray *)peerIDs withMode:(MCSessionSendDataMode)mode error:(NSError **)error;

// Disconnect from the session
- (void)disconnect;

/*
 Send a resource referenced by an NSURL to a remote peer. The resource
 can be a file or an HTTP document. The completionHandler is called when 
 the resource is received by the remote peer or if an error occurred. 
 The remote peer will get a -session:didStartReceivingResourceWithName:
 fromPeer:withProgress callback when it starts receiving the resource and 
 a -session:didFinishReceivingResourceWithName:fromPeer:atURL:withError:
 when the resource has been fully received.
 
 The primary mechanism for observing progress of the send should be to 
 create an NSProgress using +progressWithTotalUnitCount, 
 -becomeCurrentWithPendingUnitCount:, invoking this method, then calling 
 -resignCurrent. This is described in the NSProgress documentation. 
 Alternatively, if you wish to observe the progress directly instead 
 of incorporating it into a larger operation, you may observe the 
 NSProgress returned from this method.
 */
- (NSProgress *)sendResourceAtURL:(NSURL *)resourceURL withName:(NSString *)resourceName toPeer:(MCPeerID *)peerID withCompletionHandler:(void(^)(NSError *error))completionHandler;

// Start a named byte stream with the remote peer
- (NSOutputStream *)startStreamWithName:(NSString *)streamName toPeer:(MCPeerID *)peerID error:(NSError **)error;

@property (weak, NS_NONATOMIC_IOSONLY) id<MCSessionDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCPeerID *myPeerID;

@property (readonly, NS_NONATOMIC_IOSONLY) NSArray *securityIdentity;

@property (readonly, NS_NONATOMIC_IOSONLY) MCEncryptionPreference encryptionPreference;

@property (readonly, NS_NONATOMIC_IOSONLY) NSArray *connectedPeers;

@end


// Delegate methods for MCSession
@protocol MCSessionDelegate <NSObject>

// Remote peer changed state
- (void)session:(MCSession *)session peer:(MCPeerID *)peerID didChangeState:(MCSessionState)state;

// Received data from remote peer
- (void)session:(MCSession *)session didReceiveData:(NSData *)data fromPeer:(MCPeerID *)peerID;

// Received a byte stream from remote peer
- (void)session:(MCSession *)session didReceiveStream:(NSInputStream *)stream withName:(NSString *)streamName fromPeer:(MCPeerID *)peerID;

// Start receiving a resource from remote peer
- (void)session:(MCSession *)session didStartReceivingResourceWithName:(NSString *)resourceName fromPeer:(MCPeerID *)peerID withProgress:(NSProgress *)progress;

// Finished receiving a resource from remote peer and saved the content in a temporary location - the app is responsible for moving the file to a permanent location within its sandbox
- (void)session:(MCSession *)session didFinishReceivingResourceWithName:(NSString *)resourceName fromPeer:(MCPeerID *)peerID atURL:(NSURL *)localURL withError:(NSError *)error;

@optional

// Made first contact with peer and have identity information about the remote peer (certificate may be nil)
- (void)session:(MCSession *)session didReceiveCertificate:(NSArray *)certificate fromPeer:(MCPeerID *)peerID certificateHandler:(void(^)(BOOL accept))certificateHandler;

@end


/*
 If the developer chooses to write their own discovery code (with 
 NetServices, or the Bonjour C API directly), instead of using 
 MCNearbyServiceAdvertiser/Browser or MCBrowserViewController, one can 
 add a remote peer to a MCSession by following these steps:
 
 1. Exchange MCPeerID with the remote peer.  Start by serializing the 
    MCPeerID object with NSKeyedArchiver, exchange the data with 
    the remote peer, and then reconstruct the remote MCPeerID object 
    with NSKeyedUnarchiver.
 2. Exchange connection data with the remote peer.  Start by calling the
    session's -nearbyConnectionDataForPeer:completionHandler: and send 
    the connection data to the remote peer, once the completionHandler 
    is called.
 3. When the remote peer's connection data is received, call the 
    session's -connectPeer:withNearbyConnectionData: method to add the 
    remote peer to the session.
 */

@interface MCSession (MCSessionCustomDiscovery)

// Gets the connection data for a remote peer
- (void)nearbyConnectionDataForPeer:(MCPeerID *)peerID withCompletionHandler:(void(^)(NSData *connectionData, NSError *error))completionHandler;

// Connect a peer to the session once connection data is received
- (void)connectPeer:(MCPeerID *)peerID withNearbyConnectionData:(NSData *)data;

// Cancel connection attempt with a peer
- (void)cancelConnectPeer:(MCPeerID *)peerID;

@end
