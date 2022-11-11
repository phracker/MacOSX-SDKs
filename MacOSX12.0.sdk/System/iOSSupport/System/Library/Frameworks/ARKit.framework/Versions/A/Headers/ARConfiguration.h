//
//  ARConfiguration.h
//  ARKit
//
//  Copyright © 2016-2021 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreLocation/CoreLocation.h>

#import <ARKit/ARPlaneDetectionTypes.h>

NS_ASSUME_NONNULL_BEGIN

@class ARReferenceImage;
@class ARReferenceObject;
@class ARVideoFormat;
@class ARWorldMap;


/**
Option set indicating semantic understanding types of the image frame.
*/
API_AVAILABLE(ios(13.0))
typedef NS_OPTIONS(NSUInteger, ARFrameSemantics) {
    /** No semantic operation is run. */
    ARFrameSemanticNone                                = 0,

    /**
     Person segmentation.
     @discussion A pixel in the image frame that gets classified as person will have an intensity value equal to 'ARSegmentationClassPerson'.
     @see -[ARFrame segmentationBuffer]
     @see ARSegmentationClass
    */
    ARFrameSemanticPersonSegmentation                  = (1 << 0),
    
    /**
     Person segmentation with depth.
     @discussion A pixel in the image frame that gets classified as person will have an intensity value equal to 'ARSegmentationClassPerson'.
     Additionally, every pixel in the image frame that gets classified as person will also have a depth value.
     @see -[ARFrame estimatedDepthData]
     @see -[ARFrame segmentationBuffer]
     */
    ARFrameSemanticPersonSegmentationWithDepth         = (1 << 1) | (1 << 0),
    
    /**
     Body detection.
     @discussion Once activated an ARFrame will contain information about a detected body.
     @see -[ARFrame detectedBody]
     @see ARBody2D
     */
    ARFrameSemanticBodyDetection                       = (1 << 2),
    
    /**
     Scene Depth.
     @discussion Each capturedImage will have an associated scene depth data.
     @see - [ARFrame sceneDepth]
    */
    ARFrameSemanticSceneDepth API_AVAILABLE(ios(14.0)) = (1 << 3),
    
    /**
     Smoothed Scene Depth.
     @discussion Each capturedImage will have an associated scene depth data that is temporally smoothed.
     @see - [ARFrame smoothedSceneDepth]
    */
    ARFrameSemanticSmoothedSceneDepth API_AVAILABLE(ios(14.0)) = (1 << 4),
    
} NS_SWIFT_NAME(ARConfiguration.FrameSemantics);

/**
 Enum constants for indicating the world alignment.
 */
API_AVAILABLE(ios(11.0))
typedef NS_ENUM(NSInteger, ARWorldAlignment) {
    /** Aligns the world with gravity that is defined by vector (0, -1, 0). */
    ARWorldAlignmentGravity,
    
    /** Aligns the world with gravity that is defined by the vector (0, -1, 0)
     and heading (w.r.t. True North) that is given by the vector (0, 0, -1). */
    ARWorldAlignmentGravityAndHeading,
    
    /** Aligns the world with the camera’s orientation. */
    ARWorldAlignmentCamera
} NS_SWIFT_NAME(ARConfiguration.WorldAlignment);


/**
 Enum constants for indicating the mode of environment texturing to run.
 */
API_AVAILABLE(ios(12.0))
typedef NS_ENUM(NSInteger, AREnvironmentTexturing) {
    /** No texture information is gathered. */
    AREnvironmentTexturingNone,
    
    /** Texture information is gathered for the environment.
     Environment textures will be generated for AREnvironmentProbes added to the session. */
    AREnvironmentTexturingManual,
    
    /** Texture information is gathered for the environment and probes automatically placed in the scene. */
    AREnvironmentTexturingAutomatic
} NS_SWIFT_NAME(ARWorldTrackingConfiguration.EnvironmentTexturing);



/**
 Types of scene reconstruction.
 */
