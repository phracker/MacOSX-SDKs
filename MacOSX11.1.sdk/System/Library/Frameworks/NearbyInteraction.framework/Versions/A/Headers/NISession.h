//
//  NISession.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIConfiguration.h>
#import <NearbyInteraction/NIExport.h>

NS_ASSUME_NONNULL_BEGIN

@class NINearbyObject;

@protocol NISessionDelegate;

/**
 Nearby interaction session.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
NI_EXPORT
@interface NISession : NSObject

/**
 Whether or not this device is capable of participating in a nearby interaction session.
 */
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported;

/**
 A delegate for receiving NISession updates.
 */
@property (nonatomic, weak, nullable) id <NISessionDelegate> delegate;

/**
 The dispatch queue on which the delegate calls are performed.
 @discussion If not provided or nil, delegate calls will be performed on the main queue.
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 A unique nearby interaction identifer for this session.

 @discussion Copy this discoveryToken and share it with a peer device.
 The discoveryToken is unique to this device and this session.
*/
@property (nonatomic, copy, nullable, readonly) NIDiscoveryToken *discoveryToken;

/**
 The nearby interaction configuration currently being used by the session.
 */
@property (nonatomic, copy, nullable, readonly) NIConfiguration *configuration;

/**
 Start a nearby interaction session.
 @param configuration Nearby interaction configuration for this session.
 Both devices must call -runWithConfiguration: with a valid configuration identifying the other device in order to receive nearby object updates.
*/
- (void)runWithConfiguration:(NIConfiguration *)configuration NS_SWIFT_NAME(run(_:));

/**
 Pause an ongoing nearby interaction session.
 @discussion Paused sessions may be restarted by calling -runWithConfiguration:. The same local discoveryToken will be used.
*/
- (void)pause;

/**
 Invalidate an ongoing nearby interaction session.
 @discussion Invalidate sessions you wish to terminate and do not intend to restart. A peer device in a nearby interaction session will receive a callback to -didRemoveNearbyObject:withReason: some time after a call to invalidate (see NINearbyObjectRemovalReason).
 calling -runWithConfiguration: after invalidation will result in an error.
*/
- (void)invalidate;

@end

/**
 Reasons to remove a nearby object.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ENUM(NSInteger, NINearbyObjectRemovalReason) {

    /** The system has not received new activity from this object for over the allowed period. */
    NINearbyObjectRemovalReasonTimeout,
    
    /** The peer device has signaled that it will no longer participate in the session.
        This removal reason is delivered on a best effort basis and is not guaranteed to be received. */
    NINearbyObjectRemovalReasonPeerEnded,
} NS_SWIFT_NAME(NINearbyObject.RemovalReason);

/**
 Delegate for nearby interaction session updates.
 */
API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol NISessionDelegate <NSObject>

@optional

/**
 This is called when new updates about nearby objects are available.
 @param session The nearby interaction session being run.
 @param nearbyObjects The nearby objects that have been updated.
*/
- (void)session:(NISession *)session didUpdateNearbyObjects:(NSArray<__kindof NINearbyObject *> *)nearbyObjects NS_SWIFT_NAME(session(_:didUpdate:));

/**
 This is called when the system is no longer attempting to interact with some nearby objects.
 @discussion The system was unable to interact with a peer device for some time, or the peer device signaled that it is leaving the session. After this callback is received, the session with the peer is no longer active. To retry interacting with the peer, issue a new call to -runWithConfiguration:.
 @param session The nearby interaction session that removed the nearby object(s).
 @param nearbyObjects The nearby objects that were removed.
 @param reason The reason the nearby object(s) were removed.  All objects in nearbyObjects are removed for the same reason. If multiple nearby objects are removed for different reasons, -didRemoveNearbyObjects:reason: will be called multiple times.
*/
- (void)session:(NISession *)session didRemoveNearbyObjects:(NSArray<__kindof NINearbyObject *> *)nearbyObjects withReason:(NINearbyObjectRemovalReason)reason NS_SWIFT_NAME(session(_:didRemove:reason:));

/**
 This is called when a session is suspended.
 @discussion A session will be suspended in various app and system scenarios.
 A suspended session may be run again only after -sessionSuspensionEnded: has been called.  Restart a session by issuing a new call to -runWithConfiguration:.
 @param session The nearby interaction session that was suspended.
*/
- (void)sessionWasSuspended:(NISession *)session;

/**
 This is called when a session may be resumed.
 @param session The nearby interaction session that was suspended.
*/
- (void)sessionSuspensionEnded:(NISession *)session;

/**
 This is called when a session is invalidated.
 @param session The session that has become invalid. Your app should discard any references it has to this session.
 @param error The error indicating the reason for invalidation of the session (see NIError.h).
*/
- (void)session:(NISession *)session didInvalidateWithError:(NSError *)error NS_SWIFT_NAME(session(_:didInvalidateWith:));

@end

NS_ASSUME_NONNULL_END
