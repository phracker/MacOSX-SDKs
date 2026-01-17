//
// MCBrowserViewController.h
// MultipeerConnectivity
//
// Copyright (c) 2013 Apple Inc. All rights reserved.
//
// This API provides a system-supplied user interface for selecting and
// connecting to another device for a multiplayer session.
//
// The API introduces MCBrowserViewController for this purpose, and
// should be used in conjunction with the MCSession API.
//

#import <UIKit/UIKit.h>
#import <MultipeerConnectivity/MCNearbyServiceBrowser.h>

@protocol MCBrowserViewControllerDelegate;

//
// @class MCBrowserViewController
//   @abstract The
//      MCBrowserViewController class manages the system-supplied user
//      interface for choosing peers to connect with for multipeer sessions.
//
//   @discussion
//      MCBrowserViewController manages presentation of nearby peers and the
//      invite process for you. The invite process is driven by the user
//      and handled by the peer picker and the MCNearbyServiceBrowser object
//      it holds.
//
//      MCBrowserViewController must be initialized with a
//      MCNearbyServiceBrowser object and a MCSession object at init time.
//      If the browser object's delegate is nil, the browser view controller
//      will set itself as the browser's delegate. The session object will be
//      used by the browser view controller during the invite process.
//      A delegate that conforms to the MCBrowserViewControllerDelegate
//      protocol must also be provided. The delegate is notified to decide
//      whether to present a peer, when the user taps the done button, or when
//      the users taps the cancel button. No assumption should be made as to
//      which queue the callbacks are called on.
//
//      When presented, the browser view controller looks for nearby peers,
//      and allows the user to connect up to the specified maximum number of
//      peers.  When the user taps on a nearby peer, the browser view
//      controller will send an invitation to it.
//
//      When the browser view controller is dismissed, it will stop looking
//      for nearby peers.
//
NS_ASSUME_NONNULL_BEGIN
NS_CLASS_AVAILABLE(10_10, 7_0)
@interface MCBrowserViewController : UIViewController <MCNearbyServiceBrowserDelegate>
// Create a browser view controller with a service type and a session.
- (instancetype)initWithServiceType:(NSString *)serviceType session:(MCSession *)session;
// Create a browser view controller with a programmatic browser and a session.
- (instancetype)initWithBrowser:(MCNearbyServiceBrowser *)browser session:(MCSession *)session NS_DESIGNATED_INITIALIZER;

@property (weak, NS_NONATOMIC_IOSONLY, nullable) id<MCBrowserViewControllerDelegate> delegate;

@property (readonly, NS_NONATOMIC_IOSONLY, nullable) MCNearbyServiceBrowser *browser;
@property (readonly, NS_NONATOMIC_IOSONLY) MCSession *session;
// The minimum number of peers the session should expect.
@property (assign, NS_NONATOMIC_IOSONLY) NSUInteger minimumNumberOfPeers;
// The maximum number of peers the session should expect.
@property (assign, NS_NONATOMIC_IOSONLY) NSUInteger maximumNumberOfPeers;

@end

@protocol MCBrowserViewControllerDelegate <NSObject>
// Notifies the delegate, when the user taps the done button.
- (void)browserViewControllerDidFinish:(MCBrowserViewController *)browserViewController;

// Notifies delegate that the user taps the cancel button.
- (void)browserViewControllerWasCancelled:(MCBrowserViewController *)browserViewController;

@optional
// Notifies delegate that a peer was found; discoveryInfo can be used to
// determine whether the peer should be presented to the user, and the
// delegate should return a YES if the peer should be presented; this method
// is optional, if not implemented every nearby peer will be presented to
// the user.
- (BOOL)browserViewController:(MCBrowserViewController *)browserViewController
      shouldPresentNearbyPeer:(MCPeerID *)peerID
            withDiscoveryInfo:(nullable NSDictionary<NSString *, NSString *> *)info;

@end
NS_ASSUME_NONNULL_END