API_AVAILABLE(ios(13.4))
typedef NS_OPTIONS(NSUInteger, ARSceneReconstruction) {
    /** No scene reconstruction is run. */
    ARSceneReconstructionNone                   = 0,
    
    /** Scene reconstruction generates a mesh of the world */
    ARSceneReconstructionMesh                   = (1 << 0),
    
    /** Scene reconstruction generates a mesh of the world with classification for each face. */
    ARSceneReconstructionMeshWithClassification = (1 << 1) | (1 << 0)
} NS_SWIFT_NAME(ARConfiguration.SceneReconstruction);


/**
 An object to describe and configure the Augmented Reality techniques to be used in an ARSession.
 */
API_AVAILABLE(ios(11.0))
@interface ARConfiguration : NSObject <NSCopying>

/**
 Determines whether this device supports the ARConfiguration.
 */
@property (class, nonatomic, readonly) BOOL isSupported;

/**
 A list of supported video formats for this configuration and device.
 @discussion The first element in the list is the default format for session output.
 */
@property (class, nonatomic, readonly) NSArray<ARVideoFormat *> *supportedVideoFormats API_AVAILABLE(ios(11.3));

/**
 Video format of the session output.
 */
@property (nonatomic, strong) ARVideoFormat *videoFormat API_AVAILABLE(ios(11.3));

/**
 Determines how the coordinate system should be aligned with the world.
 @discussion The default is ARWorldAlignmentGravity.
 */
@property (nonatomic, assign) ARWorldAlignment worldAlignment;

/**
 Enable or disable light estimation.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isLightEstimationEnabled) BOOL lightEstimationEnabled;

/**
 Determines whether to capture and provide audio data.
 @discussion Disabled by default.
 */
@property (nonatomic, assign) BOOL providesAudioData;

/**
 The type of semantic understanding to provide with each frame.

 @discussion Use the `supportsFrameSemantics` class method to check if the configuration type you intend to run supports the set of frame semantics. For example, when running a session with
 a configuration of type ARWorldTrackingConfiguration one would need to use `+[ ARWorldTrackingConfiguration supportsFrameSemantics:]` to perform said check.
 An exception is thrown if the option
 is not supported. Defaults to ARFrameSemanticNone.
 @see ARFrameSemantics
 @see +[ARConfiguration supportsFrameSemantics:]
*/
@property (nonatomic, assign) ARFrameSemantics frameSemantics API_AVAILABLE(ios(13.0));

/**
 Determines whether the type of frame semantics is supported by the device and ARConfiguration class.

 @discussion Semantic frame understanding is not supported on all devices. Use the `supportsFrameSemantics` class method to check if the configuration type you intend to run supports the
 set of frame semantics. For example, when running a session with a configuration of type ARWorldTrackingConfiguration one would need to use
 `+[ ARWorldTrackingConfiguration supportsFrameSemantics:]` to perform said check.
 @see ARFrameSemantics
*/
+ (BOOL)supportsFrameSemantics:(ARFrameSemantics)frameSemantics API_AVAILABLE(ios(13.0));


/** Unavailable */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end


/**
 A configuration for running world tracking.
 
 @discussion World tracking provides 6 degrees of freedom tracking of the device.
 By finding feature points in the scene, world tracking enables performing hit-tests against the frame.
 Tracking can no longer be resumed once the session is paused.
 */
API_AVAILABLE(ios(11.0))
@interface ARWorldTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

/**
 The mode of environment texturing to run.
 @discussion If set, texture information will be accumulated and updated. Adding an AREnvironmentProbeAnchor to the session
 will get the current environment texture available from that probe's perspective which can be used for lighting
 virtual objects in the scene. Defaults to AREnvironmentTexturingNone.
 */
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing API_AVAILABLE(ios(12.0));

/**
 Determines whether environment textures will be provided with high dynamic range. Enabled by default.
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures API_AVAILABLE(ios(13.0));


/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap API_AVAILABLE(ios(12.0));

/**
 Images to detect in the scene.
 @discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
 */
@property (nonatomic, copy, null_resettable) NSSet<ARReferenceImage *> *detectionImages API_AVAILABLE(ios(11.3));

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of an image.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the estimated one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARImageAnchor.
 @note When set to true the transform of a returned ARImageAnchor will use the estimated scale factor to correct the translation. Default value is NO.
  */
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled API_AVAILABLE(ios(13.0));

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Images will continue to be detected regardless of images tracked. Default value is zero.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages API_AVAILABLE(ios(12.0));

