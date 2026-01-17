//
//  NISession.h
//  NearbyInteraction
//
//  Copyright © 2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <NearbyInteraction/NIAlgorithmConvergenceStatusReason.h>
#import <NearbyInteraction/NIConfiguration.h>
#import <NearbyInteraction/NIDeviceCapability.h>
#import <NearbyInteraction/NIExport.h>
#import <NearbyInteraction/NIDLTDOAMeasurement.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

@class NINearbyObject;
@class ARSession;

@protocol NISessionDelegate;

/** A sentinel value indicating that the nearby world transform is unavailable */
API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT simd_float4x4 NINearbyObjectWorldTransformNotAvailable NS_SWIFT_UNAVAILABLE("Use optional value semantics");

/**
 Nearby interaction session.
 */
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@interface NISession : NSObject

/**
 Whether or not this device is capable of participating in a nearby interaction session.
 */
@property (class, nonatomic, readonly, getter=isSupported) BOOL supported API_DEPRECATED_WITH_REPLACEMENT("Use deviceCapabilities property and check the supportsPreciseDistanceMeasurement property", ios(14.0, 16.0), watchos(7.3, 9.0)) API_UNAVAILABLE(macos, tvos);

/**
 Get the protocol that describes nearby interaction capabilities on this device.
 @discussion Detailed description on the capability protocol is in NIDeviceCapability.h.
 */
@property (class, nonatomic, readonly) id<NIDeviceCapability> deviceCapabilities API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos);

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
 A unique nearby interaction identifier for this session.

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

/**
 Provide an ARSession object for use with the NISession
 @param session The ARSession to use for camera assistance
 @discussion If not provided, an ARSession will be created automatically if the cameraAssistanceEnabled property on the configuration is YES
 @discussion The developer is responsible for running the ARSession if provided.
 @discussion If the ARConfiguration used to run the session is not compatible with the NISession, the NISession will invalidate with error
 @discussion If the platform does not support camera assistance or an ARSession is provided without enabling cameraAssistanceEnabled property in the NIConfiguration, the NISession will invalidate with error (see NIError.h)
 */
- (void)setARSession:(ARSession*)session NS_SWIFT_NAME(setARSession(_:)) API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos);

/**
 Compute a transform in ARKit's world coordinate system for a given nearby object.
 @param object The nearby object for which to compute the world transform.
 @return The transformation matrix in ARKit world coordinates.
 @discussion When not available returns NINearbyObjectWorldTransformNotAvailable.
 */
- (simd_float4x4)worldTransformForObject:(NINearbyObject *)object API_AVAILABLE(ios(16.0)) API_UNAVAILABLE(watchos) NS_REFINED_FOR_SWIFT;
@end

/**
 Reasons to remove a nearby object.
 */
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
typedef NS_ENUM(NSInteger, NINearbyObjectRemovalReason) {

    /** The system has not received new activity from this object for over the allowed period. */
    NINearbyObjectRemovalReasonTimeout,
    
    /** The peer device has signaled that it will no longer participate in the session.
        This removal reason is delivered on a best effort basis and is not guaranteed to be received. */
    NINearbyObjectRemovalReasonPeerEnded,
} NS_SWIFT_NAME(NINearbyObject.RemovalReason);

/** Expose algorithm state to make it possible for apps to coach users. */
API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
typedef NS_ENUM(NSInteger, NIAlgorithmConvergenceStatus) {
    /** Algorithm convergence status is unknown. */
    NIAlgorithmConvergenceStatusUnknown,
    /** Algorithm is not converged. */
    NIAlgorithmConvergenceStatusNotConverged,
    /** Algorithm is converged. */
    NIAlgorithmConvergenceStatusConverged,
} NS_REFINED_FOR_SWIFT;

API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(macos, tvos)
NI_EXPORT
@interface NIAlgorithmConvergence : NSObject <NSCopying, NSSecureCoding>
@property (nonatomic, readonly) NIAlgorithmConvergenceStatus status NS_REFINED_FOR_SWIFT;
@property (nonatomic, readonly) NSArray<NIAlgorithmConvergenceStatusReason>* reasons NS_SWIFT_UNAVAILABLE("use associated value in .notConverged case of NIAlgorithmConvergenceStatus");

/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


/**
 Delegate for nearby interaction session updates.
 */
API_AVAILABLE(ios(14.0), watchos(7.3)) API_UNAVAILABLE(macos, tvos)
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

/**
Provides configuration data that needs to be shared with the accessory.
@note Shareable configuration data is only provided when running an NINearbyAccessoryConfiguration.
@discussion After invoking this callback, the session will go into a special preparedness state for a limited amount of time.
The interaction on the accessory must start within this time window. If activity is not detected from the accessory, the session will call
the -[session:didRemoveNearbyObjects:reason:] delegate callback. To restart the session, coordinate with the accessory and call -[runWithConfiguration] again.
 
@param session The session which produced the configuration data.
@param shareableConfigurationData The configuration data that needs to be shared with the accessory.
@param object A representation of the accessory as a NINearbyObject. The discoveryToken property will be equal to the one in the configuration used to run the session.
*/
- (void)session:(NISession *)session didGenerateShareableConfigurationData:(NSData *)shareableConfigurationData forObject:(NINearbyObject *)object API_AVAILABLE(ios(15.0), watchos(8.0)) API_UNAVAILABLE(tvos, macos);

/**
 Called when the algorithm state is updated for a specific nearby object.
 @param session the session interacting with this object.
 @param convergence the algoriothm convergence context of the estimator for the session or nearby object
 @param object which nearby object this state was updated, if null, applies to the entire session
 */
- (void)session:(NISession *)session didUpdateAlgorithmConvergence:(NIAlgorithmConvergence *)convergence forObject:(NINearbyObject * _Nullable)object API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(tvos, macos) NS_SWIFT_NAME(session(_:didUpdateAlgorithmConvergence:for:));

/**
 This is called when new updates about DL-TDOA measurement are available.
 
 @note this will only be called after successfully running an NISession with an NIDLTDOAConfiguration.

 @param session The session that updated NI DL-TDOA measurement.
 @param measurements The measurements update from a NI DL-TDOA session
 */
- (void)session:(NISession *)session didUpdateDLTDOAMeasurements:(NSArray<__kindof NIDLTDOAMeasurement *> *)measurements NS_SWIFT_NAME(session(_:didUpdateDLTDOA:)) API_AVAILABLE(ios(26.0)) API_UNAVAILABLE(watchos, tvos, macos, visionos, macCatalyst);

/**
 The delegate may implement this method to be informed that the session started running.

 @param session The session which started running

 @discussion a call to -runWithConfiguration: will result in one of the following outcomes:
 1. The session successfully starts running. This delegate callback will be subsequently invoked.
 2. Resources are not ready, and the session is immediately suspended. This delegate callback will not be invoked.
 3. An error is encountered, and the session is immediately invalidated. This delegate callback will not be invoked.

 This delegate method provides a way to monitor #1.
 Note that #2 and #3 can be monitored by other delegate methods such as -sessionWasSuspended: and -session:didInvalidateWithError:
 */
- (void)sessionDidStartRunning:(NISession *)session API_AVAILABLE(ios(16.0), watchos(9.0)) API_UNAVAILABLE(tvos, macos);

@end
NS_ASSUME_NONNULL_END
