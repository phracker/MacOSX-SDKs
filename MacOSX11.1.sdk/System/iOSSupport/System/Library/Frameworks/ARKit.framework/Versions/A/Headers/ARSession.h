//
//  ARSession.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ARKit/ARConfiguration.h>
#import <ARKit/ARGeoTrackingTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class ARAnchor;
@class ARCamera;
@class ARFrame;
@class ARCollaborationData;
@class ARWorldMap;
@class ARRay;
@class ARRaycastQuery;
@class ARRaycastResult;
@class ARTrackedRaycast;

@protocol ARSessionDelegate;

/**
 Set of options for running the session.
 @discussion These options alter the behavior of calling run on a session.
 Providing no options will result in the default behavior of resuming tracking
 from the last known position and keeping all existing anchors.
 */
API_AVAILABLE(ios(11.0))
typedef NS_OPTIONS(NSUInteger, ARSessionRunOptions) {
    /** The session will reset tracking. */
    ARSessionRunOptionResetTracking           = (1 << 0),
    
    /** The session will remove existing anchors. */
    ARSessionRunOptionRemoveExistingAnchors   = (1 << 1),
    
    /** The session will stop currently active tracked raycasts. */
    ARSessionRunOptionStopTrackedRaycasts     = (1 << 2),

    /** The session will reset scene reconstruction. */
    ARSessionRunOptionResetSceneReconstruction     = (1 << 3)
} NS_SWIFT_NAME(ARSession.RunOptions);

/**
 The ARSession class configures and runs different Augmented Reality techniques on a device.
 */
API_AVAILABLE(ios(11.0))
@interface ARSession : NSObject

/**
 Unique identifier of the running session.
 
 @discussion The identifier may change after calling runWithConfiguration.
 */
@property (atomic, strong, readonly) NSUUID *identifier API_AVAILABLE(ios(13.0));

/**
 A delegate for receiving ARSession updates.
 */
@property (nonatomic, weak, nullable) id <ARSessionDelegate> delegate;

/**
 The dispatch queue on which the delegate calls are performed.
 @discussion If not provided or nil, delegate calls will be performed on the main queue.
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 The current frame of the session.
 */
@property (nonatomic, copy, nullable, readonly) ARFrame *currentFrame;

/**
 The configuration currently being used by the session.
 */
@property (nonatomic, copy, nullable, readonly) ARConfiguration *configuration;


/**
 Runs the session with the provided configuration.
 @discussion Calling run on a session that has already started will
 transition immediately to using the new configuration.
 @param configuration The configuration to use.
 */

- (void)runWithConfiguration:(ARConfiguration *)configuration NS_SWIFT_UNAVAILABLE("Use run(_:options:) instead");


/**
 Runs the session with the provided configuration and options.
 @discussion Calling run on a session that has already started will
 transition immediately to using the new configuration. Options
 can be used to alter the default behavior when transitioning configurations.
 @param configuration The configuration to use.
 @param options The run options to use.
 */

- (void)runWithConfiguration:(ARConfiguration *)configuration options:(ARSessionRunOptions)options NS_SWIFT_NAME(run(_:options:));

/**
 Pauses the session.
 @discussion Once paused, no more updates will be received from the
 session until run is called again.
 */
- (void)pause;

/**
 Adds an anchor to the session.
 @discussion The anchor will be added in the next frame update.
 @param anchor The anchor to add.
 */
- (void)addAnchor:(__kindof ARAnchor *)anchor NS_SWIFT_NAME(add(anchor:));

/**
 Removes an anchor from the session.
 @discussion The anchor will be removed from subsequent frame updates.
 @param anchor The anchor to remove.
 */
- (void)removeAnchor:(__kindof ARAnchor *)anchor NS_SWIFT_NAME(remove(anchor:));

/**
 Sets the world origin of the session to be at the position and orientation specified by the provided transform.
 @param relativeTransform The rotation and translation from the current world origin to the desired world origin.
 Any scale on the transform is ignored.
 */
- (void)setWorldOrigin:(simd_float4x4)relativeTransform NS_SWIFT_NAME(setWorldOrigin(relativeTransform:)) API_AVAILABLE(ios(11.3));