/**
 Objects to detect in the scene.
 @discussion If set the session will attempt to detect the specified objects. When an object is detected an ARObjectAnchor will be added to the session.
 */
@property (nonatomic, copy) NSSet<ARReferenceObject *> *detectionObjects API_AVAILABLE(ios(12.0));

/**
 Enable/disable a collaborative session. Disabled by default.
 
 @discussion When enabled, ARSession will output collaboration data for other participants using its delegate didOutputCollaborationData.
 It is the responsibility of the caller to send the data to each participant. When data is received by a participant, it
 should be passed to the ARSession by calling updateWithCollaborationData.
 */
@property (nonatomic, assign, getter=isCollaborationEnabled) BOOL collaborationEnabled API_AVAILABLE(ios(13.0));

/**
 Indicates whether user face tracking using the front facing camera can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsUserFaceTracking API_AVAILABLE(ios(13.0));

/**
 Enable or disable running Face Tracking using the front facing camera. Disabled by default.
 When enabled, ARSession detects faces (if visible in the front-facing camera image) and adds to its list of anchors,
 an ARFaceAnchor object representing each face.
 
 @discussion The transform of the ARFaceAnchor objects will be in the world coordinate space.
 @see ARFaceAnchor
 */
@property (nonatomic, assign, getter=userFaceTrackingEnabled) BOOL userFaceTrackingEnabled API_AVAILABLE(ios(13.0));

/**
 Enable or disable app clip code tracking. Disabled by default. When enabled, detected app clip codes will be surfaced as an ARAppClipCodeAnchor.
 */
@property (nonatomic, assign) BOOL appClipCodeTrackingEnabled API_AVAILABLE(ios(14.3));

/**
 Indicates whether app clip code tracking can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsAppClipCodeTracking API_AVAILABLE(ios(14.3));

/**
 Indicates whether the scene reconstruction type is supported for the configuration on this device.
 */
+ (BOOL)supportsSceneReconstruction:(ARSceneReconstruction)sceneReconstruction API_AVAILABLE(ios(13.4));

/**
 Type of scene reconstruction to run. Defaults to ARSceneReconstructionNone.
 @see ARMeshAnchor
 @discussion If set to a value other than ARSceneReconstructionNone, output of scene reconstruction will be added to the session as
 ARMeshAnchor objects.
 */
@property (nonatomic, assign) ARSceneReconstruction sceneReconstruction API_AVAILABLE(ios(13.4));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration for running orientation tracking.
 
 @discussion Orientation tracking provides 3 degrees of freedom tracking of the device.
 */
API_AVAILABLE(ios(11.0))
@interface AROrientationTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled API_AVAILABLE(ios(11.3));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running face tracking.
 
 @discussion Face tracking uses the front facing camera to track the face in 3D providing details on the topology and expression of the face.
 A detected face will be added to the session as an ARFaceAnchor object which contains information about head pose, mesh, eye pose, and blend shape
 coefficients. If light estimation is enabled the detected face will be treated as a light probe and used to estimate the direction of incoming light.
 */
API_AVAILABLE(ios(11.0))
@interface ARFaceTrackingConfiguration : ARConfiguration

/**
 Maximum number of faces which can be tracked simultaneously.
 */
@property (class, nonatomic, readonly) NSInteger supportedNumberOfTrackedFaces API_AVAILABLE(ios(13.0));

/**
 Maximum number of faces to track simultaneously.
 @discussion Setting the maximum number of tracked faces will limit the number of faces that can be tracked in a given frame.
 If more than the maximum is visible, only the faces already being tracked will continue to track until tracking is lost or another face is removed.
 Default value is one.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedFaces API_AVAILABLE(ios(13.0));

/**
 Indicates whether world tracking can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsWorldTracking API_AVAILABLE(ios(13.0));

/**
 Enable or disable World Tracking. Disabled by default.
 
 @discussion When enabled, ARSession uses the back facing camera to track the device's orientation and position in the world. The camera transform and the ARFaceAnchor transform will be in the world coordinate space.
 */
