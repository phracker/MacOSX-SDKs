//
// MCNearbyServiceBrowser.h
// MultipeerConnectivity
//
// Copyright 2013 Apple Inc. All rights reserved.
//

#import <MultipeerConnectivity/MCPeerID.h>
#import <MultipeerConnectivity/MCSession.h>

@protocol MCNearbyServiceBrowserDelegate;

//
// @class MCNearbyServiceBrowser
//   @abstract
//      MCNearbyServiceBrowser looks for nearby peers, and connects them to
//      sessions.
//
//   @discussion
//      To create the MCNearbyServiceBrowser object and start browsing for
//      nearby peers, a new MCPeerID should be created to represent the local
//      peer, and a service type needs to be specified.
//
//      The serviceType parameter is a short text string used to describe the
//      app's networking protocol.  It should be in the same format as a
//      Bonjour service type: up to 15 characters long and valid characters
//      include ASCII lowercase letters, numbers, and the hyphen.  A short name
//      that distinguishes itself from unrelated services is recommended; for
//      example, a text chat app made by ABC company could use the service type
//      "abc-txtchat". For more detailed information about service type
//      restrictions, see RFC 6335, Section 5.1.
//
//      A delegate that conforms to the MCNearbyServiceBrowserDelegate
//      protocol must also be provided.  The delegate is notified when nearby
//      peers are found and lost. No assumption should be made as to which queue
//      the callbacks are called on.
//
//      MCNearbyAdvertiser must be initialized with an MCPeerID object and a
//      valid service type.
//
//      See Bonjour APIs https://developer.apple.com/bonjour/ for more
//      information about service types.
//
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCNearbyServiceBrowser : NSObject
- (instancetype)initWithPeer:(MCPeerID *)myPeerID serviceType:(NSString *)serviceType NS_DESIGNATED_INITIALIZER;

// The methods -startBrowsingForPeers and -stopBrowsingForPeers are used to
// start and stop looking for nearby advertising peers.
- (void)startBrowsingForPeers;
- (void)stopBrowsingForPeers;

// The method -invitePeer:toSession:withContext:timeout: sends an
// invitation to a peer, and when the peer accepts the invitation, adds
// the peer to the specified session.
//
// The invited peer will receive a -advertiser:
// didReceiveInvitationFromPeer:withContext:invitationHandler: callback.
// The context is passed through to the invited peer. It can be used to
// describe the session or pass some additional identification
// information to the invitee.
//
// The timeout parameter is seconds and should be a positive value.  If a
// timeout of <=0 is specified, a default value of 30 seconds will be
// used instead.
- (void)invitePeer:(MCPeerID *)peerID
         toSession:(MCSession *)session
       withContext:(nullable NSData *)context
           timeout:(NSTimeInterval)timeout;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCNearbyServiceBrowserDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY) MCPeerID *myPeerID;
@property (readonly, NS_NONATOMIC_IOSONLY) NSString *serviceType;

@end

@protocol MCNearbyServiceBrowserDelegate <NSObject>
// Found a nearby advertising peer.
- (void)        browser:(MCNearbyServiceBrowser *)browser
              foundPeer:(MCPeerID *)peerID
      withDiscoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info;

// A nearby peer has stopped advertising.
- (void)browser:(MCNearbyServiceBrowser *)browser lostPeer:(MCPeerID *)peerID;

@optional
// Browsing did not start due to an error.
- (void)browser:(MCNearbyServiceBrowser *)browser didNotStartBrowsingForPeers:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