/**
 Copies the current state of the world being tracked by the session.
 @discussion A world map is only provided when running an ARWorldTrackingConfiguration.
 @param completionHandler The completion handler to call when the get has completed. This handler is executed
 on the session's delegate queue. The completion handler takes the following parameters:
 worldMap - The current world map or nil if unavailable.
 error - An error that indicates why the world map is unavailable, or nil if a world map was provided.
 */
- (void)getCurrentWorldMapWithCompletionHandler:(void (^)(ARWorldMap * _Nullable worldMap, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(12.0));

/**
 Creates a new reference object from scanned features within the provided bounds.
 
 @discussion Reference objects can be stored and used to track 3D objects from previously scanned data.
 Creation requires that an ARObjectScanningConfiguration is used so that sufficient features are scanned.
 @param transform The transformation matrix that defines the rotation and translation of the bounds in
 world coordinates. This will be used as the reference object's transform, defining its coordinate space.
 @param center The center of the object's bounds in the transform's coordinate space. A zero vector will
 define the object's origin centered within its extent.
 @param extent The extent of the object's bounds in the transform's coordinate space. This defines the bounds'
 size in each dimension.
 @param completionHandler The completion handler to call when the creation has completed. This handler is executed
 on the session's delegate queue. The completion handler takes the following parameters:
 referenceObject - The reference object created or nil if unavailable.
 error - An error that indicates why creation failed, or nil if a reference object was provided.
 */
- (void)createReferenceObjectWithTransform:(simd_float4x4)transform
                                     center:(simd_float3)center
                                     extent:(simd_float3)extent
                          completionHandler:(void (^)(ARReferenceObject * _Nullable referenceObject, NSError * _Nullable error))completionHandler
NS_SWIFT_NAME(createReferenceObject(transform:center:extent:completionHandler:)) API_AVAILABLE(ios(12.0));

#pragma mark - Raycasting

/**
 Perform a raycast.
 @param query Raycast query used for raycasting.
 @return List of raycast results, sorted from nearest to farthest (in distance from the camera). The results could be empty if raycast fails.
 */
- (NSArray<ARRaycastResult *> *)raycast:(ARRaycastQuery *)query API_AVAILABLE(ios(13.0));

/**
 Perform a tracked raycast.
 @discussion The session performs continuous raycasting and calls the update handler with the updated results.
 The ARTrackedRaycast object returned can be used to update the raycast with a new raycast query or stop raycasting.
 @param query Raycast query used for raycasting.
 @param updateHandler update handler where updated list of results, sorted from nearest to farthest (in distance from
        the camera) are delivered. updateHandler will be called on session's delegate queue.
 @return Tracked raycast object used to update or stop raycasting. This could be nil if the raycast fails or if the
         configuration is not `ARWorldTrackingConfiguration` or its subclasses.
 */
- (nullable ARTrackedRaycast *)trackedRaycast:(ARRaycastQuery *)query updateHandler:(void (^)(NSArray<ARRaycastResult *> *))updateHandler API_AVAILABLE(ios(13.0));

#pragma mark - Collaboration

/**
 Update session with collaboration data.
 
 @discussion Use this to update the session with collaboration data received from other participants.
 
 @param collaborationData Collaboration data for updating the session.
 @see ARCollaborationData
 */
- (void)updateWithCollaborationData:(ARCollaborationData *)collaborationData API_AVAILABLE(ios(13.0));

#pragma mark - Geo Tracking


/**
 Converts a position in world coordinate system into latitude, longitude and altitude.
 
 @discussion This method requires the session to be running a geo tracking configuration which is in state ARGeoTrackingStateLocalized.
 
 @param position Position in world coordinate system to be converted.
 @param completionHandler Completion handler to be called with the result. This handler is executed on the session's delegate queue. It has the parameters:
        coordinate - Location coordinates.
        altitude - Altitude.
        error - Error if conversion is not available.
 */
- (void)getGeoLocationForPoint:(simd_float3)position completionHandler:(void (^)(CLLocationCoordinate2D coordinate, CLLocationDistance altitude, NSError * _Nullable error))completionHandler API_AVAILABLE(ios(14.0));


@end


#pragma mark - ARSessionObserver


API_AVAILABLE(ios(11.0))
@protocol ARSessionObserver <NSObject>

@optional

/**
 This is called when a session fails.
 
 @discussion On failure the session will be paused.
 @param session The session that failed.
 @param error The error being reported (see ARError.h).
 */
- (void)session:(ARSession *)session didFailWithError:(NSError *)error;

/**
 This is called when the camera’s tracking state has changed.
 
 @param session The session being run.
 @param camera The camera that changed tracking states.
 */
- (void)session:(ARSession *)session cameraDidChangeTrackingState:(ARCamera *)camera;

/**
 This is called when a session is interrupted.
 
 @discussion A session will be interrupted and no longer able to track when
 it fails to receive required sensor data. This happens when video capture is interrupted,
 for example when the application is sent to the background or when there are
 multiple foreground applications (see AVCaptureSessionInterruptionReason).
 No additional frame updates will be delivered until the interruption has ended.
 @param session The session that was interrupted.
 */
- (void)sessionWasInterrupted:(ARSession *)session;

/**
 This is called when a session interruption has ended.
 
 @discussion A session will continue running from the last known state once
 the interruption has ended. If the device has moved, anchors will be misaligned.
 To avoid this, some applications may want to reset tracking (see ARSessionRunOptions)
 or attempt to relocalize (see `-[ARSessionObserver sessionShouldAttemptRelocalization:]`).
 @param session The session that was interrupted.
 */
- (void)sessionInterruptionEnded:(ARSession *)session;

/**
 This is called after a session resumes from a pause or interruption to determine
 whether or not the session should attempt to relocalize.
 
 @discussion To avoid misaligned anchors, apps may wish to attempt a relocalization after
 a session pause or interruption. If YES is returned: the session will begin relocalizing
 and tracking state will switch to limited with reason relocalizing. If successful, the
 session's tracking state will return to normal. Because relocalization depends on
 the user's location, it can run indefinitely. Apps that wish to give up on relocalization
 may call run with `ARSessionRunOptionResetTracking` at any time.
 @param session The session to relocalize.
 @return Return YES to begin relocalizing.
 */
- (BOOL)sessionShouldAttemptRelocalization:(ARSession *)session API_AVAILABLE(ios(11.3));

/**
 This is called when the session outputs a new audio sample buffer.
 
 @param session The session being run.
 @param audioSampleBuffer The captured audio sample buffer.
 */
- (void)session:(ARSession *)session didOutputAudioSampleBuffer:(CMSampleBufferRef)audioSampleBuffer;

/**
 This is called when the session generated new collaboration data.
 
 @discussion This data should be sent to all participants.
 
 @param session The session that produced world tracking collaboration data.
 @param data Collaboration data to be sent to participants.
 @see ARCollaborationData
 */
- (void)session:(ARSession *)session didOutputCollaborationData:(ARCollaborationData *)data API_AVAILABLE(ios(13.0));


/**
 This is called when geo tracking status changes.

 @param session The session being run.
 @param geoTrackingStatus Latest geo tracking status.
 */
- (void)session:(ARSession *)session didChangeGeoTrackingStatus:(ARGeoTrackingStatus*)geoTrackingStatus API_AVAILABLE(ios(14.0));


@end

#pragma mark - ARSessionDelegate


API_AVAILABLE(ios(11.0))
@protocol ARSessionDelegate <ARSessionObserver>

@optional

/**
 This is called when a new frame has been updated.
 
 @param session The session being run.
 @param frame The frame that has been updated.
 */
- (void)session:(ARSession *)session didUpdateFrame:(ARFrame *)frame;

/**
 This is called when new anchors are added to the session.
 
 @param session The session being run.
 @param anchors An array of added anchors.
 */
- (void)session:(ARSession *)session didAddAnchors:(NSArray<__kindof ARAnchor*>*)anchors;

/**
 This is called when anchors are updated.
 
 @param session The session being run.
 @param anchors An array of updated anchors.
 */
- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<__kindof ARAnchor*>*)anchors;

/**
 This is called when anchors are removed from the session.
 
 @param session The session being run.
 @param anchors An array of removed anchors.
 */
- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<__kindof ARAnchor*>*)anchors;

@end

/**
 A data source for an ARSession
 */
@protocol ARSessionProviding <NSObject>

/// To ensure session changes are detected, Swift classes should mark this property as `@objc` and `dynamic`
@property (readonly) ARSession *session;

@end

NS_ASSUME_NONNULL_END