@property (nonatomic, assign, getter=isWorldTrackingEnabled) BOOL worldTrackingEnabled API_AVAILABLE(ios(13.0));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running image tracking.
 
 @discussion Image tracking provides 6 degrees of freedom tracking of known images. Four images may be tracked simultaneously.
 */
API_AVAILABLE(ios(12.0))
@interface ARImageTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 Images to track in the scene.
 */
@property (nonatomic, copy) NSSet<ARReferenceImage *> *trackingImages;

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Default value is one.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for scanning objects.
 
 @discussion The object scanning configuration runs world tracking, capturing additional detail in order to create reference objects.
 Running object scanning will consume additional power in order to provide more detailed features.
 The createReferenceObject method can be called on the session to capture a scan of an object in the world.
 */
API_AVAILABLE(ios(12.0))
@interface ARObjectScanningConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end


/**
 A configuration for running body tracking.
 
 @discussion Body tracking provides 6 degrees of freedom tracking of a detected body in the scene. By default, ARFrameSemanticBodyDetection will be
 enabled.
 @see ARBodyAnchor
 @see -[ARFrame detectedBody]
 */
API_AVAILABLE(ios(13.0))
@interface ARBodyTrackingConfiguration : ARConfiguration

/**
 Enable or disable continuous auto focus.
 @discussion Enabled by default.
 */
@property (nonatomic, assign, getter=isAutoFocusEnabled) BOOL autoFocusEnabled;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap;

/**
 The mode of environment texturing to run.
 @discussion If set, texture information will be accumulated and updated. Adding an AREnvironmentProbeAnchor to the session
 will get the current environment texture available from that probe's perspective which can be used for lighting
 virtual objects in the scene. Defaults to AREnvironmentTexturingNone.
 */
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing;

/**
 Determines whether environment textures will be provided with high dynamic range. Enabled by default.
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures;

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
Images to detect in the scene.
@discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
*/
@property (nonatomic, copy) NSSet<ARReferenceImage *> *detectionImages;

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of an image.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the estimated one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARImageAnchor.
 @note When set to true the transform of a returned ARImageAnchor will use the estimated scale factor to correct the translation. Default value is NO.
 */
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled;

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of a skeleton in 3D.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the default one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARBodyAnchor.
 @note When set to true the transform of a returned ARBodyAnchor will use the estimated scale factor to correct the translation. Default value is NO.
 */
@property (nonatomic, assign) BOOL automaticSkeletonScaleEstimationEnabled;
/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Images will continue to be detected regardless of images tracked. Default value is zero.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

/**
 Enable or disable app clip code tracking. Disabled by default. When enabled, detected app clip codes will be surfaced as an ARAppClipCodeAnchor.
 */
@property (nonatomic, assign) BOOL appClipCodeTrackingEnabled API_AVAILABLE(ios(14.3));

/**
 Indicates whether app clip code tracking can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsAppClipCodeTracking API_AVAILABLE(ios(14.3));

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end

/**
 A configuration for running positional tracking.
 
 @discussion Positional tracking provides 6 degrees of freedom tracking of the device by running the camera at lowest possible resolution and frame rate.
 */
API_AVAILABLE(ios(13.0))
@interface ARPositionalTrackingConfiguration : ARConfiguration

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 The initial map of the physical space that world tracking will localize to and track.
 @discussion If set, the session will attempt to localize to the provided map with
 a limited tracking state until localization is successful or run is called again
 with a different (or no) initial map specified. Once localized, the map will be extended
 and can again be saved using the `getCurrentWorldMap` method on the session.
 */
@property (nonatomic, strong, nullable) ARWorldMap *initialWorldMap;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end



/**
 A configuration for running geographical world tracking.

 @discussion It allows placing geo-referenced anchors (ARGeoAnchor) in the scene by running world tracking with location and compass.
 */
API_AVAILABLE(ios(14.0))
@interface ARGeoTrackingConfiguration : ARConfiguration

/** Unavailable */
@property(nonatomic, assign) ARWorldAlignment worldAlignment NS_UNAVAILABLE;

/**
 The mode of environment texturing to run.
 @discussion If set, texture information will be accumulated and updated. Adding an AREnvironmentProbeAnchor to the session
 will get the current environment texture available from that probe's perspective which can be used for lighting
 virtual objects in the scene. Defaults to AREnvironmentTexturingNone.
 */
@property (nonatomic, assign) AREnvironmentTexturing environmentTexturing;

/**
 Determines whether environment textures will be provided with high dynamic range. Enabled by default.
 */
@property (nonatomic, assign) BOOL wantsHDREnvironmentTextures;

/**
 Type of planes to detect in the scene.
 @discussion If set, new planes will continue to be detected and updated over time. Detected planes will be added to the session as
 ARPlaneAnchor objects. In the event that two planes are merged, the newer plane will be removed. Defaults to ARPlaneDetectionNone.
 */
@property (nonatomic, assign) ARPlaneDetection planeDetection;

/**
 Images to detect in the scene.
 @discussion If set the session will attempt to detect the specified images. When an image is detected an ARImageAnchor will be added to the session.
 */
@property (nonatomic, copy, null_resettable) NSSet<ARReferenceImage *> *detectionImages;

/**
 Enables the estimation of a scale factor which may be used to correct the physical size of an image.
 @discussion If set to true ARKit will attempt to use the computed camera positions in order to compute the scale by which the given physical size
 differs from the estimated one. The information about the estimated scale can be found as the property estimatedScaleFactor on the ARImageAnchor.
 @note When set to true the transform of a returned ARImageAnchor will use the estimated scale factor to correct the translation. Default value is NO.
  */
@property (nonatomic, assign) BOOL automaticImageScaleEstimationEnabled;

/**
 Maximum number of images to track simultaneously.
 @discussion Setting the maximum number of tracked images will limit the number of images that can be tracked in a given frame.
 If more than the maximum is visible, only the images already being tracked will continue to track until tracking is lost or another image is removed.
 Images will continue to be detected regardless of images tracked. Default value is zero.
 */
@property (nonatomic, assign) NSInteger maximumNumberOfTrackedImages;

/**
 Objects to detect in the scene.
 @discussion If set the session will attempt to detect the specified objects. When an object is detected an ARObjectAnchor will be added to the session.
 */
@property (nonatomic, copy) NSSet<ARReferenceObject *> *detectionObjects;

/**
 Enable or disable app clip code tracking. Disabled by default. When enabled, detected app clip codes will be surfaced as an ARAppClipCodeAnchor.
 */
@property (nonatomic, assign) BOOL appClipCodeTrackingEnabled API_AVAILABLE(ios(14.3));

/**
 Indicates whether app clip code tracking can be enabled on this device.
 */
@property (class, nonatomic, readonly) BOOL supportsAppClipCodeTracking API_AVAILABLE(ios(14.3));

/**
 Determines the availability of geo tracking at the current location.

 @discussion This method will attempt to acquire a location fix on a background thread, then check availability.

 @param completionHandler Completion handler that is called when availability has been determined. This handler is executed on an arbitrary serial queue. It takes the following parameters:
        isAvailable - True if geo tracking is available at the current location, otherwise false.
        error - An error that indicates why geo tracking is not available at the current location.
 */
+ (void)checkAvailabilityWithCompletionHandler:(void (^)(BOOL isAvailable, NSError * _Nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC;

/**
Determines the availability of geo tracking at the given location.

@param coordinate Location at which to check.
@param completionHandler Completion handler that is called when availability has been determined. This handler is executed on an arbitrary serial queue. It takes the following parameters:
       isAvailable - True if geo tracking is available at the given location, otherwise false.
       error - An error that indicates why geo tracking is not available at the given location.
*/
+ (void)checkAvailabilityAtCoordinate:(CLLocationCoordinate2D)coordinate completionHandler:(void (^)(BOOL isAvailable, NSError * _Nullable error))completionHandler NS_SWIFT_DISABLE_ASYNC;

- (instancetype)init;
+ (instancetype)new NS_SWIFT_UNAVAILABLE("Use init() instead");

@end



NS_ASSUME_NONNULL_END
